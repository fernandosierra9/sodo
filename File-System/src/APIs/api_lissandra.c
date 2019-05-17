/*
 * api_lissandra.c
 *
 *  Created on: 16 may. 2019
 *      Author: jhon
 */
#include "api_lissandra.h"


void* select1(const char * nombre_de_tabla, unsigned int key){
	verificar_existencia_de_tabla(nombre_de_tabla);
	void* unaMetadata=obtenerMetadata(nombre_de_tabla);

}
	//el timestamp es opcional
void* insert_1(const char* nombre_de_tabla,unsigned int key , const char* value);
void* insert_2(const char* nombre_de_tabla,unsigned int key , const char* value, const char * timestamp);
void* create(const char* nombre_de_tabla,const char* tipo_consistencia,unsigned int numero_de_particiones,unsigned int tiempo_de_compactacion );
void* describe1();
void* describe2(const char* nombre_de_tabla);
void* drop(const char* nombre_de_tabla);
