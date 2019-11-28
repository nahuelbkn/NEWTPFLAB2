#include "TDA_Arboles.h"
#include "TDA_Listas.h"
#include "TDA_AdL.h"

#define archiCanciones "canciones.dat"
#define archiPlaylist "playlist.dat"
#define archiUsuarios "usuarios.dat"

typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;

/// ------------------------------------------------------- PROTOTIPADOS ------------------------------------------------------ ///
void banner ();

void primeraPantalla ();
int menuPrimeraPantalla ();

int pantallaLogin (int opcion);
stUsuario menuLogin (int opcion);

void pantallaRegistro (int opcion);
void menuRegistro (int opcion);

void pantallaPpalAdmin (stCelda ADL[], int validos, int posLogueado, nodoArbolCancion * arbolDeCanciones);
int menuPpalAdmin ();

void pantallaPpalCliente (stCelda ADL[], int validos, int posLogueado, nodoArbolCancion * arbolDeCanciones);
int menuPpalCliente ();

void pantallaModificarPerfilDesdeArreglo (stCelda ADL[], int validos, int posLogueado, int clave);
int menuPantallaModificarPerfil (stUsuario modificar, int clave);

void modificarUsuario (stCelda ADL[], int validos, int clave);

void mostrarArchivoUsuarios ();

void pantallaListarCanciones (int clave);
int menuListarCanciones ();
void mostrarArregloCanciones (stCancion arreglo[], int validos, int clave);
void mostrarRegistroCancion (stCancion c, int clave);
int posMenorPorTitulo(stCancion arreglo[], int validos, int pos);
int posMenorPorGenero(stCancion arreglo[], int validos, int pos);
int posMenorPorAlbum(stCancion arreglo[], int validos, int pos);
void ordenacionSeleccionCanciones(stCancion arreglo[], int validos, int clave);

void ocultarPass (char password[]);
int moverCursor(int X, int Y, int arriba, int abajo, int saltos);

void escribirUsuarioEnArchi (stUsuario usr);
int contarRegistrosUsuario ();
int contarRegistrosPlaylist ();
int contarUsuariosActivos ();
void mostrarRegistroUsuario (stUsuario usr, int nivel);

int existeUsuario (stUsuario usr, stUsuario * buscado);

void buscarCancionEnArbol (stCelda ADL[], int validos, int posLogueado, nodoArbolCancion * arbolDeCanciones, int clave);
void guardarRegistroPlaylist (stPlaylist guardar);

int buscarClienteEnArreglo (stCelda ADL[], int validos, int idUsuarioBuscado);
void cargarClientesActivos (stCelda ADL[], int validos);
int buscarPosDelUserLogueado (stCelda arreglo[], int validos, int idBuscador);
void levantarUsuarioCompleto (stCelda ADL[], int dimension, nodoArbolCancion * raiz);
void cargarUsuariosActivos (stCelda ADL[], int validos);
void cargarPlaylistDeClientesActivos (stCelda ADL[], int validos, nodoArbolCancion * raiz);

int contarRegistrosCancion ();
stCancion crearCancion ();
void altaCancionEnArchivo ();

void modificarUsuarioDesdeArchivo (int idModificar);
void persistirUsuario (stCelda ADL[], int validos, int posLogueado);
nodoListaCancion * agregarCancionToPlaylist (nodoListaCancion * lista, stCancion buscada);

void reproducirCancion(stCancion cancion);
void reproducirPlayList(nodoListaCancion * listaUsuario);
int subMenuReproductor();

/// ----------------------------------------------------- FIN PROTOTIPADOS ---------------------------------------------------- ///

int main()
{
    primeraPantalla();
    return 0;
}

void banner ()
{
    system("cls");
    gotoxy(45,0);
    puts("++--------------------------------------------------------++");
    gotoxy(45,1);
    puts("||  _____  _     _           _            _               ||");
    gotoxy(45,2);
    puts("|| |  __ \\(_)   | |         | |          | |              ||");
    gotoxy(45,3);
    puts("|| | |  | |_ ___| | __      | | ___   ___| | _____ _   _  ||");
    gotoxy(45,4);
    puts("|| | |  | | / __| |\/ \/  _   | |/ _ \\ / __| |/ / _ \\ | | | ||");
    gotoxy(45,5);
    puts("|| | |__| | \\__ \\   <  | |__| | (_) | (__|   <  __/ |_| | ||");
    gotoxy(45,6);
    puts("|| |_____/|_|___/_|\\_\\  \\____/ \\___/ \\___|_|\\_\\___|\\__, | ||");
    gotoxy(45,7);
    puts("||                                                  __/ | ||");
    gotoxy(45,8);
    puts("||                                                 |___/  ||");
    gotoxy(45,9);
    puts("++--------------------------------------------------------++");
}

void primeraPantalla ()
{
    int posLogueado;
    int idLogueado;
    int opcion;

    do
    {
        int dimension = contarUsuariosActivos();
        stCelda * ADL = (stCelda*) malloc(sizeof(stCelda) * dimension);
        limpiarADL(ADL, dimension);

        nodoArbolCancion * arbolDeCanciones = inicArbol();
        arbolDeCanciones = fromArchiToArbol(arbolDeCanciones);

        levantarUsuarioCompleto(ADL, dimension, arbolDeCanciones);
        hidecursor(0);
        opcion = menuPrimeraPantalla();
        switch (opcion)
        {
        case 1:
            idLogueado = pantallaLogin(opcion);
            posLogueado = buscarPosDelUserLogueado(ADL, dimension, idLogueado);
            pantallaPpalAdmin(ADL, dimension, posLogueado, arbolDeCanciones);
            break;

        case 2:
            idLogueado = pantallaLogin(opcion);
            posLogueado = buscarPosDelUserLogueado(ADL, dimension, idLogueado);
            pantallaPpalCliente(ADL, dimension, posLogueado, arbolDeCanciones);
            break;

        case 3:
            pantallaRegistro(opcion);
            break;

        case 4: // salir
            gotoxy(60, 18);
            printf("Gracias. Vuelvas prontos!\n");
            //No existe -o al menos no encontré- el ascii de "¡" (Signo de admiración de apertura).
            gotoxy(60, 22);
            break;

        default:
            gotoxy(60,19);
            printf("Opci%cn inv%clida.", 162, 160);
            Sleep(1000);
            system("cls");
        }
    }
    while (opcion >= 1 && opcion <= 3);
}

