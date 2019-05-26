/*
 * api_lissandra.h
 *
 *  Created on: 16 may. 2019
 *      Author: jhon
 */

#ifndef APIS_API_LISSANDRA_H_
#define APIS_API_LISSANDRA_H_

#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> // para a estructura stat que me da la descripcion del archivo
#include <dirent.h>
#include <stdlib.h>
#define EXITSUCCESS 1
#define EXITFAILURE 0
#define STRONGCONSISTENCY "SC"
#define EVENTUALCONSISTENCY "EC"
#include <stdbool.h>

#include "../config/config.h"

//funciones de la API de LFS,para ser consultadas
void select1(const char * nombre_de_tabla, unsigned int key);
	//el timestamp es opcional
void insert_1(const char* nombre_de_tabla,unsigned int key , const char* value);
void insert_2(const char* nombre_de_tabla,unsigned int key , const char* value, const char * timestamp);
void create(const char* nombre_de_tabla,const char* tipo_consistencia,unsigned int numero_de_particiones,unsigned int tiempo_de_compactacion );
void describe1();
void describe2(const char* nombre_de_tabla);
void drop(const char* nombre_de_tabla);


bool verificar_existencia_de_tabla(const char* nombre_de_tabla);

typedef struct {
	char* CONSISTENCY;//=SC
	unsigned int PARTITIONS;//=3
	unsigned long COMPACTION_TIME;//=60000
}Metadata_Tabla;

//auxiliares
char archivo_path(const char rutaMontaje, const char *rutaArchivo);

void crearMetadata_v2(const char* pathTabla,const char* tipoConsistencia, unsigned int numeroParticiones,
		unsigned int tiempoCompactacion);

void mostrarMetadata(const char* path_config);

#endif /* APIS_API_LISSANDRA_H_ */
