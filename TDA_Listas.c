#include "TDA_Listas.h"

nodoListaCancion * inicLista () {
    return NULL;
}

nodoListaCancion * crearNodoLista (stCancion datos) {
    nodoListaCancion * nuevo = (nodoListaCancion*) malloc(sizeof(nodoListaCancion));
    nuevo->c = datos;
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
    while (lista) {
        mostrarUnNodoCancion(lista);
        lista = lista->sig;
        printf("\n");
        system("pause");
    }
}

void mostrarUnNodoCancion (nodoListaCancion * node) {
    if (node)
        mostrarRegistroCancion(node->c, 0);
}

/*nodoListaCancion * borrarNodo(nodoListaCancion * lista, int dato) {
    nodoListaCancion * aBorrar=NULL;
    nodoListaCancion * seg=NULL;

    if(lista!=NULL) {
        if(lista->dato==dato) {
            aBorrar=lista;

            lista=lista->ste;
            if(lista!=NULL)
                lista->ante=NULL;

            free(aBorrar);
        } else {
            seg=lista->ste;
            while(seg!=NULL && seg->dato!=dato) {
                seg=seg->ste;
            }

            if( seg!= NULL) {
                nodoListaCancion * anterior=seg->ante; /// bajo a una variable el anterior

                anterior->ste = seg->ste; ///salteo el nodo que quiero eliminar.

                if(seg->ste) { /// si existe el nodo siguiente
                    nodoListaCancion * siguiente = seg->ste;
                    siguiente->ante=anterior;
                }
                free(seg); ///elimino el nodo.
            }
        }
    }
    return lista;
}*/