int menuPrimeraPantalla ()
{
    int opcion;
    banner();
    gotoxy(60,11);
    puts("Ingresar como Admin");
    gotoxy(60,12);
    puts("Ingresar como Usuario");
    gotoxy(60,13);
    puts("Registrarse");
    gotoxy(60,14);
    puts("Salir");
    opcion = moverCursor(58, 11, 11, 14, 1);
    return opcion;
}

int moverCursor(int X, int Y, int arriba, int abajo, int saltos)
{
    int x=X, y=Y, opcion=1;
    char control;

    //color(x);

    gotoxy(x, y);
    printf("%c", 62);
    do
    {
        control = getch();
        if(control !=13)
        {
            if(control == 80 && y < abajo)
            {
                y+=saltos;
                opcion++;
            }
            else if(control == 72 && y > arriba)
            {
                y-=saltos;
                opcion--;
            }
            else if(control == 80 && y == abajo+1)
            {
                y-=saltos;
                opcion--;
            }
            else if(control == 72 && y == arriba-1)
            {
                y+=saltos;
                opcion++;
            }

            if(control == 80)
            {
                gotoxy(x, y-saltos);
                printf(" ");
                gotoxy(x, y);
                printf("%c", 62);
            }
            else if(control == 72)
            {
                gotoxy(x, y+saltos);
                printf(" ");
                gotoxy(x, y);
                printf("%c", 62);
            }

        }
    }
    while(control != 13);
    //color(15);
    gotoxy(x, y);
    printf(" ");

    return opcion;
}

void levantarUsuarioCompleto (stCelda ADL[], int dimension, nodoArbolCancion * raiz)
{
    cargarUsuariosActivos(ADL, dimension);
    cargarPlaylistDeClientesActivos(ADL, dimension, raiz);
}

