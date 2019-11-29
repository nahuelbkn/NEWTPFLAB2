#include "TDA_Arboles.h"

nodoArbolCancion * inicArbol () {
    return NULL;
}

nodoArbolCancion * crearNodoArbol (stCancion datos) {
    nodoArbolCancion * nuevo = (nodoArbolCancion*) malloc(sizeof(nodoArbolCancion));
    nuevo->c = datos;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

/// arreglo tiene que estar ordenado, inicio es 0, fin es validos-1 (INICIO, MEDIO Y FIN son posiciones del arreglo)
nodoArbolCancion * fromArregloToArbol (stCancion arreglo[], int inicio, int fin) {
    nodoArbolCancion * raiz;
    if (inicio > fin) {
        raiz = inicArbol(); /// tambien puede ser "raiz = NULL;"
    } else {
        int medio = (inicio + fin)/2;   /// busca la posicion del medio del arreglo, si queda decimal redondea para abajo (se queda con la parte entera)

        raiz = crearNodoArbol(arreglo[medio]);  /// crea el nodo raiz con la cancion de la mitad del arreglo

        raiz->izq =  fromArregloToArbol(arreglo, inicio, medio-1);  /// manda el nodo izq y la mitad izq del arreglo y repite
        raiz->der = fromArregloToArbol(arreglo, medio+1, fin);      /// hace lo mismo pero para la derecha
    }
    return raiz;
}

int fromArchiToArreglo (stCancion arreglo[], int dim) { /// abre el archivo y pasa las CANCIONES ACTIVAS al arreglo
    FILE * archi = fopen("canciones.dat", "ab+");
    stCancion aux;
    int i = 0;

    if (archi) {
        fseek(archi, 0, SEEK_SET);
        while (fread(&aux, sizeof(stCancion), 1, archi)>0 && i<dim) { /// mientras tengas datos en el archivo y no te caigas del arreglo
            //if (aux.eliminado == 0) { /// solo pasa y cuenta las ACTIVAS
                arreglo[i] = aux;
                i++;
            //}
        }
        fclose(archi);
    } else {
        printf("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
    return i;   /// devuelve la cantidad de canciones pasadas al arreglo
}

nodoArbolCancion * fromArchiToArbol (nodoArbolCancion * arbol) {
    stCancion arreglo[100];
    int validos = fromArchiToArreglo(arreglo, 100);
    arbol = fromArregloToArbol(arreglo, 0, validos-1);
    return arbol;
}

stCancion inicCancion () {
    stCancion vacia;
    vacia.idCancion = 0;
    vacia.titulo[0] = '\0';
    vacia.album[0] = '\0';
    vacia.artista[0] = '\0';
    vacia.genero[0] = '\0';
    vacia.duracion = 0;
    vacia.anio = 0;
    vacia.comentario[0] = '\0';
    vacia.eliminado = 0;
    return vacia;
}

stCancion buscarCancionPorID (nodoArbolCancion * raiz, int idCancionBuscada) {
    stCancion aux = inicCancion();
    if (raiz) {
        if (raiz->c.idCancion == idCancionBuscada) {
            aux = raiz->c;
        } else {
            if (raiz->c.idCancion > idCancionBuscada) {
                aux = buscarCancionPorID(raiz->izq, idCancionBuscada);
            } else {
                aux = buscarCancionPorID(raiz->der, idCancionBuscada);
            }
        }
    }
    return aux;
}
