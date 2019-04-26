/*
 * PaginacionSegmentacion.h
 *
 *  Created on: 22 abr. 2019
 *      Author: utnso
 */

#ifndef PAGINACIONSEGMENTACION_H_
#define PAGINACIONSEGMENTACION_H_


#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <commons/bitarray.h>
#include <commons/collections/list.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>


typedef struct {
	int numeroPagina;
	int direccionFisica;
} paginacion;


typedef struct {
	char* nombreTabla;
	t_list * direccionTablaDePaginas;
} segmentacion;

typedef struct{
	char* nombreTabla;
	char* value;
	uint16_t key;
	unsigned long epoc;
} registroTabla;

registroTabla *buscarPagina(t_list *tablaPaginas,uint16_t keyDeBusqueda,int *numeroDeNodo,int tam,char *nombreTabla,void *memoria);
void destruirBitmap(t_bitarray *bitmap);
void limpiarBitMap(t_bitarray *bitmap);
void liberarPaginacionSementacion(t_list *tablaSegmentos);
int cantidadDePaginas(t_bitarray *bitmap);
int listaLFSvacia(t_list *listaLFS);
void liberarPaginacionSementacion(t_list *tablaSegmentos);
void agregar_TablaDePaginaDeSegmento(segmentacion *segmento);
void agregar_pagina(t_list *tablaPaginas,paginacion *unaPagina);
t_list *crearTablaDePaginas();
char *crearMemoria(int cantidadDebytes);
void liberarMemoria(char **memoria);
int paginaLibre();
t_bitarray *crearBitmap(int cantidadDepagina,char *direccionArchivoBitmap);
void setearPaginaEnOcupada(int numeroDepagina);
t_bitarray *bitarray;

#endif /* PAGINACIONSEGMENTACION_H_ */