void cargarUsuariosActivos(stCelda ADL[], int validos)
{
    int i = 0;
    stUsuario aux;
    FILE * archi = fopen(archiUsuarios, "rb+");

    if (archi)
    {
        while ((fread(&aux, sizeof(stUsuario), 1, archi) >0) && i<validos)
        {
            if (aux.eliminado == 0)
            {
                ADL[i].cliente = aux;
                i++;
            }
        }
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
}

int buscarClienteEnArreglo (stCelda ADL[], int validos, int idUsuarioBuscado)
{
    int rta = -1;
    int i = 0;
    while ((i<validos) && (rta == -1))
    {
        if (ADL[i].cliente.idUsuario == idUsuarioBuscado)
            rta = i;
        i++;
    }
    return rta;
}

void cargarClientesActivos (stCelda ADL[], int validos)
{
    int i = 0;
    stUsuario aux;
    FILE * archi = fopen(archiUsuarios, "rb");

    if (archi)
    {
        while ((fread(&aux, sizeof(stUsuario), 1, archi) >0) && i<validos)
        {
            if (aux.eliminado == 0)
            {
                ADL[i].cliente = aux;
                i++;
            }
        }
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
}

void cargarPlaylistDeClientesActivos (stCelda ADL[], int validos, nodoArbolCancion * raiz)
{
    FILE * archi = fopen(archiPlaylist, "ab+");
    stCancion cancion;
    stPlaylist aux;
    int pos;

    if (archi)
    {
        fseek(archi, 0, SEEK_SET);
        while (fread(&aux, sizeof(stPlaylist), 1, archi) > 0)
        {
            pos = buscarClienteEnArreglo(ADL, validos, aux.idUsuario);
            if (pos != -1)
            {
                cancion = buscarCancionPorID(raiz, aux.idCancion);
                if (cancion.idCancion != 0)
                {
                    nodoListaCancion * agregar = crearNodoLista(cancion);
                    ADL[pos].listaCanciones = agregarPpio(ADL[pos].listaCanciones, agregar);
                }
            }
        }
        fclose(archi);
    }
}

void escribirUsuarioEnArchi (stUsuario usr)
{
    FILE * archi = fopen(archiUsuarios, "ab+");

    if (archi)
    {
        fwrite(&usr, sizeof(stUsuario), 1, archi);
        fclose(archi);
    }
    else
    {
        gotoxy(60,15);
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
}

int contarRegistrosUsuario ()
{
    int cant = 0;
    FILE * archi = fopen(archiUsuarios, "ab+");
    if (archi)
    {
        fseek(archi, 0, SEEK_END);
        cant = ftell(archi)/sizeof(stUsuario);
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
    return cant;
}

int contarUsuariosActivos ()
{
    int i = 0;
    stUsuario cliente;
    FILE * archi = fopen(archiUsuarios, "ab+");

    if (archi)
    {
        fseek(archi, 0, SEEK_SET);
        while ((fread(&cliente, sizeof(stUsuario), 1, archi) >0))
        {
            if (cliente.eliminado == 0)
            {
                i++;
            }
        }
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
    return i;
}

int buscarPosDelUserLogueado (stCelda arreglo[], int validos, int idBuscador)
{
    int i = 0;
    int pos = -1;
    while (i<validos && idBuscador != arreglo[i].cliente.idUsuario)
    {
        i++;
    }
    if (arreglo[i].cliente.idUsuario == idBuscador)
    {
        pos = i;
    }
    return pos;
}

int pantallaLogin (int opcion)
{
    stUsuario logueado;
    stUsuario aux;
    int flag;
    int intentos = 0;

    do
    {
        system("cls");
        banner();
        gotoxy(55,9);
        printf("|| ----------- LOGIN ----------- ||");
        aux = menuLogin(opcion);

        flag = existeUsuario(aux, &logueado);

        if (flag < 2)
        {
            intentos++;
            gotoxy(58,15);
            printf("Usuario o contrase%ca incorrectos.", 164);
            Sleep(1000);
        }
        else
        {
            if (logueado.eliminado == 1)
            {
                intentos++;
                flag--;
                gotoxy(58,15);
                printf("El usuario ha sido eliminado.");
                Sleep(1000);
            }
            else
            {
                if (logueado.nivel != aux.nivel)
                {
                    intentos++;
                    flag--;
                    gotoxy(58,15);
                    printf("Las credenciales no coinciden.");
                    Sleep(1000);
                }
            }
        }
    }
    while (flag < 2 && intentos < 3);

    if (intentos == 3)
    {
        gotoxy(58,17);
        puts("Has fallado 3 veces seguidas.");
        gotoxy(58,18);
        puts("Cerrando el programa.");
        exit(0);
    }

    return logueado.idUsuario;
}

int existeUsuario (stUsuario usr, stUsuario * buscado)
{
    int flag = 0;
    stUsuario aux;
    FILE * archi = fopen(archiUsuarios, "ab+");
    if (archi)
    {
        fseek(archi, 0, SEEK_SET);
        while ((fread(&aux, sizeof(stUsuario), 1, archi) >0) && (flag < 2))
        {
            if ((strcmpi(usr.nombreUsuario, aux.nombreUsuario)==0))
            {
                flag++;
                if (strcmp(usr.pass, aux.pass)==0)
                {
                    flag++;
                    (*buscado) = aux;
                }
            }
        }
        fclose(archi);
    }
    else
    {
        gotoxy(60,15);
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
    return flag;
}

stUsuario menuLogin (int opcion)
{
    hidecursor(1);
    stUsuario aux;

    gotoxy(55,13);
    printf("|| Contrase%ca: ", 164);
    gotoxy(55,12);
    printf("||");
    gotoxy(55,10);
    printf("||");
    gotoxy(55,11);
    printf("|| Usuario: ");
    fflush(stdin);
    gets(aux.nombreUsuario);

    gotoxy(70,13); //printf("Contrase%ca: ", 164);
    fflush(stdin);
    ocultarPass(aux.pass);



    if (opcion == 1)
        aux.nivel = 1;
    else if (opcion == 2)
        aux.nivel = 0;


    return aux;
}

void ocultarPass (char password[])
{
    int p=0;
    do
    {
        password[p] = getch();
        if (password[p] == 8)   /// backspace
        {
            if (p>0)
            {
                p--;
                printf("\b \b");
            }
        }
        else
        {
            if (password[p] != '\r') /// distinto de enter
                printf("*");
            p++;
        }
        if (p > 16 && password[p-1] != '\r')
        {
            p--;
            printf("\b \b");
        }
        fflush(stdin);
    }
    while (password[p-1] != '\r');
    password[p-1]='\0';
}

void pantallaRegistro (int opcion)
{
    system("cls");
    banner();
    menuRegistro(opcion);
}

void menuRegistro (int opcion)
{
    hidecursor(1);

    stUsuario nuevo = inicUsuario();
    nuevo.eliminado = 0;
    nuevo.nivel = 0;    /// por defecto el usuario nuevo tiene privilegios de CLIENTE, cambiar a 1 para ADMIN
    nuevo.idUsuario = contarRegistrosUsuario() + 1;         /// ID autoincremental, empieza en 1, el 0 reservado para VACIO

    int flag = 0;
    char passAux[17];

    do      /// Verificador de NOMBRE DE USUARIO
    {
        gotoxy(60,11);
        puts("                                             ");   /// LIMPIADOR
        gotoxy(60,13);
        puts("                                             ");   /// LIMPIADOR

        gotoxy(60,11);
        printf("Nombre de usuario: ");
        fflush(stdin);
        gets(nuevo.nombreUsuario);

        flag = existeUsuario(nuevo, NULL);

        if (flag == 1)
        {
            gotoxy(60,13);
            printf("Usuario existente.");
            Sleep(1000);
        }
    }
    while (flag == 1);

    do      /// Verificador de PASSWORD
    {
        gotoxy(60,13);
        printf("                                                       ");   /// LIMPIADOR
        gotoxy(60,15);
        printf("                                                       ");   /// LIMPIADOR
        gotoxy(60,17);
        printf("                                                       ");   /// LIMPIADOR

        gotoxy(60,13);
        printf("Contrase%ca: ", 164);
        fflush(stdin);
        ocultarPass(nuevo.pass);

        gotoxy(60,15);
        printf("Confirmar Contrase%ca: ", 164);
        fflush(stdin);
        ocultarPass(passAux);

        if (strcmp(nuevo.pass, passAux) != 0)
        {
            gotoxy(60,17);
            printf("Las contrase%cas no coinciden.", 164);
            Sleep(1000);
        }
    }
    while (strcmp(nuevo.pass, passAux) != 0);

    do      /// Verificador de GENERO
    {
        gotoxy(60,17);
        printf("                                                       ");   /// LIMPIADOR
        gotoxy(60,19);
        printf("                                                       ");   /// LIMPIADOR

        gotoxy(60,17);
        printf("G%cnero (M/F/O): ", 130);
        fflush(stdin);
        nuevo.genero = toupper(getchar());

        if ((nuevo.genero != 'M') && (nuevo.genero != 'F') && (nuevo.genero != 'O'))
        {
            gotoxy(60,19);
            printf("Car%ccter inv%clido.", 160, 160);
            Sleep(1000);
        }
    }
    while ((nuevo.genero != 'M') && (nuevo.genero != 'F') && (nuevo.genero != 'O'));

    do      /// Verificador de EDAD
    {
        gotoxy(60,19);
        printf("                                                       ");   /// LIMPIADOR
        gotoxy(60,21);
        printf("                                                       ");   /// LIMPIADOR

        gotoxy(60,19);
        printf("A%co de nacimiento: ", 164);
        fflush(stdin);
        scanf("%i", &nuevo.anioNacimiento);
        if ((2019 - nuevo.anioNacimiento) < 16)
        {
            gotoxy(60,21);
            printf("Debes ser mayor de 16 a%cos para registrarte.", 164);
            Sleep(1000);
        }
    }
    while ((2019 - nuevo.anioNacimiento) < 16);

    gotoxy(60,21);
    printf("Pa%cs: ", 161);
    fflush(stdin);
    gets(nuevo.pais);

    if (opcion == 1)
    {
        gotoxy(60,23);
        printf("Nivel: ");
        scanf("%i", &nuevo.nivel);

        gotoxy(60,25);
        printf("Eliminado: ");
        scanf("%i", &nuevo.eliminado);
    }

    escribirUsuarioEnArchi(nuevo);

    if (nuevo.nivel == 1)
    {
        gotoxy(60,27);
        puts("Admin registrado exitosamente.");
        Sleep(1000);
    }
    else if (nuevo.nivel == 0)
    {
        gotoxy(60,27);
        puts("Usuario registrado exitosamente.");
        Sleep(1000);
    }
}

void pantallaPpalAdmin (stCelda ADL[], int validos, int posLogueado, nodoArbolCancion * arbolDeCanciones)
{
    int opcion;

    do
    {
        system("cls");
        opcion = menuPpalAdmin();
        switch (opcion)
        {
        case 1: /// crear usuario (cliente o admin)
            pantallaRegistro(opcion);
            break;

        case 2: /// mod usuario (tanto activos en arreglo como inactivos en archivo)
            modificarUsuario(ADL, validos, ADL[posLogueado].cliente.nivel);
            break;

        case 3: /// listar usuarios
            system("cls");
            mostrarArchivoUsuarios();
            break;

        case 4:
            // buscarUsuario();
            break;

        case 5: /// subir cancion
            altaCancionEnArchivo();
            break;

        case 6:
            // modCancion();
            break;

        case 7: /// listar canciones (por titulo, genero y album)
            pantallaListarCanciones(opcion);
            break;

        case 8: /// buscar Cancion por ID en arbol
            buscarCancionEnArbol(ADL, validos, posLogueado, arbolDeCanciones, opcion);
            break;

        case 9: /// cerrar sesion (vuelve a la main screen)
            persistirUsuario(ADL, validos, posLogueado);
            break;

        case 10: /// salir
            persistirUsuario(ADL, validos, posLogueado);
            printf("\n");
            exit(0);
            break;

        default:
            printf("\nOpci%cn inv%clida.", 162, 160);
            Sleep(1000);
            system("cls");
        }
    }
    while (opcion >= 1 && opcion <= 8);
}

void buscarCancionEnArbol (stCelda ADL[], int validos, int posLogueado, nodoArbolCancion * arbolDeCanciones, int clave)
{
    int idBuscada;
    stCancion buscada;
    char opcion;
    char fav;
    stPlaylist guardar;

    do
    {
        system("cls");
        puts ("/// --- BUSCAR CANCION POR ID --- ///");
        gotoxy(1,2);
        printf("Hay %i canciones cargadas...", contarRegistrosCancion());
        gotoxy(1,3);
        printf("Ingrese el ID de la canci%cn: ", 162);
        scanf("%i", &idBuscada);
        buscada = buscarCancionPorID(arbolDeCanciones, idBuscada);
        if (buscada.idCancion > 0)
        {
            mostrarRegistroCancion(buscada, clave);
            if (clave == 0)
            {
                printf("\n\n Desea agregar a favoritos? (S/N) ");
                fflush(stdin);
                fav = toupper(getchar());
                if (fav == 'S')
                {
                    ADL[posLogueado].listaCanciones = agregarCancionToPlaylist(ADL[posLogueado].listaCanciones, buscada);
                    guardar.idCancion = buscada.idCancion;
                    guardar.idUsuario = ADL[posLogueado].cliente.idUsuario;
                    guardarRegistroPlaylist(guardar);
                }
            }
            printf("\n Buscar otra canci%cn? (S/N) ", 162);
            fflush(stdin);
            opcion = toupper(getchar());
        }
        else
        {
            printf("\nNo se encontr%c la canci%cn.", 162, 162);
            Sleep(1000);
        }
    }
    while (opcion == 'S');
}

void guardarRegistroPlaylist (stPlaylist guardar)
{
    FILE * archi = fopen(archiPlaylist, "ab+");
    guardar.idPlaylist = contarRegistrosPlaylist() + 1;

    if (archi)
    {
        fwrite(&guardar, sizeof(stPlaylist), 1, archi);
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
}

int contarRegistrosPlaylist ()
{
    int cant = 0;
    FILE * archi = fopen(archiPlaylist, "ab+");
    if (archi)
    {
        fseek(archi, 0, SEEK_END);
        cant = ftell(archi)/sizeof(stCancion);
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
    return cant;
}

int menuPpalAdmin ()
{
    hidecursor(0);
    int opcion;
    puts("------- MENU PRINCIPAL -------");

    gotoxy(3,2);
    puts("Crear un usuario");
    gotoxy(3,3);
    puts("Modificar un usuario");
    gotoxy(3,4);
    puts("Listar usuarios");
    gotoxy(3,5);
    puts("Buscar usuario especifico");
    gotoxy(3,6);
    printf("Subir canci%cn", 162);
    gotoxy(3,7);
    printf("Modificar canci%cn", 162);
    gotoxy(3,8);
    puts("Listar canciones");
    gotoxy(3,9);
    printf("Buscar canci%cn espec%cfica", 162, 161);
    gotoxy(3,10);
    printf("Cerrar sesi%cn", 162);
    gotoxy(3,11);
    puts("Salir");
    opcion = moverCursor(1, 2, 2, 11, 1);
    return opcion;
}

void modificarUsuario (stCelda ADL[], int validos, int clave)
{
    hidecursor(1);
    int idModificar = 0;
    int posModificar;

    gotoxy(23,3);
    printf(" - Ingrese el ID del usuario a modificar: ");
    fflush(stdin);
    scanf("%i", &idModificar);

    posModificar = buscarClienteEnArreglo(ADL, validos, idModificar);
    if (posModificar != -1)
    {
        pantallaModificarPerfilDesdeArreglo(ADL, validos, posModificar, clave);
        persistirUsuario(ADL, validos, posModificar);
    }
    else
        modificarUsuarioDesdeArchivo(idModificar);

}

void mostrarArchivoUsuarios ()
{
    stUsuario aux;
    FILE * archi = fopen (archiUsuarios, "rb");

    if (archi)
    {
        while (fread(&aux, sizeof(stUsuario), 1, archi)>0)
        {
            mostrarRegistroUsuario(aux, 1);
            system("pause");
        }
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
}

void mostrarRegistroUsuario (stUsuario usr, int nivel)
{
    gotoxy(0,0);
    puts("                                   ");   /// LIMPIADOR
    gotoxy(0,2);
    puts("                                   ");   /// LIMPIADOR
    gotoxy(0,3);
    puts("                                   ");   /// LIMPIADOR
    gotoxy(0,4);
    puts("                                   ");   /// LIMPIADOR
    gotoxy(0,5);
    puts("                                   ");   /// LIMPIADOR
    gotoxy(0,6);
    puts("                                   ");   /// LIMPIADOR
    gotoxy(0,7);
    puts("                                   ");   /// LIMPIADOR
    gotoxy(0,8);
    puts("                                   ");   /// LIMPIADOR
    /// se usa el nivel del usuario que accesa a la funcion para determinar la vista
    if (nivel == 1)   /// vista de admin
    {
        gotoxy(0,0);
        printf("/// --- INFO DEL USUARIO [%i] --- ///", usr.idUsuario);
        //gotoxy(3,2); printf("ID: %i", usr.idUsuario);
        gotoxy(3,2);
        printf("Usuario: %s", usr.nombreUsuario);
        gotoxy(3,3);
        printf("Contrase%ca: %s", 164, usr.pass);
        gotoxy(3,4);
        printf("G%cnero: %c", 130, usr.genero);
        gotoxy(3,5);
        printf("Nacimiento: %i", usr.anioNacimiento);
        gotoxy(3,6);
        printf("Pa%cs: %s", 161, usr.pais);
        gotoxy(3,7);
        printf("Nivel: %i", usr.nivel);
        gotoxy(3,8);
        printf("Eliminado: %i\n\n", usr.eliminado);

    }
    else     /// vista de cliente
    {
        gotoxy(0,0);
        puts ("/// ----- MI PERFIL ----- ///");
        gotoxy(3,2);
        printf("Usuario: %s", usr.nombreUsuario);
        gotoxy(3,3);
        printf("Contrase%ca: %s", 164, usr.pass);
        gotoxy(3,4);
        printf("G%cnero: %c", 130, usr.genero);
        gotoxy(3,5);
        printf("Nacimiento: %i", usr.anioNacimiento);
        gotoxy(3,6);
        printf("Pa%cs: %s", 161, usr.pais);
    }
}

int contarRegistrosCancion ()
{
    int cant = 0;
    FILE * archi = fopen(archiCanciones, "ab+");
    if (archi)
    {
        fseek(archi, 0, SEEK_END);
        cant = ftell(archi)/sizeof(stCancion);
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
    return cant;
}

stCancion crearCancion ()
{
    hidecursor(1);
    system("cls");
    stCancion nueva;

    nueva.idCancion = contarRegistrosCancion() + 1;

    gotoxy(0,0);
    printf("Creando canci%cn", 162);

    gotoxy(0,2);
    printf("ID Canci%cn: %i", 162, nueva.idCancion);

    gotoxy(0,4);
    printf("T%ctulo: ", 161);
    fflush(stdin);
    gets(nueva.titulo);

    gotoxy(0,6);
    printf("%clbum: ", 181);
    fflush(stdin);
    gets(nueva.album);

    gotoxy(0,8);
    printf("A%co: ", 164);
    scanf("%i", &nueva.anio);

    gotoxy(0,10);
    printf("Artista: ");
    fflush(stdin);
    gets(nueva.artista);

    gotoxy(0,12);
    printf("Duraci%cn (segundos): ", 162);
    scanf("%i", &nueva.duracion);

    gotoxy(0,14);
    printf("G%cnero: ", 130);
    fflush(stdin);
    gets(nueva.genero);

    gotoxy(0,16);
    printf("Comentario (opcional): ");
    fflush(stdin);
    gets(nueva.comentario);

    gotoxy(0,18);
    printf("Eliminado (NO = 0 / SI = 1): ");
    scanf("%i", &nueva.eliminado);

    return nueva;
}

void altaCancionEnArchivo ()
{
    FILE * archi = fopen(archiCanciones, "ab+");
    if (archi)
    {
        do
        {
            stCancion nueva = crearCancion();   /// si abre el archi se crean canciones a gusto del usuario
            fwrite(&nueva, sizeof(stCancion), 1, archi);
            fclose(archi);
            gotoxy(0,20);
            printf("%cCargar otra canci%cn al sistema? (S/N) ", 168, 162);
            fflush(stdin);
        }
        while (tolower(getchar()) == 's');
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
}

void pantallaListarCanciones (int clave)
{
    int dim = contarRegistrosCancion();
    stCancion * arreglo = (stCancion*) malloc(sizeof(stCancion) * dim); /// generado en tiempo de ejecucion
    int cant = fromArchiToArreglo(arreglo, dim); /// levanta todas las canciones

    int opcion;
    do
    {
        opcion = menuListarCanciones();
        switch (opcion)
        {
        case 1: /// ordena por titulo
            ordenacionSeleccionCanciones(arreglo, cant, opcion);
            mostrarArregloCanciones(arreglo, cant, clave);
            break;

        case 2: /// ordena por genero
            ordenacionSeleccionCanciones(arreglo, cant, opcion);
            mostrarArregloCanciones(arreglo, cant, clave);
            break;

        case 3: /// ordena por album
            ordenacionSeleccionCanciones(arreglo, cant, opcion);
            mostrarArregloCanciones(arreglo, cant, clave);
            break;

        case 4: ///atras
            break;

        default:
            gotoxy(60,19);
            printf("Opci%cn inv%clida.", 162, 160);
            Sleep(1000);
            system("cls");
        }
    }
    while (opcion >= 1 && opcion <= 3);
}

int menuListarCanciones ()
{
    hidecursor(0);
    int opcion;
    system("cls");
    puts ("/// ----- LISTAR CANCIONES ----- ///");
    gotoxy(3,2);
    printf("Listar por T%ctulo", 161);
    gotoxy(3,3);
    printf("Listar por G%cnero", 130);
    gotoxy(3,4);
    printf("Listar por %clbum", 181);
    gotoxy(3,5);
    printf("Atr%cs", 160);
    opcion = moverCursor(1, 2, 2, 5, 1);
    return opcion;
}

void mostrarArregloCanciones (stCancion arreglo[], int validos, int clave)
{
    system("cls");
    for (int i = 0; i<validos; i++)
    {
        mostrarRegistroCancion(arreglo[i], clave);
    }
    printf("\n\n");
    system("pause");
}

void mostrarRegistroCancion (stCancion c, int clave)
{
    puts ("\n\n/// ----- INFO CANCION ----- ///");
    if (clave == 7 || clave == 8)   /// ADMIN accede a traves de "opcion" que viaja hasta aca
    {
        printf("ID: %i", c.idCancion);
        printf("\nEliminado: %i\n", c.eliminado);

    }
    if ((clave == 7 || clave == 8) || c.eliminado == 0)
    {

        printf("T%ctulo: %s", 161, c.titulo);
        printf("\n%clbum: %s", 181, c.album);
        printf("\nA%co: %i", 164, c.anio);
        printf("\nArtista: %s", c.artista);
        printf("\nDuraci%cn: %i", 162, c.duracion);
        printf("\nG%cnero: %s", 130, c.genero);
        printf("\nComentario: %s", c.comentario);
    }
    else
    {
        printf("\n\nLa canci%cn ha sido eliminada.", 162);
        Sleep(1000);
    }
}

int posMenorPorTitulo(stCancion arreglo[], int validos, int pos)   /// ordenar por titulo
{
    stCancion menor = arreglo[pos];
    int posMenor = pos;
    int i = pos + 1;
    while (i < validos)
    {
        if (strcmpi(menor.titulo, arreglo[i].titulo)>0)
        {
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}

int posMenorPorGenero(stCancion arreglo[], int validos, int pos)   /// ordenar por genero
{
    stCancion menor = arreglo[pos];
    int posMenor = pos;
    int i = pos + 1;
    while (i < validos)
    {
        if (strcmpi(menor.genero, arreglo[i].genero)>0)
        {
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}

int posMenorPorAlbum(stCancion arreglo[], int validos, int pos)   /// ordenar por album
{
    stCancion menor = arreglo[pos];
    int posMenor = pos;
    int i = pos + 1;
    while (i < validos)
    {
        if (strcmpi(menor.album, arreglo[i].album)>0)
        {
            menor = arreglo[i];
            posMenor = i;
        }
        i++;
    }
    return posMenor;
}

void ordenacionSeleccionCanciones(stCancion arreglo[], int validos, int clave)
{
    stCancion aux;
    int ultimaPos = validos - 1;
    int posMenor;
    int i = 0;
    while(i < ultimaPos)
    {
        switch (clave)          /// "clave" es la "opcion" que elegimos en el menu que viaja hasta aca
        {
        case 1:
            posMenor = posMenorPorTitulo(arreglo, validos, i);
            break;

        case 2:
            posMenor = posMenorPorGenero(arreglo, validos, i);
            break;

        case 3:
            posMenor = posMenorPorAlbum(arreglo, validos, i);
            break;
        }
        aux = arreglo[posMenor];
        arreglo[posMenor] = arreglo[i];
        arreglo[i] = aux;
        i++;
    }
}

void pantallaPpalCliente (stCelda ADL[], int validos, int posLogueado, nodoArbolCancion * arbolDeCanciones)
{
    int opcion;

    do
    {
        opcion = menuPpalCliente();
        switch (opcion)
        {
        case 1: /// Ver perfil
            system("cls");
            mostrarRegistroUsuario(ADL[posLogueado].cliente, ADL[posLogueado].cliente.nivel);
            printf("\n\n");
            system("pause");
            break;

        case 2: /// Modificar perfil
            pantallaModificarPerfilDesdeArreglo(ADL, validos, posLogueado, ADL[posLogueado].cliente.nivel);
            break;

        case 3:
            /// Ver playlist
            mostrarListaCanciones(ADL[posLogueado].listaCanciones);
            system("pause");
            break;

        case 4:
            // escuchar playlist
            // reproducirCancion();
            break;

        case 5:
            /// Listar canciones activas
            pantallaListarCanciones(opcion);
            break;

        case 6:
            /// Reproducir Playlist del usuario.
            //reproducirPlayList(ADL[pos])
            break;

        case 7: /// Buscar cancion especifica en arbol, le pregunta al CLIENTE si la quiere agregar a su playlist
            buscarCancionEnArbol (ADL, validos, posLogueado, arbolDeCanciones, ADL[posLogueado].cliente.nivel);
            break;

        case 8:
            /// Cerrar sesion
            persistirUsuario(ADL, validos, posLogueado);
            break;

        case 9:
            /// Salir del programa
            persistirUsuario(ADL, validos, posLogueado);
            exit(0);
            break;

        default:
            printf("\nOpci%cn inv%clida.", 162, 160);
            Sleep(1000);
            system("cls");
        }
    }
    while (opcion >= 1 && opcion <= 7);
}

int menuPpalCliente ()
{
    system("cls");
    hidecursor(0);
    int opcion;
    puts("------- MENU PRINCIPAL -------");
    gotoxy(3,2);
    puts(" Ver mi perfil");
    gotoxy(3,3);
    puts(" Modificar mi perfil");
    gotoxy(3,4);
    puts(" Ver mi Playlist");
    gotoxy(3,5);
    puts(" Escuchar mi Playlist");
    gotoxy(3,6);
    puts(" Listar canciones");
    gotoxy(3,7);
    printf(" Escuchar una canci%cn", 162);
    gotoxy(3,8);
    printf(" Buscar canci%cn especifica", 162);
    gotoxy(3,9);
    printf(" Cerrar sesi%cn", 162);
    gotoxy(3,10);
    puts(" Salir");
    opcion = moverCursor(1,2,2,10,1);
    return opcion;
}

nodoListaCancion * agregarCancionToPlaylist (nodoListaCancion * lista, stCancion buscada)
{
    nodoListaCancion * fav = crearNodoLista(buscada);
    lista = agregarPpio(lista, fav);
    return lista;
}

void pantallaModificarPerfilDesdeArreglo (stCelda ADL[], int validos, int posLogueado, int clave)
{
    system("cls");          /// esta funcion modifica la el perfil de la persona que esta logueada
    stUsuario aux;          /// o sea que solo modifica usuarios activos cargados al arreglo
    char passAux[17];       /// puede ser llamada tanto por admin como por user
    int flag = 0;
    int opcion;

    do
    {
        opcion = menuPantallaModificarPerfil(ADL[posLogueado].cliente, clave);
        hidecursor(1);
        switch (opcion)
        {
        case 1: /// nombre
            do      /// Verificador de NOMBRE DE USUARIO
            {
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,2);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,2);
                printf("Usuario: ");
                fflush(stdin);
                gets(aux.nombreUsuario);

                if (strcmpi(ADL[posLogueado].cliente.nombreUsuario, aux.nombreUsuario)!=0)
                {
                    flag = existeUsuario(aux, NULL);
                    if (flag == 1)
                    {
                        gotoxy(3,15);
                        printf("Usuario existente.");
                        Sleep(1000);
                    }
                    else
                        strcpy(ADL[posLogueado].cliente.nombreUsuario, aux.nombreUsuario);
                }
            }
            while (flag == 1);
            break;

        case 2: /// pass
            do      /// Verificador de PASSWORD
            {
                gotoxy(3,3);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,3);
                printf("Contrase%ca: ", 164);
                fflush(stdin);
                ocultarPass(ADL[posLogueado].cliente.pass);

                gotoxy(3,14);
                printf("Confirmar Contrase%ca: ", 164);
                fflush(stdin);
                ocultarPass(passAux);

                if (strcmp(ADL[posLogueado].cliente.pass, passAux) != 0)
                {
                    gotoxy(3,15);
                    printf("Las contrase%cas no coinciden.", 164);
                    Sleep(1000);
                }
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,14);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,3);
                puts("                                             ");   /// LIMPIADOR
            }
            while (strcmp(ADL[posLogueado].cliente.pass, passAux) != 0);
            break;

        case 3: /// genero
            do      /// Verificador de GENERO
            {
                gotoxy(3,4);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,4);
                printf("G%cnero (M/F/O): ", 130);
                fflush(stdin);
                ADL[posLogueado].cliente.genero = toupper(getchar());

                if ((ADL[posLogueado].cliente.genero != 'M') && (ADL[posLogueado].cliente.genero != 'F') && (ADL[posLogueado].cliente.genero != 'O'))
                {
                    gotoxy(3,15);
                    printf("Car%ccter inv%clido.", 160, 160);
                    Sleep(1000);
                }
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,4);
                puts("                                             ");   /// LIMPIADOR
            }
            while ((ADL[posLogueado].cliente.genero != 'M') && (ADL[posLogueado].cliente.genero != 'F') && (ADL[posLogueado].cliente.genero != 'O'));
            break;

        case 4: /// nacimiento
            do      /// Verificador de EDAD
            {
                gotoxy(3,5);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,5);
                printf("A%co de nacimiento: ", 164);
                fflush(stdin);
                scanf("%i", &ADL[posLogueado].cliente.anioNacimiento);
                if ((2019 - ADL[posLogueado].cliente.anioNacimiento) < 16)
                {
                    gotoxy(3,15);
                    printf("Debes ser mayor de 16 a%cos para registrarte.", 164);
                    Sleep(1000);
                }
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,5);
                puts("                                             ");   /// LIMPIADOR
            }
            while ((2019 - ADL[posLogueado].cliente.anioNacimiento) < 16);
            break;

        case 5: /// pais
            gotoxy(3,6);
            puts("                                             ");   /// LIMPIADOR
            gotoxy(3,6);
            printf("Pa%cs: ", 161);
            fflush(stdin);
            gets(ADL[posLogueado].cliente.pais);
            gotoxy(3,6);
            puts("                                             ");   /// LIMPIADOR
            break;

        case 6: /// nivel (solo admin)
            if (clave == 1)   /// clave = nivel
            {
                gotoxy(3,7);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,7);
                printf("Nivel: ");
                fflush(stdin);
                scanf("%i", &ADL[posLogueado].cliente.nivel);
                gotoxy(3,6);
                puts("                                             ");   /// LIMPIADOR
            }
            break;

        case 7: /// estado (solo admin)
            if (clave == 1)   /// clave = nivel
            {
                gotoxy(3,8);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,8);
                printf("Eliminado: ");
                scanf("%i", &ADL[posLogueado].cliente.eliminado);
                gotoxy(3,8);
                puts("                                             ");   /// LIMPIADOR
            }
            break;

        case 8: // atras
            break;

        default:
            printf("\nOpci%cn inv%clida.", 162, 160);
            Sleep(1000);
            system("cls");
        }
        if (clave == 1)
        {
            persistirUsuario(ADL, validos, posLogueado);
        }
    }
    while (opcion >= 1 && opcion <= 7);
}

int menuPantallaModificarPerfil (stUsuario modificar, int clave)
{
    hidecursor(0);
    int opcion;

    mostrarRegistroUsuario(modificar, clave);

    gotoxy(3,9);
    printf("Atr%cs", 160);
    opcion = moverCursor(1,2,2,9,1);

    return opcion;
}

void persistirUsuario (stCelda ADL[], int validos, int posLogueado)
{
    FILE * archi = fopen(archiUsuarios, "r+b");
    int posEnArchi = (ADL[posLogueado].cliente.idUsuario) - 1;
    //printf("POS = %i !!! ", posEnArchi);
    //system("pause");

    if (archi)
    {
        fseek(archi, posEnArchi*(sizeof(stUsuario)), SEEK_SET);
        fwrite(&ADL[posLogueado].cliente, sizeof(stUsuario), 1, archi);
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }

}

stUsuario pantallaModificarUsuarioDesdeArchivo (stUsuario leer, int clave)
{
    system("cls");
    stUsuario escribir = leer;
    stUsuario aux;
    char passAux[17];
    int flag = 0;
    int opcion;

    do
    {
        opcion = menuPantallaModificarPerfil(escribir, 1);
        hidecursor(1);
        switch (opcion)
        {
        case 1: // nombre
            do      /// Verificador de NOMBRE DE USUARIO
            {
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,2);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,2);
                printf("Usuario: ");
                fflush(stdin);
                gets(aux.nombreUsuario);

                if (strcmpi(escribir.nombreUsuario, aux.nombreUsuario)!=0)
                {
                    flag = existeUsuario(aux, NULL);
                    if (flag == 1)
                    {
                        gotoxy(3,15);
                        printf("Usuario existente.");
                        Sleep(1000);
                    }
                    else
                        strcpy(escribir.nombreUsuario, aux.nombreUsuario);
                }
            }
            while (flag == 1);
            break;

        case 2: // pass
            do      /// Verificador de PASSWORD
            {
                gotoxy(3,3);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,3);
                printf("Contrase%ca: ", 164);
                fflush(stdin);
                ocultarPass(escribir.pass);

                gotoxy(3,14);
                printf("Confirmar Contrase%ca: ", 164);
                fflush(stdin);
                ocultarPass(passAux);

                if (strcmp(escribir.pass, passAux) != 0)
                {
                    gotoxy(3,15);
                    printf("Las contrase%cas no coinciden.", 164);
                    Sleep(1000);
                }
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,14);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,3);
                puts("                                             ");   /// LIMPIADOR
            }
            while (strcmp(escribir.pass, passAux) != 0);
            break;

        case 3: // genero
            do      /// Verificador de GENERO
            {
                gotoxy(3,4);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,4);
                printf("G%cnero (M/F/O): ", 130);
                fflush(stdin);
                escribir.genero = toupper(getchar());

                if ((escribir.genero != 'M') && (escribir.genero != 'F') && (escribir.genero != 'O'))
                {
                    gotoxy(3,15);
                    printf("Car%ccter inv%clido.", 160, 160);
                    Sleep(1000);
                }
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,4);
                puts("                                             ");   /// LIMPIADOR
            }
            while ((escribir.genero != 'M') && (escribir.genero != 'F') && (escribir.genero != 'O'));
            break;

        case 4: // nacimiento
            do      /// Verificador de EDAD
            {
                gotoxy(3,5);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,5);
                printf("A%co de nacimiento: ", 164);
                fflush(stdin);
                scanf("%i", &escribir.anioNacimiento);
                if ((2019 - escribir.anioNacimiento) < 16)
                {
                    gotoxy(3,15);
                    printf("Debes ser mayor de 16 a%cos para registrarte.", 164);
                    Sleep(1000);
                }
                gotoxy(3,15);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,5);
                puts("                                             ");   /// LIMPIADOR
            }
            while ((2019 - escribir.anioNacimiento) < 16);
            break;

        case 5: // pais
            gotoxy(3,6);
            puts("                                             ");   /// LIMPIADOR
            gotoxy(3,6);
            printf("Pa%cs: ", 161);
            fflush(stdin);
            gets(escribir.pais);
            gotoxy(3,6);
            puts("                                             ");   /// LIMPIADOR
            break;

        case 6:
            if (clave == 1)
            {
                gotoxy(3,7);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,7);
                printf("Nivel: ");
                fflush(stdin);
                scanf("%i", &escribir.nivel);
                gotoxy(3,6);
                puts("                                             ");   /// LIMPIADOR
            }
            break;

        case 7:
            if (clave == 1)
            {
                gotoxy(3,8);
                puts("                                             ");   /// LIMPIADOR
                gotoxy(3,8);
                printf("Eliminado: ");
                scanf("%i", &escribir.eliminado);
                gotoxy(3,8);
                puts("                                             ");   /// LIMPIADOR
            }
            break;

        case 8: // atras
            break;

        default:
            printf("\nOpci%cn inv%clida.", 162, 160);
            Sleep(1000);
            system("cls");
        }
    }
    while (opcion >= 1 && opcion <= 7);
    return escribir;
}

