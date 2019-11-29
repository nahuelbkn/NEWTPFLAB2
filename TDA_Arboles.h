#ifndef TDA_ARBOLES_H_INCLUDED
#define TDA_ARBOLES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include "gotoxy.h"

typedef struct {
    int  idCancion;
    char titulo[40];
    char artista[40];
    int  duracion;
    char album[40];
    int  anio;
    char genero[20];
    char comentario[100];
    int  eliminado; // indica 1 o 0 si la canción fue eliminada
} stCancion;

typedef struct {
    stCancion c;
    struct nodoArbolCancion * izq;
    struct nodoArbolCancion * der;
} nodoArbolCancion;

nodoArbolCancion * inicArbol ();
nodoArbolCancion * crearNodoArbol (stCancion datos);

nodoArbolCancion * fromArregloToArbol (stCancion arreglo[], int inicio, int fin);
int fromArchiToArreglo (stCancion arreglo[], int dim);
nodoArbolCancion * fromArchiToArbol (nodoArbolCancion * arbol);

stCancion inicCancion ();
nodoArbolCancion * buscarCancionPorID (nodoArbolCancion * raiz, int idCancionBuscada);

#endif // TDA_ARBOLES_H_INCLUDED
