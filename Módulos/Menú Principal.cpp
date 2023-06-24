#include <iostream>  //Librería estándar
#include <conio.h>   //Incluida para el uso de la función getch();
#include <Windows.h> //Incluida para usar funciones como cambio de color de consola, limpieza de pantalla, etc.
#include <string>    //Incluida para uso de funciones que tienen string
// Constantes usadas para detectar teclas
#define TECLA_ARRIBA 119
#define TECLA_ABAJO 115
#define ENTER 13
using namespace std; // Agilizar tiempo de escritura
// Las funciones serán definidas en sus definiciones (abajo)
void gotoxy(int, int);
void color_cnsl(int, int);
template <class char_o_string>
void imprimir_franja(int, int, int, int, char_o_string);
template <class char_o_string>
void imprimir_diagonal(int, int, int, int, int, char_o_string);
void imprimir_linea_horizontal(int, int, int, int, int);
void imprimir_linea_vertical(int, int, int, int, int);
void menu_principal(string &);
bool comprobar_empleado(string &);
void Cargando();
template <class char_o_string>
void imprimir_texto(int, int, int, int, char_o_string);
void imprimir_cuadrilatero(int, int, int, int, int, int);
template <class char_o_string>
void imprimir_matriz_grafica(int, int, int[], int, int, int, int, char_o_string);
void ingresar_nombre(string &nom);
void menu_empleado(string);
void menu_cliente(string);
/*
En el caso de las matrices que se van a utilizar para imprimir "imágenes", se emplearán arreglos simples con una 
cantidad de elementos resultado de la multiplicación de las filas y columnas. Esta decisión se tomó con el propósito
de crear una única función que imprima las matrices. Sin embargo, al pasar una matriz a esta función, sería 
necesario definir la cantidad de columnas obligatoriamente, dado que las matrices a imprimir tienen diferentes
números de columnas. Por lo tanto, se optó por utilizar arreglos en los que el elemento [i][j] de una matriz 
corresponde al elemento [(i * columnas totales) + j] del arreglo.
Por ejemplo, si tenemos la siguiente matriz:
    01
    23
Esta matriz consta de 4 elementos. El elemento 2 se encuentra en la posición [1][0]. Ahora, si concatenamos todas 
las filas una después de la otra, obtendremos:
    0123
En este arreglo, el elemento 2 se encuentra en la posición [2], pero este 2 es equivalente a [(1 * 2) + 0]. De manera
similar, el elemento 3 sería [(1 * 2) + 1].
*/
// Matriz que contiene el Logo del estacionamiento (AE)
int Logo_Estacionamiento[6 * 15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                                    0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                                    0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};
// Matriz que contiene el número del grupo (8)
int Numero_de_grupo[6 * 7] = {0, 0, 0, 0, 0, 0, 0,
                              0, 1, 1, 1, 1, 1, 0,
                              1, 1, 0, 0, 0, 1, 1,
                              0, 1, 1, 1, 1, 1, 0,
                              1, 1, 0, 0, 0, 1, 1,
                              0, 1, 1, 1, 1, 1, 0};
