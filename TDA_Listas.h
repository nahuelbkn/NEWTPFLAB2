#ifndef TDA_LISTAS_H_INCLUDED
#define TDA_LISTAS_H_INCLUDED

#include "TDA_Arboles.h"

typedef struct {
    stCancion c;
    struct nodoListaCancion * sig;
} nodoListaCancion;

nodoListaCancion * inicLista ();
nodoListaCancion * crearNodoLista (stCancion datos);
nodoListaCancion * agregarPpio (nodoListaCancion * lista, nodoListaCancion * nuevo);
void mostrarListaCanciones (nodoListaCancion * lista);
void mostrarUnNodoCancion (nodoListaCancion * node);

#endif // TDA_LISTAS_H_INCLUDED
