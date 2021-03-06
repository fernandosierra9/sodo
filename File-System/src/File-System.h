/*
 * File-System.h
 *
 *  Created on: 3 abr. 2019
 *      Author: utnso
 */

#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_
#include "../../biblioteca/biblioteca/bibliotecaDeSockets.h"
#include "../../biblioteca/biblioteca/parser.h"

#include <commons/config.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <commons/string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "util/util.h"
#include "APIs/api_lissandra.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "config/bitmap.h"
#include "config/metadata.h"
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

//funcion recibir que comunica con memoria
void recibir_conexion();
void crear_estructuras();
int FileSystem_fd;
char *path_bitmap();
void creacionDeBloques();
int leerMetaData();
void cargar_metadata();
void *dump_proceso();
int  LFS_FD;

void *lfs_consola();
void leer_tablas();
void ejecutar_linea_lql(struct_operacion* parametros_de_linea_lql);


#endif /* FILE_SYSTEM_H_ */
