/*
 * api_lissandra.c
 *
 *  Created on: 16 may. 2019
 *      Author: jhon
 */
#include "api_lissandra.h"

#include <commons/config.h>
#include <commons/txt.h>

void select1(const char * nombre_de_tabla, unsigned int key){
	yaExisteTabla(nombre_de_tabla);
//	void* unaMetadata=obtenerMetadata(nombre_de_tabla);
	return ;

}
	//el timestamp es opcional
void insert_1(const char* nombre_de_tabla,unsigned int key , const char* value){
//	verificar_existencia_de_tabla();
//	Metadata_Tabla unMetadataDeTabla = obtenerMetadata(nombre_de_tabla);
//
//	return ;
}
void insert_2(const char* nombre_de_tabla,unsigned int key , const char* value, const char * timestamp){
	return ;
}
//void create(const char* nombre_de_tabla,const char* tipo_consistencia,unsigned int numero_de_particiones,unsigned int tiempo_de_compactacion ){
//	//	//falta validaciones de los parametros de los unsigned
//		validarCadenaNoVacia(nombre_de_tabla," nombre de la tabla no debe ser vacio");
//		validarTipoConsistencia(tipo_consistencia);
//
//		string_to_upper(nombre_de_tabla);
//		char * pathTableMasNombreDeTabla_aux = str_concat("Tables/",nombre_de_tabla);
//		char* rutaTabla = archivo_path(lfs.puntoDeMontaje, pathTableMasNombreDeTabla_aux);
//		free(pathTableMasNombreDeTabla_aux);
//		if(existeTabla(rutaTabla) == EXITSUCCESS){
//			log_info(logger,"Creando tabla %s" , nombre_de_tabla);
//			crearTabla(rutaTabla);
//			//aplicar_retardo();
//			crearMetadata_v2(nombre_de_tabla, tipo_consistencia, numero_de_particiones, tiempo_de_compactacion);
//			//aplicar_retardo();
//			crearArchivosBinariosYAsignarBloque(rutaTabla, numero_de_particiones);
//		}
//		else{
//			log_error(logger, "Ya existe la tabla %s" ,nombre_de_tabla);
//			printf("Ya existe la tabla %s" ,nombre_de_tabla);
//		}
//		free(rutaTabla);
//}
void create(const char* nombre_de_tabla,const char* tipo_consistencia,unsigned int numero_de_particiones,unsigned int tiempo_de_compactacion ){
	puts("crear tabla");
//	if(yaExisteTabla(nombre_de_tabla))return;
	crearTabla(nombre_de_tabla);
	crearMetadata_v2(nombre_de_tabla,tipo_consistencia,numero_de_particiones,tiempo_de_compactacion);
//	puts("x");
	crearParticiones(nombre_de_tabla,numero_de_particiones);
	puts("fin crear tabla");
}
void crearParticiones(const char* tabla, unsigned int numeroDeParticiones){
	char* path_tabla=obtenerPathDeTabla(tabla);
	char* path_particion=malloc(strlen(path_tabla)+6);
	for (int numeroDeParticion = 0; numeroDeParticion < numeroDeParticiones; numeroDeParticion++) {
		sprintf(path_particion,"%s/%d.bin",path_tabla,numeroDeParticion);
		FILE* particion = fopen(path_particion,"w+r");
		fprintf(particion,"SIZE = 0 \n");
		fprintf(particion,"BLOCKS= [] ");
		fclose(particion);
	}
	free(path_tabla);
	free(path_particion);
}



void describe1();
void describe2(const char* nombre_de_tabla);
void drop(const char* nombre_de_tabla){

}

bool  yaExisteTabla(const char* nombre_de_tabla){
	//if exit(RES)

	//loggear el error (de que existe la tabla )
	char* path = obtenerPathDeTabla(nombre_de_tabla);
	bool yaExiste=existeCarpeta(path);
	free(path);
	return yaExiste;
}
char*  obtenerPathDeTabla(const char* nombre_de_tabla)
{
	char* path_aux = malloc(strlen(nombre_de_tabla)+strlen("Tables/")+strlen(lfs.puntoDeMontaje));
	sprintf(path_aux,"%s%s%s",lfs.puntoDeMontaje,"Tables/",nombre_de_tabla);
//	mostrarCaracteres(path_aux);
//	printf("path de tabla %s es \"%s\" \n",nombre_de_tabla,path_aux);
	return  path_aux;
}
void crear_directorio_para_tabla(nombre_de_tabla){

}

