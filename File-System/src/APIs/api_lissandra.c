/*
 * api_lissandra.c
 *
 *  Created on: 16 may. 2019
 *      Author: jhon
 */
#include "api_lissandra.h"


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
	char* aux_path_directorio=str_concat(lfs.puntoDeMontaje,"Tables/");
	aux_path_directorio=str_concat(aux_path_directorio,rutaTabla);
	if(mkdir(aux_path_directorio, S_IRWXU) == -1){
		log_error(logger, "No se pudo crear directorio %s" ,aux_path_directorio);
		free(aux_path_directorio);
		return ;
	}
	else {
		free(aux_path_directorio);
	}
}
//
//
//}
//
void crearMetadata(const char rutaArchivo, const char tipoConsistencia, unsigned int numeroParticiones,
		unsigned int tiempoCompactacion){

	char* rutaMetadata = archivo_path(rutaArchivo, "Tables/Metadata.met");
	crearArchivo(rutaMetadata);
	insertarInfoEnMetadata(rutaMetadata, tipoConsistencia, numeroParticiones, tiempoCompactacion);
	free(rutaMetadata);
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


