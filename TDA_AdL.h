#ifndef TDA_ADL_H_INCLUDED
#define TDA_ADL_H_INCLUDED

#include "TDA_Listas.h"

typedef struct _stUsuario {
    int  idUsuario;
    char nombreUsuario[30];
    char pass[17];  // 16 caracteres alfanuméricos y el ENTER al final
    int  anioNacimiento;
    char genero;
    char pais[60];  // el país con el nombre más largo tiene 58 letras
    int  eliminado; // indica 1 o 0 si el cliente fue eliminado
    int  nivel;     // indica 1 o 0 si el usuario es ADMIN o CLIENTE
} stUsuario;

typedef struct {
    stUsuario cliente;
    nodoListaCancion * listaCanciones;
} stCelda;

stUsuario inicUsuario ();
void limpiarADL (stCelda arreglo[], int dim);

#endif // TDA_ADL_H_INCLUDED