void crear_archivo_metadata(nombre_de_tabla,tipo_consistencia,numero_de_particiones,tiempo_de_compactacion){

}
void aplicar_retardo(){
//	sleep(lfs.retardo/1000);
//	usleep();
}










//void select1(const char  nombre_de_tabla, unsigned int key){
//	verificar_existencia_de_tabla(nombre_de_tabla);
////	void* unaMetadata=obtenerMetadata(nombre_de_tabla);
//
//}
//	//el timestamp es opcional
//void insert_1(const char nombre_de_tabla,unsigned int key , const char value){
////	verificar_existencia_de_tabla();
////	Metadata_Tabla unMetadataDeTabla = obtenerMetadata(nombre_de_tabla);
////
////	return ;
//}
//
//void insert_2(const char nombre_de_tabla,unsigned int key , const char value, const char  timestamp);
//
//void create(const char rutaMontaje, const char nombreTabla, const char* tipoConsistencia,
//		unsigned int numeroParticiones, unsigned int tiempoCompactacion){
//
//	//falta validaciones de los parametros de los unsigned
//	validarCadenaNoVacia(nombreTabla," nombre de la tabla no debe ser vacio");
//	validarTipoConsistencia(tipoConsistencia);
//
//	string_to_upper(nombreTabla);
//	char* rutaTabla = archivo_path(rutaMontaje, "Tables/" +nombreTabla);
//
//	if(existeTabla(rutaTabla) == EXITSUCCESS){
//		log_info(logger,"Creando tabla" + nombreTabla);
//		crearTabla(rutaTabla);
//		//aplicar_retardo();
//		crearMetadata(nombreTabla, tipoConsistencia, numeroParticiones, tiempoCompactacion);
//		//aplicar_retardo();
//		crearArchivosBinariosYAsignarBloque(rutaTabla, numeroParticiones);
//	}
//	else{
//		log_error(logger, "Ya existe la tabla" +nombreTabla);
//		printf("Ya existe la tabla" +nombreTabla);
//	}
//	free(rutaTabla);
//}
//
char archivo_path(const char rutaMontaje, const char *rutaArchivo){

	char  complete_path = (char ) malloc(1 + strlen(rutaMontaje) + strlen(rutaArchivo));
    strcpy(complete_path, rutaMontaje);
    strcat(complete_path, rutaArchivo);
    return complete_path;
}
//
////--------------------------VALIDACIONES INICIO
void validarCadenaNoVacia(const char cadena, const char mensajeError){
	if(string_is_empty(cadena)){
		printf(mensajeError);
		return ;
	}
}
//
void validarNombreTablaNoVacia(const char* nombreTabla){
	validarCadenaNoVacia(nombreTabla, "El nombre de la tabla no puede ser vacío");
}

void validarTipoConsistencia(const char* tipoConsistencia){
	validarCadenaNoVacia(tipoConsistencia, "El tipo de consistencia no puede ser vacío");
	validarTipoConsitenciaExistente(tipoConsistencia);
}

void validarTipoConsitenciaExistente(const char* tipoConsistencia){
	if(tipoConsistencia != STRONGCONSISTENCY || tipoConsistencia != EVENTUALCONSISTENCY){
		printf("El tipo de consistencia no existe");
	}
}
//
bool existeCarpeta(const char* path_tabla){
	bool existe=false;
	DIR *directorio = opendir(path_tabla);
	if(directorio == NULL)existe=true;
//		return EXITSUCCESS;
//	}
	closedir(directorio);
//	return EXITFAILURE;
	return existe;
}
////--------------------------VALIDACIONES FIN
//
//
////--------------------------EJECUCIONES INICIO

