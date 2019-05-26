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
	verificar_existencia_de_tabla(nombre_de_tabla);
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
void create(const char* nombre_de_tabla,const char* tipo_consistencia,unsigned int numero_de_particiones,unsigned int tiempo_de_compactacion ){
	//	//falta validaciones de los parametros de los unsigned
		validarCadenaNoVacia(nombre_de_tabla," nombre de la tabla no debe ser vacio");
		validarTipoConsistencia(tipo_consistencia);

		string_to_upper(nombre_de_tabla);
		char * pathTableMasNombreDeTabla_aux = str_concat("Tables/",nombre_de_tabla);
		char* rutaTabla = archivo_path(lfs.puntoDeMontaje, pathTableMasNombreDeTabla_aux);
		free(pathTableMasNombreDeTabla_aux);
		if(existeTabla(rutaTabla) == EXITSUCCESS){
			log_info(logger,"Creando tabla %s" , nombre_de_tabla);
			crearTabla(rutaTabla);
			//aplicar_retardo();
			crearMetadata(nombre_de_tabla, tipo_consistencia, numero_de_particiones, tiempo_de_compactacion);
			//aplicar_retardo();
			crearArchivosBinariosYAsignarBloque(rutaTabla, numero_de_particiones);
		}
		else{
			log_error(logger, "Ya existe la tabla %s" ,nombre_de_tabla);
			printf("Ya existe la tabla %s" ,nombre_de_tabla);
		}
		free(rutaTabla);
}
void describe1();
void describe2(const char* nombre_de_tabla);
void drop(const char* nombre_de_tabla){

}

bool  verificar_existencia_de_tabla(const char* nombre_de_tabla){
	//if exit(RES)
	bool yaExiste=false;
	//loggear el error (de que existe la tabla )
	return yaExiste;
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
int existeTabla(const char* rutaTabla){
	DIR *directorio = opendir(rutaTabla);
	if(directorio == NULL){
		return EXITSUCCESS;
	}
	closedir(directorio);
	return EXITFAILURE;
}
////--------------------------VALIDACIONES FIN
//
//
////--------------------------EJECUCIONES INICIO

void crearTabla(const char* rutaTabla){
//	char* aux_path_directorio=str_concat(lfs.puntoDeMontaje,"Tables/");
//	aux_path_directorio=str_concat(aux_path_directorio,rutaTabla);
	if(mkdir(rutaTabla, S_IRWXU) == -1){
		log_error(logger, "No se pudo crear directorio %s" ,rutaTabla);
		return ;
	}
	else {
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
void crearMetadata_v2(const char* pathTabla,const char* tipoConsistencia, unsigned int numeroParticiones,
		unsigned int tiempoCompactacion){ //ok
	FILE* unArchivo=fopen(pathTabla,"w+r");
	fprintf(unArchivo,"CONSISTENCY=%s \n",tipoConsistencia);
	fprintf(unArchivo,"PARTITIONS=%d \n",numeroParticiones );
	fprintf(unArchivo,"COMPACTION_TIME=%d ",tiempoCompactacion);
	fclose(unArchivo);
//	CONSISTENCY=SC
//	PARTITIONS=3
//	COMPACTION_TIME=60000
}
void mostrarMetadata(const char* path_config){

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


