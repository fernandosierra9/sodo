/*
 ============================================================================
 Name        : Memoria.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Memoria.h"
#include <dirent.h>

int main(void) {

	log_Memoria = log_create("Memoria.log","Memoria",false,LOG_LEVEL_INFO);

	char *archivo;
	archivo="config_memoria.cfg";

	directorio_actual();
	if(validarArchivoConfig(archivo)<0)
		puts("hola");
	puts("0");
	cargar_configuracion(archivo);
    puts("1");
    lista_tabla_gossping = list_create();

	//Me conecto al file system
	crearSocket(&FileSystem_fd);
/*
	//Se conecta al file system
	if(conectar(&FileSystem_fd,config_fileSystem.puerto_fs,config_fileSystem.ip_fs)!=0){
		  puts( "error");
			exit(1);
	}
	else{
		puts("estableci conexion");
	}
*/
	pthread_t hilo_consola;
	pthread_t hilo_gossiping;
	pthread_t hilo_pool;
	pthread_t hilo_inotify;


	cantidadBytes= config_memoria.tam_mem;

	//pedir a file system
	valor = 10;


	tamanio_pagina=valor +sizeof(unsigned long long)+sizeof(uint16_t);

	int tamanio = tamanio_pagina;
	cantidad_de_Paginas =  cantidadBytes/ (tamanio);
	int diferencia= cantidad_de_Paginas % 8;
	printf("cantidad de paginas %d: \n",cantidad_de_Paginas);
	printf("tamanio %d: \n",tamanio);
	printf("diferencia %d: \n",diferencia);

	//Crea Memoria
	memoria=crearMemoria(cantidadBytes);

	//Array de Marcos
	marcos = crearBitmap(cantidad_de_Paginas,diferencia);

	//Paginas en Modificado
	modificado = crearBitmap(cantidad_de_Paginas,diferencia);


	//lista_segmento
	lista_segmento = crearTablaDeSegmentos();


	pthread_create(&hilo_consola,NULL,(void*)consola_memoria,NULL);
	pthread_detach(hilo_consola);


	//<Agregar codigo paa lo de gossiping en las funciones gossiping y pool>

	pthread_create(&hilo_pool,NULL,(void*)pool,NULL);
	//pthread_create(&hilo_gossping,NULL,(void*)gossiping,NULL);
	pthread_detach(hilo_pool);
	//pthread_detach(hilo_gossiping);


	//pthread_create(&hilo_inotify,NULL,(void*)inotify,NULL);
	//pthread_detach(hilo_inotify);

	for(;;);

	return EXIT_SUCCESS;
}


void inotify(){
	//Detectar cambios en el archivo configuracion
}

void consola_memoria(){
	log_info(log_Memoria,"Consola en linea");
	char * linea;
	int resultado;
	while(1) {
		linea = readline("API_MEMORIA>");
		struct_operacion* operacion =parsear_linea(linea);
		if(!strncmp(linea, "SELECT ", 7)) {
			resultado=existeTablaEnTablaDeSegmento((operacion->parametros)[0],lista_segmento);
			if(resultado<0){
				//Mandar msj a file system
			}
			else{

			}

		}
		if(!strncmp(linea, "INSERT ", 7)){
			//nuevoSegmento(,lista_segmento);
			resultado=agregarDatOaTabla((operacion->parametros)[0],marcos,modificado,10,lista_segmento,cantidad_de_Paginas);
			if (resultado <0){
				//iniciar journal

				//volver a agregar a tabla
				resultado=agregarDatOaTabla((operacion->parametros)[0],marcos,modificado,10,lista_segmento,cantidad_de_Paginas);
			}

			//usar la estructura registro
			//guardarEnMemoria(memoria,resultado,valor,operacion);
		}

		if(!strncmp(linea, "CREATE ", 7)){
			//mandar create a file system
		}
		if (!strncmp(linea, "DROP ", 5)){
			//mandar comando a file system
		}
		if (!strncmp(linea, "DESCRIBE ", 9)){
			//mandar a file system
		}
		if (!strncmp(linea, "JOURNAL ", 8)){
			//funcion journal
		}
		if (!strncmp(linea, "EXIT", 4)){
			break;
		}
	}
}
void gossiping(){
	t_nodo_tabla_gossiping *uno_mismo = malloc(sizeof(t_nodo_tabla_gossiping));
	uno_mismo->puerto = config_memoria.puerto;
	//uno_mismo->
	list_add(lista_tabla_gossping,uno_mismo);
	//Revisar seeds
	//Revisar tabla
}
void pool(){
		//log_info(log_MDJ,"Iniciar conexion a DMA");
		int tipo_operacion,bytesRecibidos;
		int memoria_fd;
		crearSocket(&memoria_fd);
		setearParaEscuchar(&memoria_fd, config_memoria.puerto);

		int conexion_fd=aceptarConexion(memoria_fd);

		if(conexion_fd==-1){
			exit(0);
		}

		//Espero a que el kernel o alguna otra memoria me mande una peticion

		while(1){

			//bytesRecibidos=recv(conexion_fd,&tipo_operacion,sizeof(int),0);
			int *operacion;
			operacion = recibirYDeserializarEntero(conexion_fd);
			if(operacion==NULL){
				//log_error(log_memoria,"Error al recibir la operacion del DAM");
				exit(1);
			}
			log_info(log_Memoria,"Peticion recibida del Kernel/Memoria, procesando....");


			switch (*operacion){
				case SELECT:
				{
					struct_select* select = recibirYDeserializar(conexion_fd,*operacion);

					printf("select %s:",select->nombreTabla);
				    int resultado=existeTablaEnTablaDeSegmento(select->nombreTabla,lista_segmento);
					if(resultado<0){
						puts("Recibi select");
						int resultado = SELECT_RESULTADO;
						serializarYEnviarEntero(conexion_fd, &resultado);
						//Mandar msj a file system
					}
					else{


					}

					break;
				}
				case INSERT:
				{
					struct_insert* insert = recibirYDeserializar(conexion_fd,*operacion);

					int resultado=agregarDatOaTabla(insert->nombreTabla,marcos,modificado,10,lista_segmento,cantidad_de_Paginas);
					if(resultado<0){
							//realizar journal

							//volver a agregar
							resultado=agregarDatOaTabla(insert->nombreTabla,marcos,modificado,10,lista_segmento,cantidad_de_Paginas);
					}
					printf("select %s:",insert->nombreTabla);
					log_info(log_Memoria,"INSERT recibido....");
					//guardar en marco
					//guardarEnMemoria(memoria,resultado,valor,operacion);
					//resultado = INSERT_TERMINADO;
					//serializarYEnviarEntero(conexion_fd, &resultado);
					break;
				}
				case DROP:
				{
					struct_tabla* drop = recibirYDeserializar(conexion_fd,*operacion);
					break;
				}
				case CREATE:
				{
					struct_create* create = recibirYDeserializar(conexion_fd,*operacion);
					break;
				}
				case PEDIR_GOSSIPING:
				{
					//Enviar info de gossing
				}


		}
		close(conexion_fd);
		}
}
 //logica para lo de grooping


