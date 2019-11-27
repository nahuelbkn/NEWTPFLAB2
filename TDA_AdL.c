#include "TDA_AdL.h"

stUsuario inicUsuario () {
    stUsuario vacio;
    vacio.idUsuario = 0;
    vacio.nombreUsuario[0] = '\0';
    vacio.pass[0] = '\0';
    vacio.genero = ' ';
    vacio.anioNacimiento = 0;
    vacio.pais[0] = '\0';
    vacio.nivel = -1;
    vacio.eliminado = 0;
    return vacio;
}

void limpiarADL (stCelda arreglo[], int dim) {
    for (int i = 0; i<dim; i++) {
        arreglo[i].cliente = inicUsuario();
        arreglo[i].listaCanciones = inicLista();
    }
}
