/*
 * api_lissandra.c
 *
 *  Created on: 16 may. 2019
 *      Author: jhon
 */
#include "api_lissandra.h"


void* select1(const char * nombre_de_tabla, unsigned int key){
	verificar_existencia_de_tabla(nombre_de_tabla);
//	void* unaMetadata=obtenerMetadata(nombre_de_tabla);
	return NULL;
}
	//el timestamp es opcional
void insert_1(const char* nombre_de_tabla,unsigned int key , const char* value){
//	verificar_existencia_de_tabla();
//	Metadata_Tabla unMetadataDeTabla = obtenerMetadata(nombre_de_tabla);
//
//	return ;
}
void* insert_2(const char* nombre_de_tabla,unsigned int key , const char* value, const char * timestamp){
	return NULL;
}
void create(const char* nombre_de_tabla,const char* tipo_consistencia,unsigned int numero_de_particiones,unsigned int tiempo_de_compactacion ){
//	if( verificar_existencia_de_tabla(nombre_de_tabla)){
//		return;
//	}
//	else{
//
//		crear_directorio_para_tabla(nombre_de_tabla);
//		aplicar_retardo();
//		crear_archivo_metadata(nombre_de_tabla,tipo_consistencia,numero_de_particiones,tiempo_de_compactacion);
//		aplicar_retardo();
//	}
}
void* describe1();
void* describe2(const char* nombre_de_tabla);
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