void cargar_configuracion(char *archivo){

	memoria_config_leer=config_create(archivo);
	config_memoria.puerto=config_get_int_value(memoria_config_leer,"PUERTO");
	config_memoria.ip_fs=string_duplicate(config_get_string_value(memoria_config_leer,"IP_FS"));
	config_memoria.puerto_fs=config_get_int_value(memoria_config_leer,"PUERTO_FS");
	config_memoria.ip_seeds=config_get_array_value(memoria_config_leer,"IP_SEEDS");
	config_memoria.puerto_seeds=config_get_array_value(memoria_config_leer,"PUERTO_SEEDS");
	config_memoria.retardo_mem=config_get_int_value(memoria_config_leer,"RETARDO_MEM");
	config_memoria.retardo_fs=config_get_int_value(memoria_config_leer,"RETARDO_FS");
	config_memoria.tam_mem=config_get_int_value(memoria_config_leer,"TAM_MEM");
	config_memoria.retardo_journal=config_get_int_value(memoria_config_leer,"RETARDO_JOURNAL");
	config_memoria.retardo_gossiping=config_get_int_value(memoria_config_leer,"RETARDO_GOSSIPING");
	config_memoria.memori_number=config_get_int_value(memoria_config_leer,"MEMORY_NUMBER");

	config_destroy(memoria_config_leer);

}

void directorio_actual(){
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {

			dir_actual= malloc(strlen(cwd)+1);
		    memcpy(dir_actual,cwd,strlen(cwd));
		    dir_actual[strlen(cwd)]='\0';
	}
	else
	{
	       perror("getcwd() error");
	}
	puts(dir_actual);
}
void journal(t_list *lista_segmento,t_bitarray* modificado,int socket){
	int cantidad = list_size(lista_segmento);
	int tam_registro = sizeof(unsigned long long)+sizeof(uint16_t)+valor;
	t_list * lista_enviar= list_create();
	for (int i=0;i<cantidad;i++){
		 segmentacion* segmento =list_get(lista_segmento,i);
		 int cantidad_tabla=list_size(segmento->direccionTablaDePaginas);
		 for  (int k=0;k<cantidad_tabla;i++){
			  paginacion *unaPagina = list_get(segmento->direccionTablaDePaginas,k);
			  if( bitarray_test_bit(modificado,unaPagina->numeroPagina)){
				  int marco=k;
				  struct_insert *registro_enviar = malloc(sizeof(struct_insert));
				  registro_enviar->nombreTabla=strdup(segmento->nombreTabla);
				  memcpy(registro_enviar->valor,memoria+marco*tam_registro,valor);
				  memcpy(&registro_enviar->key,memoria+marco*tam_registro+valor,sizeof(uint16_t));
				  memcpy(&registro_enviar->timestats,memoria+marco*tam_registro+valor+sizeof(uint16_t),sizeof(unsigned long long));
				  list_add(lista_enviar,registro_enviar);
			  }
			  list_destroy_and_destroy_elements(segmento->direccionTablaDePaginas,free);
		 }
	}
	struct_journal_tabla* enviar = malloc(sizeof(struct_journal_tabla));
	enviar->lista = lista_enviar;

	enviar->cantidad = sizeof(lista_enviar);
	int operacion = JOURNAL ;
	serializarYEnviar(socket,operacion,enviar);
	list_clean_and_destroy_elements(lista_segmento,free);
	list_destroy(lista_enviar);
	free(enviar);

}