void modificarUsuarioDesdeArchivo (int idModificar)
{
    FILE * archi = fopen(archiUsuarios, "r+b");
    int posEnArchi = idModificar - 1;                               /// toma la pos del reg a modificar
    stUsuario leer;
    stUsuario escribir;

    if (archi)
    {
        fseek(archi, posEnArchi*(sizeof(stUsuario)), SEEK_SET);
        if (fread(&leer, sizeof(stUsuario), 1, archi) >0 )
        {
            escribir = pantallaModificarUsuarioDesdeArchivo(leer, 1);  /// envia el dato leido y recibe el modificado
            fseek(archi, (-1)*(sizeof(stUsuario)), SEEK_CUR);          /// vuelve el puntero donde estaba
            fwrite(&escribir, sizeof(stUsuario), 1, archi);            /// escribe el dato modificado en el archi
        }
        else
            printf("No se pudo leer del archivo.");
        fclose(archi);
    }
    else
    {
        puts("Error al abrir el archivo.");
        Sleep(1000);
        exit(0);
    }
}

void reproducirCancion(stCancion cancion)
{
    mostrarRegistroCancion(cancion, 0);
    // Timer pendiente.
}


///Función Reproductor
void reproducirPlayList(nodoListaCancion * listaUsuario)
{
    int opcion = 0;
    nodoListaCancion * reproduciendo = listaUsuario;
    reproducirCancion(reproduciendo->c));

    while ( opcion != 27)
    {
        opcion = subMenuReproductor();

        switch ( opcion )
        {
            case 37:
                if (reproduciendo->ante)
                    reproduciendo = reproduciendo->ante;
                else
                    while( reproduciendo->sig )
                        reproduciendo = reproduciendo->sig;

                reproducirCancion( reproduciendo->c );
            break;

            case 38:
                //Activar timer, siempre y cuando no este activado.
            break;

            case 39:
                reproducirCancion(listaUsuario)
            break;

        }
    }
}

int subMenuReproductor(vaskñvdavs///recibir lista para comprobar y no mostrar ante y sig)
{
    char opcion;
    gotoxy(60,18);
    printf("Anterior: %c",17 );
    gotoxy(60,19);
    printf("Siguiente%c",16);
    gotoxy(60,20);
    printf("Reproducir: %c",30);
    gotoxy(60,21);
    printf("Pausa: %c",31);

    while ( (int) opcion != 27 ) //Mientras no se apriete escape.
        if ( kbhit() ) //Si se aprieta una tecla,
            opcion = getch(); //Guarda el ascii de esa tecla en "opcion".

    return (int) opcion;
}
















