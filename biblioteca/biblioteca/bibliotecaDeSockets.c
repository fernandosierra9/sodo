#include "bibliotecaDeSockets.h"

#define BACKLOG 20

int enviarTodo(int socketReceptor, void *buffer, int *cantidadTotal) {
    int total = 0;
    int faltante  = *cantidadTotal;
    int n;

    while(total < *cantidadTotal) {
        n = send(socketReceptor, buffer+total, faltante, 0);
        if (n == -1) {
        	break;
        }
        total += n;
        faltante -= n;
    }
    *cantidadTotal = total;
	if(n==-1){
		return -1;
	}

	return 0;
}

int crearSocket(int *mySocket) {
	int opcion=1;

	if ((*mySocket=socket(AF_INET, SOCK_STREAM,0))==-1){
		perror("-1 al crear el socket");
		return -1;
	}
	if (setsockopt(*mySocket, SOL_SOCKET, SO_REUSEADDR, &opcion, sizeof(int))==-1){
		perror("-1 al setear las opciones del socket");
		return -1;
	}
	return 0;
}

int setearParaEscuchar(int *mySocket, int puerto) {
	struct addrinfo direccion, *infoBind = malloc(sizeof(struct addrinfo));

	memset(&direccion, 0, sizeof direccion);
	direccion.ai_family = AF_INET;
	direccion.ai_socktype = SOCK_STREAM;
	direccion.ai_flags = AI_PASSIVE;

	char *port= malloc(sizeof(char)*6);

	port = string_itoa(puerto);
	getaddrinfo(NULL, port, &direccion, &infoBind);

	free(port);
	int opcion=1;

	if(bind(*mySocket,infoBind->ai_addr, infoBind->ai_addrlen)==-1){
		perror("Fallo el bind");
		free(infoBind);
		return -1;
	}
	//ver si hay que sacar el free
	free(infoBind);
	if (listen(*mySocket, BACKLOG) ==-1){
		perror("Fallo el listen");
		return -1;
	}
	//Si en todos los procesos llamamos al logger con el mismo nombre podemos llamarlo desde la biblioteca
	//log_info(logger, " ... Escuchando conexiones ... ");
	return 0;
}

int conectar(int* mySocket, int puerto, char *ip) {
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	char *stringPort = string_itoa(puerto);
	getaddrinfo(ip, stringPort, &hints, &res);
	free(stringPort);
	if(connect(*mySocket, res->ai_addr, res->ai_addrlen)!=0){
		return -1;
	}
	return 0;
}

int aceptarConexion(int fd){

	struct sockaddr_in cliente;

	unsigned int len = sizeof(struct sockaddr);

	return accept(fd,(void*)&cliente,&len);

}


int escuchar(int socketListener, fd_set *fd,  void *(funcionSocketNuevo)(int, void*), void *argumentosSocketNuevo,
				void *(funcionSocketExistente)(int, void*), void *argumentosSocketExistente){

	fd_set copia = *fd;
	int socketsComunicandose=0;
	if((socketsComunicandose=select(FD_SETSIZE,&copia,NULL,NULL,NULL))==-1) {

		perror("Fallo en el select");
		return -1;
	}

	if(FD_ISSET(socketListener,&copia)) {

		int socketNuevo=0;
		if ((socketNuevo = accept(socketListener, NULL, 0)) < 0) {

			perror("Error al aceptar conexion entrante");
			return -1;
		} else {

			FD_SET(socketNuevo,fd);

			if(funcionSocketNuevo!=NULL) {
				funcionSocketNuevo(socketNuevo, argumentosSocketNuevo);
			}
		}
	}else{

		int i;
		for (i = 0; i < FD_SETSIZE; i++) {

			if (FD_ISSET(i, &copia) && i != socketListener) {
				funcionSocketExistente(i, argumentosSocketExistente);
			}
		}
	}
	return 0;
}

struct_select* crear_select(uint16_t key,char *nombreTabla){
	 struct_select* select = malloc(sizeof(struct_select));
	 select->key = key;
	 select->nombreTabla = strdup(nombreTabla);
	 return select;
}