int main()
{
    system("color F0");                       // Definimos el color de fondo predeterminado como blanco y color de letra negra
    getch();                                  // Pausa antes de ejecutar el programa, puede que se retire en el trabajo final
    Cargando();                               // LLamada a función Cargando()
    string nombre_principal = "";             // Inicialización del nombre, en este caso, el dato es provisional puesto que
                                              // debe salir de la estructura principal donde de guardarán los datos
    menu_principal(nombre_principal);         // LLamada a la función menu_principal(string)
    system("cls");                            // Limpieza de pantalla antes de la siguiente impresión
    if (comprobar_empleado(nombre_principal)) // La función comprobar_empleado() devuelte true si el nombre ingresado
                                              // corresponde a un empleado, esta parte deriva entre el menú para el
                                              // empleado o cliente
        menu_empleado(nombre_principal);
    else
        menu_cliente(nombre_principal);
    getch();
    return 0;
}
void menu_principal(string &nombre)
{
    /*
    En esta función se encuentran todas las impresiones del menú principal. Dicha función recibe el parámetro 
    "nombre" por referencia, ya que modificará su valor al ingresar el nombre que la persona introduzca a través 
    del teclado.
    */
    imprimir_franja(30, 86, 3, 3, "o");
    imprimir_franja(30, 40, 11, 11, "o");
    imprimir_diagonal(30, 39, 3, 3, 1, 'o');
    imprimir_diagonal(30, 85, 15, 15, 1, 'o');
    imprimir_diagonal(30, 37, 11, 3, 2, char(178));
    imprimir_diagonal(30, 83, 3, 15, 2, char(178));
    imprimir_diagonal(30, 35, 11, 3, 3, char(178));
    imprimir_diagonal(30, 81, 3, 15, 3, char(178));
    imprimir_texto(3, 2, 0, 11, "U");
    imprimir_texto(3, 3, 0, 11, "N");
    imprimir_texto(3, 4, 0, 11, "M");
    imprimir_texto(3, 5, 0, 11, "S");
    imprimir_texto(3, 6, 0, 11, "M");
    imprimir_texto(4, 2, 11, 0, "niversidad");
    imprimir_texto(4, 3, 11, 0, "acional");
    imprimir_texto(4, 4, 11, 0, "ayor de");
    imprimir_texto(4, 5, 11, 0, "an");
    imprimir_texto(4, 6, 11, 0, "arcos");
    imprimir_matriz_grafica(40, 10, Logo_Estacionamiento, 15, 6, 15, 15, "o");
    imprimir_texto(41, 17, 3, 15, "A P A R K E D");
    imprimir_matriz_grafica(98, 20, Numero_de_grupo, 7, 6, 8, 8, "o");
    imprimir_texto(99, 26, 15, 8, "Grupo");
    imprimir_cuadrilatero(85, 10, 32, 3, 15, 8);
    imprimir_texto(85, 10, 15, 8, char(201));
    imprimir_texto(116, 10, 15, 8, char(187));
    imprimir_texto(85, 12, 15, 8, char(200));
    imprimir_texto(116, 12, 15, 8, char(188)); 
    imprimir_texto(83, 14, 15, 8, "Estimado usuario, escriba su nombre");
    color_cnsl(15, 0);
    gotoxy(98, 11);
    ingresar_nombre(nombre);
}
void gotoxy(int coordx, int coordy)
{
    /*
    Función gotoxy, esta se encarga de manipular la posición del cursor en la pantalla, gracias a esto
    podemos desplazarnos por la pantalla e imprimir diferentes caracteres.
    */
    HANDLE hCon;                            // declaración de controlador llamado hCon
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); // asignando a hCon el controlador de la salida estándar
    COORD dwPos;                            // Declarando la variable dwPos de tipo estructura, la estructura COORD viene definida
                                            // en Windows.h, tiene 2 componentes la coordenada X y la coordenada Y.
    dwPos.X = coordx;                       // Asignación de la coordenada X según el valor ingresado
    dwPos.Y = coordy;                       // Asingnación de la coordenada Y según el valor ingreado
    SetConsoleCursorPosition(hCon, dwPos);  // Llamado a la función SetConsolCursosPosition(HANDLE, COORD)
                                            // esta recibe el controlador y las nuevas coordenadas para mover
                                            // el cursor
}
void color_cnsl(int colorfondo, int colortexto)
{
    /*
    Función color_cnsl, cambia el color del texto y fondo DE LA SIGUIENTE IMPRESIÓN, a diferencia de system("color XX") esta
    no cambia el color de toda la consola sino, el color de las siguientes impresiones. Por eso mismo se recomienda que una vez se
    haya terminado de usar la función, devolver al color inicial o predeterminado.
    Esta función recibe 2 parámetros, el color del fondo y el color del texto. Los códigos se mostrarán a continuación:
    0: Negro
    1: Azul
    2: Verde
    3: Aguamarina
    4: Rojo
    5: Púrpura
    6: Amarillo
    7: Blanco
    8: Gris
    9: Azul claro
    10: Verde claro
    11: Aguamarina claro
    12: Rojo claro
    13: Púrpura claro
    14: Amarillo claro
    15: Blanco brillante
    */
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);  // creación y asignación de la variable consoleHandle
                                                             // este es un controlador de pantalla al igual que el de
                                                             // la función gotoxy
    int colorAttributes = (colorfondo << 4) | colortexto;    // Se desplaza 4 bits a la izquierda (0010->00100000) al código
                                                             // del color de fondo y luego se le aumento el código
                                                             // del color de texto (00100000->0010(1010)) (1010 codificación
                                                             // del color de texto)
    SetConsoleTextAttribute(consoleHandle, colorAttributes); // Se llama a la función SetConsoleTextAttribute y se le pasa el
                                                             // controlador y el código nuevo de color
}
template <class char_o_string> // Este template se usa para que la función acepte tanto char como string en el mismo parámetro
void imprimir_franja(int filas, int inic_col, int fondo, int txt, char_o_string o)
{
    /*
    Función imprimir_franja, esta imprime una sucesión de carácteres de manera que en cada fila, la cantidad de elementos
    disminuya en 1:
    00000000
    0000000
    000000
    00000
    0000
    000
    00
    0
    La función recibe 5 parámetros, la cantidad de filas a imprimir, la columna desde donde se quiere inciar, el color de fondo,
    color de texto y el texto o carácter a imprimir (tener en cuenta que si se imprime un texto mayor a 1 caracter, este ocupará
    más espacio)
    */
    for (int fil_act = 0; fil_act < filas; fil_act++) // Bucle que irá cambiando a traves de las filas
    {
        for (int col_act = inic_col; col_act >= 0; col_act--) // Bucle que imprimira los elementos por fila
        {
            imprimir_texto(col_act, fil_act, fondo, txt, o); // LLamada a función imprimir_texto()
        }
        inic_col--; // Disminución en 1 del total de caracteres a imprimir por fila (esto genera el efecto cascada)
    }
}
template <class char_o_string> // Este template se usa para que la función acepte tanto char como string en el mismo parámetro
void imprimir_diagonal(int filas, int inic_col, int fondo, int txt, int aumento, char_o_string o)
{
    /*
    Función imprimir_diagonal, se encarga de imprmir una columna de caracteres, con el caracter de la siquiente fila desplazado
    en una posición (si se introduce un número positivo se desplaza a la izquierda y si es negativo hacia la derecha)
    Tiene 6 parámetros, el primero es el total de filas a imprimir, sigue la posición de la columna en la que se desea comenzar
    a imprimir, seguido del color de fondo y texto. Luego está el aumento que es el desplazamiento vertical y horizontal del
    siguiente caracter. Por último el texto o caracter a imprimir
    */
    for (int fil_act = 0; fil_act < filas; fil_act += abs(aumento)) // Bucle que va cambiando las filas y desplazando verticalmente
    {
        imprimir_texto(inic_col, fil_act, fondo, txt, o); // LLamada a la función imprimir_texto()
        inic_col -= aumento;                              // Desplazamiento horizontal
    }
}
void imprimir_linea_horizontal(int inic_X, int inic_Y, int tam, int fondo, int txt)
{
    /*
    Función imprimir_linea_horizontal, se encarga de imprimir serie de caracteres que simulan ser una línea horizontal
    Recibe 5 parámetros, la posición inicial en X, la posición inicial en Y, el tamaño de la línea, el color de fondo
    y el color de la línea.
    */
    gotoxy(inic_X, inic_Y);                         // Desplazamiento hasta la posición asignada
    color_cnsl(fondo, txt);                         // asignación de colores
    for (int col_act = 0; col_act < tam; col_act++) // Bucle que imprime todos los caracteres
    {
        cout << char(196); // Impresión de caracter línea "─" (ver código ASCII)
    }
}
void imprimir_linea_vertical(int inic_X, int inic_Y, int tam, int fondo, int txt)
{
    /*
    Función imprimir_linea_vertical, esta se encarga de imprimir una serie de caracteres de manera vertical, recibe 5 parámetros
    los 2 primeros corresponden a las coordenadas de origen, el tercero al tamaño y los 2 últimos al color del fondo y color de
    línea respectivamente
    */
    for (int aumento_fil = 0; aumento_fil < tam; aumento_fil++) // Bucle que cambia la fila
    {
        imprimir_texto(inic_X, inic_Y + aumento_fil, fondo, txt, char(179)); // Función imprimir_texto(), el segundo parámtro cambia
                                                                             // conforme aumentan las filas
    }
}
bool comprobar_empleado(string &cadena_nombre)
{
    /*
    Función comprobar_empleado, función que retorna true si se trata de un empleado y false si se trata de un cliente, tiene
    un parámetro, pasado por referencia, esta función tiene una utilidad extra ya que elimina la parte "EMP-" ingresada por un
    empleado al momento de introducir su nombre.
    */
    string cadena_comprob = ""; // Definimos una cadena que nos ayudará a comprobar si existe el prefijo "EMP-"
    for (int i = 0; i < 4; i++) // Bucle que guarda en cadena_comprob los 4 primeros carácteres de cadena_nombre
        cadena_comprob += cadena_nombre[i];
    if (cadena_comprob == "EMP-") // Utilidad secundaria de la función, si es verdadero, se ejcuta la parte de borrado
    { 
        cadena_nombre.erase(0, 4); // Con la función erase() proveniente de la librería string, eliminamos
                                                           // el prefijo "EMP-" del nombre, esta recibe 2 parámetros, el índice de inicio
                                                           // y la cantidad de caracteres a borrar.
    }
    return (cadena_comprob == "EMP-"); // La función es de tipo booleana por lo que retorna si hay o no el prefijo "EMP-"
}
void Cargando()
{
    /*
    Función Cargando, esta muestra la palabra, cargando... en pantalla y una barra que se va llevando en medio de esta
    */
    system("cls");                                          // Limpiamos la consola
    imprimir_texto(53, 10, 15, 0, "C A R G A N D O . . ."); // Usamos la función imprimir_texto para imprimir la palabra cargando
    for (int col_act1 = 0; col_act1 <= 79; col_act1++)      // Bucle encargado de generar 80 caracteres que simularán el fondo de la barra
    {
        imprimir_texto(20 + col_act1, 15, 8, 8, char(219)); 
    }
    for (int col_act2 = 0; col_act2 <= 79; col_act2++) // Bucle encargado de generar 80 caracteres que simularán la barra creciente
    {
        imprimir_texto(20 + col_act2, 15, 15, 0, char(219));
        Sleep(2 * 1000 / 80); // La función sleep() retrasa la ejecucuión de procedimientos por un tiempo que reciba en parámetros, este
                              // está en milisegundos, se le ingresa la cantidad de segundos que deseamos que dure el bucle, lo convertimos
                              // a milisegundos multiplicándolo por 1000 y lo dividimos entre las 80 impresiones que realizará el bucle
    }
    system("cls"); // Limpiamos pantalla para finalizar la carga
}
template <class char_o_string> // Este template se usa para que la función acepte tanto char como string en el mismo parámetro
void imprimir_texto(int coord_x, int coord_y, int fondo, int txt, char_o_string texto)
{
    /*
    Función imprimir_texto, se encarga de mostrar texto en pantalla, recibe 5 parámetros, los 2 primeros, son las coordenadas en
    donde se quiere imprimir, el tercero y cuarto pertencen al colo de fondo y texto respectivamente y el último es el caracter
    u oración que se desea mostrar
    */
    gotoxy(coord_x, coord_y); // función gotoxy()
    color_cnsl(fondo, txt);   // función color_cnsl()
    cout << texto;            // impresión del texto
}
void imprimir_cuadrilatero(int pos_x, int pos_y, int largo, int alto, int fondo, int txt)
{
    /*
    Función imprimir_cuadrilatero, se apoya de las funciones gotoxy e imprimir_linea (h y v) para generar un cuadrilátero de un tamaño
    personalizable. Consta de 6 parámetros, los 2 primeros corresponden a la posición en la que se desea realizar el cuadrilátero, los
    dos siguientes corresponden a las dimensiones, y los 2 últimos corresponden a los colores de la impresión
    */
    gotoxy(pos_x, pos_y);
    cout << char(218);                                                  // imprime "┌"
    imprimir_linea_horizontal(pos_x + 1, pos_y, largo - 2, fondo, txt); // El caracter que imprime es "─"
    gotoxy(pos_x + largo - 1, pos_y);
    cout << char(191);                                               // imprime "┐"
    imprimir_linea_vertical(pos_x, pos_y + 1, alto - 2, fondo, txt); // El caracter que imprime es "│"
    gotoxy(pos_x, pos_y + alto - 1);
    cout << char(192); // imprime "└"
    imprimir_linea_horizontal(pos_x + 1, pos_y + 2, largo - 2, fondo, txt);
    gotoxy(pos_x + largo - 1, pos_y + alto - 1);
    cout << char(217); // imprime "┘"
    imprimir_linea_vertical(pos_x + largo - 1, pos_y + 1, alto - 2, fondo, txt);
}
template <class char_o_string> // Este template se usa para que la función acepte tanto char como string en el mismo parámetro
void imprimir_matriz_grafica(int pos_x, int pos_y, int m[], int largo, int alto, int fondo, int txt, char_o_string o)
{
    /*
    Función imprimir_matriz_grafica, esta se encarga de imprimir un *ARREGLO* que sea construido con la finalidad de usarse como matriz (esto
    se explica al inicio del código). Esta función recibe 8 parámetros, los 2 primeros para la ubicación en el plano, el 3ro es el arreglo a
    imprimir, el 4to y 5to corresponden a las dimensiones de la figura, el 6to y 7mo corresponden a los colores para el fondo y texto respectivamente
    y el último parámetro corresponde al caracter que se desea imprimir.
    Cabe aclarar que esta función solo imprime arreglos conformador por 0's y 1's por lo que arreglos con más condiciones o propiedades requieren
    crear una función manual.
    */
    color_cnsl(fondo, txt);
    for (int fil_act = 0; fil_act < alto; fil_act++)
    {
        for (int col_act = 0; col_act < largo; col_act++) // Bucle clásico de impresión de matriz
        {
            gotoxy(pos_x + col_act, pos_y + fil_act); // El gotoxy ayuda a posicionarnos en el plano correctamente
            if (m[fil_act * largo + col_act] == 1)    // Se corrobora si hay un 1 en el espacio y si es así, se imprime el caracter ingresado
                cout << o;
        }
        cout << endl;
    }
}
void ingresar_nombre(string &nom)
{
    /*
    Función ingresar_nombre, esta se encarga de recibir el input del usuario, sin embargo, no deja que se accione la tecla de enter, con el fin de
    que no se desordene al momento de ingresar el imput.
    */
    bool band1 = true; // Variable booleana que ayudará a romper el bucle
    char c;            // Declaramos una variable tipo char que nos ayudará a comprobar si se pulsó la tecla enter
    while (band1)      // Definimos un bucle que se ejecute hasta que se cumpla cierta condición
    {
        if ((c = getch()) != ENTER) // Asignamos a c la tecla que se presionó en ese momento y si es diferente de ENTER (constante definida en la parte
                                    // superior), entonces se ejecutará la siguiente parte del código
        {
            if (c == '\b' && !nom.empty()) // Condicional para que cuando se presione el retroceso "\b" y el string no esté vacio, se ejecuta el siguiente
                                           // comando
            {
                cout << "\b \b"; // Retrocede un espacio el cursor con "\b" luego lo rellena con un espacio vacío " ", y luego retrocede nuevamente el cursor
                                 // esto genera el efecto de que se borró el caracter impreso
                nom.pop_back(); // Se elimina el ultimo caracter del string //ab 
            }
            else
            {
                cout << c;
                nom += c;
            }
        }
        else if (c == ENTER && !nom.empty()) // Si se presiona enter y el nombre no está vacío, entonce se rompe el bucle y se guarda la info ingresada.
        {
            band1 = false;
        }
    }
}
/*
Las siguientes son funciones provisionales y serán reemplazadas por su contrapartes finales una vez estén terminadas
*/
void menu_empleado(string nom)
{
    cout << "Hola " << nom << " (empleado)";
}
void menu_cliente(string nom)
{
    cout << "Hola " << nom;
}