void crearTabla(const char* nombreDeTabla){//ok

	char* path_aux = malloc(strlen(nombreDeTabla)+strlen("Tables/")+strlen(lfs.puntoDeMontaje));
	sprintf(path_aux,"%s%s%s",lfs.puntoDeMontaje,"Tables/",nombreDeTabla);
//	mostrarCaracteres(path_aux);
	printf("path de tabla %s es \"%s\" \n",nombreDeTabla,path_aux);

	if(mkdir(path_aux, S_IRWXU) == -1){
		log_error(logger, "No se pudo crear directorio para tabla  \"%s\" \n" ,nombreDeTabla);
		free(path_aux);
		return ;
	}
	else {
		free(path_aux);
	}
}
//
//
//}
//
void crearMetadata(const char* pathDeTabla, const char tipoConsistencia, unsigned int numeroParticiones,
		unsigned int tiempoCompactacion){

//	char* rutaMetadata = archivo_path(pathDeTabla, "Tables/Metadata.met");
	crearArchivo(pathDeTabla);
	insertarInfoEnMetadata(pathDeTabla, tipoConsistencia, numeroParticiones, tiempoCompactacion);
	free(pathDeTabla);
}
void crearMetadata_v2(const char* tabla,const char* tipoConsistencia, unsigned int numeroParticiones,
		unsigned int tiempoCompactacion){ //ok
	char* aux_path=obtenerPathDeTabla(tabla);
	char* path_metadata=malloc(strlen(aux_path)+strlen("/Metadata.metadata")+1); //str_concat(aux_path,"/Metadata.metadata");
	sprintf(path_metadata,"%s/Metadata.metadata",aux_path);
	free(aux_path);
	FILE* unArchivo=fopen(path_metadata,"w+r");
	free(path_metadata);
	fprintf(unArchivo,"CONSISTENCY=%s \n",tipoConsistencia);
	fprintf(unArchivo,"PARTITIONS=%d \n",numeroParticiones );
	fprintf(unArchivo,"COMPACTION_TIME=%d ",tiempoCompactacion);
	fclose(unArchivo);
//	CONSISTENCY=SC
//	PARTITIONS=3
//	COMPACTION_TIME=60000
}
void mostrarMetadata(const char* path_config){ //ok
	//obtener metadata
	Metadata_Tabla unMetadata;//=obtenerMetadata(path_config);
	t_config* unConfig=config_create(path_config);
	if(unConfig==NULL){
		fprintf(stderr,"No Existe el archivo %s \n",path_config);
		return;
	}
	else {
		unMetadata.COMPACTION_TIME=config_get_int_value(unConfig,"COMPACTION_TIME");
		unMetadata.CONSISTENCY=strdup(config_get_string_value(unConfig,"CONSISTENCY"));
		unMetadata.PARTITIONS=config_get_int_value(unConfig,"PARTITIONS");
	}
	config_destroy(unConfig);
	//mostrar
	printf("COMPACTION_TIME = %d  \n",unMetadata.COMPACTION_TIME);
	printf("CONSISTENCY= %s \n",unMetadata.CONSISTENCY);
	printf("PARTITIONS= %d \n",unMetadata.PARTITIONS);

	free(unMetadata.CONSISTENCY);

}
void crearArchivo(const char rutaArchivo, const char tipoArchivo){

	log_info(logger, "Creando archivo" + tipoArchivo);
	FILE *archivo = fopen(string_append(rutaArchivo), "w");
	if(archivo == NULL){
		log_error(logger, "Creando archivo" + tipoArchivo);
	}
	fclose(archivo);
}

void insertarInfoEnMetadata(const char rutaMetadata, const char tipoConsistencia, unsigned int numeroParticiones,
		unsigned int tiempoCompactacion){

	log_info(logger, "Grabar archivo metadata");
	FILE *metadata = fopen(string_append(rutaMetadata), "a");
	if(metadata == NULL){
		log_error(logger, "Grabar archivo metadata");
	}
	else{
		Metadata_Tabla *record = malloc(sizeof(Metadata_Tabla));
		record->CONSISTENCY = tipoConsistencia;
		record->PARTITIONS = numeroParticiones;
		record->COMPACTION_TIME = tiempoCompactacion;
		fwrite(&record, sizeof(record), 1, metadata);
		free(record);
	}
	fclose(metadata);

}

void crearArchivosBinariosYAsignarBloque(const char* rutaArchivo, unsigned int numeroParticiones){

	for(int i = numeroParticiones; i > 0; i--){

		char *nombreArchivo = archivo_path(i-1, ".bin");
		char *rutaArchivoBinario = archivo_path(rutaArchivo, nombreArchivo);
		crearArchivo(rutaArchivoBinario, nombreArchivo);
		free(nombreArchivo);
		free(rutaArchivoBinario);
	}
}

void copiarStringABloquesLibres(const char* contenido_LQL){
//	char*  path_posicionDelBloqueLibre = getBloqueLibre_path_v2();

}


//void aplicar_retardo(){
////	sleep(lfs.retardo/1000);
////	usleep();
//
////}
//
//void* describe1();
//void describe2(const char nombre_de_tabla);
//void drop(const char nombre_de_tabla);
//--------------------------EJECUCIONES FIN