//Explicación: Serializamos convirtiendo a un string, de la forma <Tipo de struct>[<Tamaño elemento><Elemento>]
//Se envían de forma separada enteros y strings llamando a las funciones correspondientes
void serializarYEnviar(int socket, int tipoDePaquete, void* package){
	serializarYEnviarEntero(socket, &tipoDePaquete);

	switch(tipoDePaquete){
		case VALOR_LFS:
		{
			serializarYEnviarEntero(socket,&((valor_tamanio*)package)->valor);
			return;
		}
		case SELECT:
		{
			serializarYEnviarString(socket,((struct_select*)package)->nombreTabla);
			serializarYEnviarUint16(socket,&((struct_select*)package)->key);
			return;
		}
		case CREATE:
		{
			serializarYEnviarString(socket,((struct_create*)package)->nombreTabla);
			serializarYEnviarEntero(socket,&((struct_create*)package)->tipo);
			serializarYEnviarEntero(socket,&((struct_create*)package)->numeroParticiones);
			serializarYEnviarEntero(socket,&((struct_create*)package)->tiempoCompactacion);
			return;
		}
		case INSERT:
		{
			serializarYEnviarString(socket,((struct_insert*)package)->nombreTabla);
			serializarYEnviarUint16(socket,&((struct_insert*)package)->key);
			serializarYEnviarString(socket,((struct_insert*)package)->valor);
			serializarYEnviarUnsignedLong(socket,&((struct_insert*)package)->timestats);
			return;
		}
		case DROP:
		{
			serializarYEnviarString(socket,((struct_tabla*)package)->nombreTabla);
			return;
		}
		case JOURNAL:
		{
			serializarYEnviarEntero(socket,&((struct_journal_tabla*)package)->cantidad);
			for(int i=0 ; i<((struct_journal_tabla*)package)->cantidad;i++ ){
				struct_insert *insert =list_get (((struct_journal_tabla*)package)->lista,i);
				serializarYEnviarString(socket,insert->nombreTabla);
				serializarYEnviarUint16(socket,&insert->key);
				serializarYEnviarString(socket,insert->valor);
				serializarYEnviarUnsignedLong(socket,&insert->timestats);
			}
			return;
		}
		case VERIFICAR_TABLA:
		{
			serializarYEnviarString(socket,((struct_tabla*)package)->nombreTabla);
			return;
		}
		case ENVIAR_GOSSIPING:
		{
			t_list *lista_tabla=((t_tabla_gossiping*)package)->lista;
			int cantidad = list_size(lista_tabla);
			serializarYEnviarEntero(socket,&cantidad);
			for(int i=0;i<cantidad;i++){
				t_nodo_tabla_gossiping *nodo =list_get(lista_tabla,i);
				serializarYEnviarString(socket,nodo->ip);
				serializarYEnviarEntero(socket,&nodo->puerto);
			}
			return;
		}
		case SELECT_RESULTADO:
		{
			serializarYEnviarString(socket,((struct_insert*)package)->nombreTabla);
			serializarYEnviarUint16(socket,&((struct_insert*)package)->key);
			serializarYEnviarString(socket,((struct_insert*)package)->valor);
			serializarYEnviarUnsignedLong(socket,&((struct_insert*)package)->timestats);
			return;
		}

  }
}

void serializarYEnviarString(int socket, char *string){

	int largo, tam, offset = 0;
	char * serializado;

	largo = strlen(string)+1;
	serializado = malloc(sizeof(largo)+largo);
	memset(serializado,0,largo+sizeof(int));

	tam = sizeof(largo);
	memcpy(serializado+offset,&largo, tam);
	offset += tam;

	tam = largo;
	memcpy(serializado+offset,string,tam);
	offset += largo;

	enviarTodo(socket, serializado, &offset);
}

void serializarYEnviarEntero(int socket, int* entero){
	int largo, tam, offset = 0;
	char * serializado;

	largo = sizeof(entero);
	serializado = malloc(sizeof(largo)+largo);
	memset(serializado,0,largo+sizeof(largo));

	tam = sizeof(largo);
	memcpy(serializado+offset,&largo, tam);
	offset += tam;

	tam = largo;
	memcpy(serializado+offset,entero,tam);
	offset += largo;

	enviarTodo(socket, serializado, &offset);
}

void serializarYEnviarUint16(int socket, uint16_t* entero){
	int largo, tam, offset = 0;
	char * serializado;

	largo = sizeof(entero);
	serializado = malloc(sizeof(largo)+largo);
	memset(serializado,0,largo+sizeof(largo));

	tam = sizeof(largo);
	memcpy(serializado+offset,&largo, tam);
	offset += tam;

	tam = largo;
	memcpy(serializado+offset,entero,tam);
	offset += largo;

	enviarTodo(socket, serializado, &offset);
}

void serializarYEnviarUnsignedLong(int socket, unsigned long* entero){
	int largo, tam, offset = 0;
	char * serializado;

	largo = sizeof(entero);
	serializado = malloc(sizeof(largo)+largo);
	memset(serializado,0,largo+sizeof(largo));

	tam = sizeof(largo);
	memcpy(serializado+offset,&largo, tam);
	offset += tam;

	tam = largo;
	memcpy(serializado+offset,entero,tam);
	offset += largo;

	enviarTodo(socket, serializado, &offset);
}

