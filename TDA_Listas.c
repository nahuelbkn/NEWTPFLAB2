#include "TDA_Listas.h"

nodoListaCancion * inicLista () {
    return NULL;
}

nodoListaCancion * crearNodoLista (stCancion datos) {
    nodoListaCancion * nuevo = (nodoListaCancion*) malloc(sizeof(nodoListaCancion));
    nuevo->c = datos;
    nuevo->ante = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

nodoListaCancion * agregarPpio (nodoListaCancion * lista, nodoListaCancion * nuevo) {
    if (!lista)
        lista = nuevo;
    else {
        nuevo->sig = lista;
        lista->ante = nuevo;
        lista = nuevo;
    }
    return lista;
}

void mostrarListaCanciones (nodoListaCancion * lista) {
    system("cls");
    printf("/// ----- MI PLAYLIST ----- ///\n");

    if (!lista)
        printf("\n\n\tNo hay canciones en la PlayList.\n\n\n");

    while (lista) {
        mostrarUnNodoCancion(lista);
        lista = lista->sig;
    }
}

void mostrarUnNodoCancion (nodoListaCancion * node) {
    if (node)
        mostrarRegistroCancion(node->c, 5);
}