void* recibirYDeserializar(int socket,int tipo){
	switch(tipo){
	case VALOR_LFS:{
		valor_tamanio *valor = malloc(sizeof(valor_tamanio));
		valor->valor = *recibirYDeserializarEntero(socket);
		return valor;

	}
	case SELECT:
	{
		printf("algo");
		struct_select* select = malloc(sizeof(struct_select));
		select->nombreTabla = recibirYDeserializarString(socket);
		select->key =*recibirYDeserializarEntero(socket);
		return select;
	}
	case CREATE:
	{
		struct_create* create = malloc(sizeof(struct_create));
		create->nombreTabla= recibirYDeserializarString(socket);
		create->tipo= *recibirYDeserializarEntero(socket);
		create->numeroParticiones=  *recibirYDeserializarEntero(socket);
		create->tiempoCompactacion = *recibirYDeserializarEntero(socket);
		return create;
	}
	case INSERT:
	{
		struct_insert* insert = malloc (sizeof(struct_insert));
		insert->nombreTabla = recibirYDeserializarString(socket);
		insert->key= *recibirYDeserializarEntero(socket);
		insert->valor= recibirYDeserializarString(socket);
		insert->timestats=*recibirYDeserializarEntero(socket);
		return insert;
	}
	case DROP:
	{
		struct_tabla* tabla = malloc(sizeof(struct_tabla));
		tabla->nombreTabla=recibirYDeserializarString(socket);
		return tabla;
	}
	case JOURNAL:
	{
		struct_journal_tabla* journal = malloc (sizeof(struct_journal_tabla));
		journal->cantidad = *recibirYDeserializarEntero(socket);
		journal->lista =list_create();
		for(int i=0;i<journal->cantidad;i++){
			struct_insert* insert = malloc (sizeof(struct_insert));
			insert->nombreTabla = recibirYDeserializarString(socket);
			insert->key= *recibirYDeserializarEntero(socket);
			insert->valor= recibirYDeserializarString(socket);
			insert->timestats=*recibirYDeserializarEntero(socket);
		}
		return journal ;
	}
	case VERIFICAR_TABLA:
	{
		char *string_archivo=recibirYDeserializarString(socket);
		return string_archivo;
	}
	case ENVIAR_GOSSIPING:
	{
		t_list *lista_tabla=list_create();
		int cantidad = *recibirYDeserializarEntero(socket);
		for(int i=0;i<cantidad;i++){
			t_nodo_tabla_gossiping *nodo =malloc(sizeof(t_nodo_tabla_gossiping));
			nodo->ip= recibirYDeserializarString(socket);
			nodo->puerto=*recibirYDeserializarEntero(socket);
			list_add(lista_tabla,nodo);
		}
		return lista_tabla;
	}
	case SELECT_RESULTADO:
	{
		struct_insert* insert = malloc (sizeof(struct_insert));
		insert->nombreTabla = recibirYDeserializarString(socket);
		insert->key= *recibirYDeserializarEntero(socket);
		insert->valor= recibirYDeserializarString(socket);
		insert->timestats=*recibirYDeserializarEntero(socket);
		return insert;
	}

	default:
		return NULL;
	}
}

int *recibirYDeserializarEntero(int socket){
	int offset = 0, n;
	int* tam = malloc(sizeof(int));

	if (recv(socket, tam, sizeof(int), 0) <=0){
		perror("Conexión falló");
		free(tam);
		return NULL;
	}

	int *numero= malloc(*tam);

	memset(numero,0,*tam);

	while(offset < *tam) {
		n = recv(socket, numero+offset, *tam, 0);
		if(n <=0){
			perror("Conexión falló");
			free(tam);
			return NULL;
		}
		offset +=n;
	}
	free(tam);
	return numero;
}

uint16_t *recibirYDeserializarUint16(int socket){
	int offset = 0, n;
	int* tam = malloc(sizeof(uint16_t));

	if (recv(socket, tam, sizeof(uint16_t), 0) <=0){
		perror("Conexión falló");
		free(tam);
		return NULL;
	}

	uint16_t *numero= malloc(*tam);

	memset(numero,0,*tam);

	while(offset < *tam) {
		n = recv(socket, numero+offset, *tam, 0);
		if(n <=0){
			perror("Conexión falló");
			free(tam);
			return NULL;
		}
		offset +=n;
	}
	free(tam);
	return numero;
}

unsigned long *recibirYDeserializarUnsignedLong(int socket){
	int offset = 0, n;
	int* tam = malloc(sizeof(unsigned long));

	if (recv(socket, tam, sizeof(unsigned long), 0) <=0){
		perror("Conexión falló");
		free(tam);
		return NULL;
	}

	unsigned long *numero= malloc(*tam);

	memset(numero,0,*tam);

	while(offset < *tam) {
		n = recv(socket, numero+offset, *tam, 0);
		if(n <=0){
			perror("Conexión falló");
			free(tam);
			return NULL;
		}
		offset +=n;
	}
	free(tam);
	return numero;
}


char *recibirYDeserializarString(int socket){

	int offset = 0, *tamString = malloc(sizeof(int)), n;

	if (recv(socket, tamString, sizeof(int), 0) <=0){
		perror("Conexión falló");
		free(tamString);
		return NULL;
	}

	char *string= malloc(*tamString);

	memset(string,0,*tamString);

	while(offset < *tamString) {
		n = recv(socket, string+offset, *tamString, 0);
		if(n <=0){
			perror("Conexión falló");
			free(tamString);
			return NULL;
		}
		offset +=n;
	}
	free(tamString);
	return string;
}

int validarArchivoConfig(char *archivo){
	int f = open(archivo, O_RDONLY);
	if (f < 0){
		//printf("no se encontro el archivo Configuracion %s.\n",archivo);
		return -1;
	}
	close(f);
	return 0;
}
