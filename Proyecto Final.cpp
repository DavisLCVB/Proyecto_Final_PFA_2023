#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <ctype.h>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <string>
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13
#define TECLA_DERECHA 77
#define TECLA_IZQUIERDA 75
#define TECLA_w 119
#define TECLA_s 115
#define TECLA_a 97
#define TECLA_d 100
#define TECLA_W 87
#define TECLA_S 83
#define TECLA_A 65
#define TECLA_D 68

using namespace std;
struct retiro
{
    int posicionf;
    int posicionc;
    double pago;
    float tiempo_en_h;
};
struct VEHICULO
{
    string Placa;
    string Tipo;
    string Color;
};
struct PERSONA
{
    string Nombre;
    int Edad;
    bool Miembro;
};
struct crono
{
    int dia;
    int hora;
    int minu;
    int seg;
};

struct espacios
{
    int x;
    int y;
    int ocupado;
    crono momento[4]; // 0 es inicio 1 es final 2 es actual 3 es restante
};
struct CLIENTE
{
    PERSONA Persona;
    VEHICULO Vehiculo;
    espacios t;
} *Clientes_actuales = new CLIENTE[16], C_Temp;

struct senial
{
    int xpuntero;
    int ypuntero;
};

senial aux[4][4];

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
void ingresar_nombre(string &);
void leer_estacionamientos();
void menu_empleado(string);
void establecer_horario(int);
float hora_salida(int);
void estacionamiento_detallado();
void almacenar_cronometros();
void leer_cronometros();
void mostrar_crono(int k);
void mostrar_detalles(int i, int j);
void reloj();
void seleccionador(int tecla, int &lugar, int opciones, int botonaum, int botondism);
void dibujo();
int opciones_empleado();
void menu_cliente(string);
void ocultar_cursor();
void reiniciar_C_Temp();
void Ingreso_datos(string);
int Estacionar_o_retirar();
void mostrar_est();
void escoger_lugar();
void esc_y_mos_est();
void retiro_veh(retiro);
void voucher(retiro);
string menu_tipo_vehiculo();
void retiro_de_veh();
void Guardar_estacionamiento();
void Recuperar_estacionamiento();
void retirar(retiro &, bool &);
void Guardar_clientes(int);
void Limpiar_espacio(int);
int stoin(string);
float stofl(string);
void texto_centrado(int, int, string);
void comprobar_miembro(int, string);
void opciones_miembros();
void Registro_miembros();
void agregar_miembro();
int menu_miembros(const char[], const char *[], int);
void registro_miembros_archivo();
void crear_archivo_miembros();
string comprobar_miembro_duplicado(string);
bool coinciden_datos(int);
void inicializar_datos();
void crear_archivo_clientes();
// void guardar_historial(int, int, string, float);
void guardar_historial(int, float, float);
void imprimir_informe();
void leer_historial_e_imprimir();
void guardar_informe(float, int, string, string, string, string, string, string);
int pos_inic_x = 41;
int pos_inci_y = 2;
int Estacionamiento[15][36];
int Logo_Estacionamiento[6 * 15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                                    0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
                                    0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};
int Numero_de_grupo[6 * 7] = {0, 0, 0, 0, 0, 0, 0,
                              0, 1, 1, 1, 1, 1, 0,
                              1, 1, 0, 0, 0, 1, 1,
                              0, 1, 1, 1, 1, 1, 0,
                              1, 1, 0, 0, 0, 1, 1,
                              0, 1, 1, 1, 1, 1, 0};
int main()
{
    ocultar_cursor();
    system("color F0");
    inicializar_datos();
    leer_estacionamientos();
    Recuperar_estacionamiento();
    leer_cronometros();
    bool condicion = true;
    while (condicion)
    {
        Cargando();
        menu_principal(C_Temp.Persona.Nombre);
        system("cls");
        if (C_Temp.Persona.Nombre == "exit")
        {
            condicion = false;
            break;
        }
        if (comprobar_empleado(C_Temp.Persona.Nombre))
        {
            menu_empleado(C_Temp.Persona.Nombre);
        }
        else
        {
            menu_cliente(C_Temp.Persona.Nombre);
        }
        almacenar_cronometros();
        reiniciar_C_Temp();
    }
    delete[] Clientes_actuales;
    return 0;
}
void ocultar_cursor()
{
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
    cci.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
void Guardar_estacionamiento()
{
    ofstream estacionamiento_archivo;
    estacionamiento_archivo.open("Estacionamiento.txt", ios::out);
    if (estacionamiento_archivo.fail())
    {
        cout << "No se pudo abrir el archivo\n";
        return;
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 36; j++)
        {
            estacionamiento_archivo << Estacionamiento[i][j];
        }
        estacionamiento_archivo << endl;
    }
    estacionamiento_archivo.close();
}
void Recuperar_estacionamiento()
{
    ifstream estacionamiento_archivo;
    estacionamiento_archivo.open("Estacionamiento.txt", ios::in);
    if (estacionamiento_archivo.fail())
    {
        int nuevovalor[15][36] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                                  {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}};
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 36; j++)
            {
                Estacionamiento[i][j] = nuevovalor[i][j];
            }
        }
        Guardar_estacionamiento();
        return;
    }
    char a;
    int b;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 36; j++)
        {
            estacionamiento_archivo >> a;
            b = a - '0';
            if (b == 0 || b == 1 || b == 2 || b == 3)
                Estacionamiento[i][j] = b;
        }
    }
    estacionamiento_archivo.close();
}
void comprobar_miembro(int k, string nombre)
{
    ifstream archivos_miembros;
    archivos_miembros.open("miembros.txt", ios::in);
    if (archivos_miembros.fail())
    {
        crear_archivo_miembros();
        return;
    }
    string texto;
    while (!archivos_miembros.eof())
    {
        getline(archivos_miembros, texto);
        if (texto == nombre)
        {
            if (k > 0)
            {
                Clientes_actuales[k].Persona.Miembro = true;
            }
            else
            {
                C_Temp.Persona.Miembro = true;
            }
        }
    }
    archivos_miembros.close();
}
void crear_archivo_miembros()
{
    ofstream crear_archivo;
    crear_archivo.open("miembros.txt", ios::out);
    if (crear_archivo.fail())
    {
        cout << "No se pudo crear el archivo\n";
        return;
    }
    crear_archivo << endl;
    crear_archivo.close();
}
void inicializar_datos()
{
    for (int i = 0; i < 16; i++)
        Limpiar_espacio(i);
}
void menu_principal(string &nombre)
{
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
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = coordx;
    dwPos.Y = coordy;
    SetConsoleCursorPosition(hCon, dwPos);
}
void color_cnsl(int colorfondo, int colortexto)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttributes = (colorfondo << 4) | colortexto;
    SetConsoleTextAttribute(consoleHandle, colorAttributes);
}
template <class char_o_string>
void imprimir_franja(int filas, int inic_col, int fondo, int txt, char_o_string o)
{
    for (int fil_act = 0; fil_act < filas; fil_act++)
    {
        for (int col_act = inic_col; col_act >= 0; col_act--)
        {
            imprimir_texto(col_act, fil_act, fondo, txt, o);
        }
        inic_col--;
    }
}
template <class char_o_string>
void imprimir_diagonal(int filas, int inic_col, int fondo, int txt, int aumento, char_o_string o)
{
    for (int fil_act = 0; fil_act < filas; fil_act += abs(aumento))
    {
        imprimir_texto(inic_col, fil_act, fondo, txt, o);
        inic_col -= aumento;
    }
}
void imprimir_linea_horizontal(int inic_X, int inic_Y, int tam, int fondo, int txt)
{
    gotoxy(inic_X, inic_Y);
    color_cnsl(fondo, txt);
    for (int col_act = 0; col_act < tam; col_act++)
    {
        cout << char(196);
    }
}
void imprimir_linea_vertical(int inic_X, int inic_Y, int tam, int fondo, int txt)
{
    for (int aumento_fil = 0; aumento_fil < tam; aumento_fil++)
    {
        imprimir_texto(inic_X, inic_Y + aumento_fil, fondo, txt, char(179));
    }
}
bool comprobar_empleado(string &cadena_nombre)
{
    string cadena_comprob = "";
    for (int i = 0; i < 4; i++)
        cadena_comprob += cadena_nombre[i];
    if (cadena_comprob == "EMP-")
    {
        cadena_nombre.erase(0, 4);
    }
    return (cadena_comprob == "EMP-");
}

void Cargando()
{
    getch();
    system("cls");
    imprimir_texto(53, 10, 15, 0, "C A R G A N D O . . .");
    for (int col_act1 = 0; col_act1 <= 79; col_act1++)
    {
        imprimir_texto(20 + col_act1, 15, 8, 8, char(219));
    }
    for (int col_act2 = 0; col_act2 <= 79; col_act2++)
    {
        imprimir_texto(20 + col_act2, 15, 15, 0, char(219));
        Sleep(1 * 1000 / 80);
    }
    system("cls");
}
template <class char_o_string>
void imprimir_texto(int coord_x, int coord_y, int fondo, int txt, char_o_string texto)
{
    gotoxy(coord_x, coord_y);
    color_cnsl(fondo, txt);
    cout << texto;
}
void imprimir_cuadrilatero(int pos_x, int pos_y, int largo, int alto, int fondo, int txt)
{
    gotoxy(pos_x, pos_y);
    cout << char(218);
    imprimir_linea_horizontal(pos_x + 1, pos_y, largo - 2, fondo, txt);
    gotoxy(pos_x + largo - 1, pos_y);
    cout << char(191);
    imprimir_linea_vertical(pos_x, pos_y + 1, alto - 2, fondo, txt);
    gotoxy(pos_x, pos_y + alto - 1);
    cout << char(192);
    imprimir_linea_horizontal(pos_x + 1, pos_y + 2, largo - 2, fondo, txt);
    gotoxy(pos_x + largo - 1, pos_y + alto - 1);
    cout << char(217);
    imprimir_linea_vertical(pos_x + largo - 1, pos_y + 1, alto - 2, fondo, txt);
}
template <class char_o_string>
void imprimir_matriz_grafica(int pos_x, int pos_y, int m[], int largo, int alto, int fondo, int txt, char_o_string o)
{
    color_cnsl(fondo, txt);
    for (int fil_act = 0; fil_act < alto; fil_act++)
    {
        for (int col_act = 0; col_act < largo; col_act++)
        {
            gotoxy(pos_x + col_act, pos_y + fil_act);
            if (m[fil_act * largo + col_act] == 1)
                cout << o;
        }
        cout << endl;
    }
}
void ingresar_nombre(string &nom)
{
    bool band1 = true;
    char c;
    while (band1)
    {
        if ((c = getch()) != ENTER)
        {
            if (c == '\b' && !nom.empty())
            {
                cout << "\b \b";
                nom.pop_back();
            }
            else
            {
                cout << c;
                nom += c;
            }
        }
        else if (c == ENTER && !nom.empty())
        {
            band1 = false;
        }
    }
}
void reiniciar_C_Temp()
{
    C_Temp.Persona.Edad = 0;
    C_Temp.Persona.Miembro = false;
    C_Temp.Persona.Nombre = "";
    C_Temp.Vehiculo.Color = "";
    C_Temp.Vehiculo.Placa = "";
    C_Temp.Vehiculo.Tipo = "";
}
void menu_empleado(string nom)
{
    cout << "Hola " << nom << endl
         << endl;
    bool seguir = true;
    int opc = 0;
    while (seguir)
    {
        opc = opciones_empleado();
        switch (opc)
        {
        case 1:
            system("cls");
            imprimir_informe();
            break;
        case 2:
            estacionamiento_detallado();
            break;
        case 3:
            seguir = false;
            break;
        }
    }
}
int opciones_empleado()
{

    int eleccion;
    do
    {
        cout << "MENU DE OPCIONES PARA EL EMPLEADO" << endl;
        cout << "1. Generar informe" << endl;
        cout << "2. Mostrar estacionamiento detallado" << endl;
        cout << "3. Salir" << endl;
        cout << "DIGITE LA OPCION A EJECUTAR: ";
        cin >> eleccion;
        if (eleccion != 1 && eleccion != 2 && eleccion != 3)
        {
            cout << "\nOpcion invalida ;-;";
            Sleep(3000);
            system("cls");
        }
    } while (eleccion != 1 && eleccion != 2 && eleccion != 3);

    return eleccion;
}
void leer_estacionamientos()
{
    ifstream lectura_clientes;
    lectura_clientes.open("Clientes_actuales.txt", ios::in);
    if (lectura_clientes.fail())
    {
        crear_archivo_clientes();
        return;
    }
    string texto;
    for (int i = 0; i < 16; i++)
    {
        lectura_clientes >> Clientes_actuales[i].Persona.Edad;
        lectura_clientes.ignore();
        lectura_clientes >> Clientes_actuales[i].Persona.Miembro;
        lectura_clientes.ignore();
        getline(lectura_clientes, texto);
        Clientes_actuales[i].Persona.Nombre = texto;
        getline(lectura_clientes, texto);
        Clientes_actuales[i].Vehiculo.Color = texto;
        getline(lectura_clientes, texto);
        Clientes_actuales[i].Vehiculo.Placa = texto;
        getline(lectura_clientes, texto);
        Clientes_actuales[i].Vehiculo.Tipo = texto;
    }
}

void almacenar_cronometros()
{
    ofstream archivo("Cronometros.txt", ios::out);

    if (archivo.fail())
    {
        cout << "No se ha podido crear el archivo";
        return;
    }

    for (int i = 0; i < 16; i++)
    {
        // Momento inicial del reloj i
        archivo << Clientes_actuales[i].t.momento[0].seg << endl;
        archivo << Clientes_actuales[i].t.momento[0].minu << endl;
        archivo << Clientes_actuales[i].t.momento[0].hora << endl;
        archivo << Clientes_actuales[i].t.momento[0].dia << endl;
    }

    archivo.close();
}

void leer_cronometros()
{
    ifstream archivo("Cronometros.txt", ios::in);

    if (archivo.fail())
    {

        // archivo.close();

        for (int i = 0; i < 16; i++)
        {
            Clientes_actuales[i].t.momento[0].dia = 0;
            Clientes_actuales[i].t.momento[0].seg = 100;
            Clientes_actuales[i].t.momento[0].minu = 60;
            Clientes_actuales[i].t.momento[0].hora = 60;
        }
        almacenar_cronometros();
        leer_cronometros();

        return;
    }

    int i = 0;
    string linea;
    while (!archivo.eof())
    {
        getline(archivo, linea);
        if (linea == "")
        {
            break;
        }
        Clientes_actuales[i].t.momento[0].seg = stoin(linea);
        getline(archivo, linea);
        Clientes_actuales[i].t.momento[0].minu = stoin(linea);
        getline(archivo, linea);
        Clientes_actuales[i].t.momento[0].hora = stoin(linea);
        getline(archivo, linea);
        Clientes_actuales[i].t.momento[0].dia = stoin(linea);
        i++;
    }

    // ESTO SE DEBE HACER POR ARCHIVOS, POR LO CUAL AUN ES TEMPORAL
    // Establecemos las coordenadas (x,y) desde donde se colocaran los relojes
    int espaciadox = 41;
    int espaciadoy = -3; // Es -2 porque al escribir se da un aumento de "+4" en la funcion mostrar_crono()
                         // EN CASO SE QUIERAN MOSTRAR LOS RELOJOS COMPLETOS (INICIO, FINAL, ACTUAL, RESTANTE), COLOCAR 0

    // DETERMINAMOS LOS DATOS PARA CADA ESPACIO DE LOS 16 EXISTENTES
    for (int i = 0; i < 16; i++)
    {
        // coordenadas del reloj i
        Clientes_actuales[i].t.x = espaciadox;
        Clientes_actuales[i].t.y = espaciadoy;
        Clientes_actuales[i].t.ocupado = 0;
        // EN CASO LAS COORDENDAS X SOBREPASEN LOS 80, SE PASARA A LA SIGUIENTE LINEA
        if (espaciadox >= 94)
        {
            espaciadox = 41;
            espaciadoy += 7;
        }
        else
        { // CASO CONTRARIO SE AUMENTARA +22 PARA EL SIGUIENTE RELOJ i+1
            espaciadox += 21;
        }
    }

    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            aux[i][j] = {Clientes_actuales[k].t.x + 2, Clientes_actuales[k].t.y + 4};
            k++;
        }
    }

    archivo.close();
}

void establecer_horario(int k)
{
    // system("cls");
    time_t inicio = time(NULL);
    // Se crea una estructura tipo tm* (predefinida por libreria <time.c>
    tm *time = localtime(&inicio);

    // Asignamos las horas, minutos y segundos al momento inicial
    Clientes_actuales[k].t.momento[0].dia = time->tm_yday;
    Clientes_actuales[k].t.momento[0].hora = time->tm_hour;
    Clientes_actuales[k].t.momento[0].minu = time->tm_min;
    Clientes_actuales[k].t.momento[0].seg = time->tm_sec;

    // gotoxy(t[k].x,t[k].y+1);
    // cout<<"INICO: "<<t[k].momento[0].hora<<":"<<t[k].momento[0].minu<<":"<<t[k].momento[0].seg<<endl;
    // getch();
}
float hora_salida(int k)
{

    time_t final = time(NULL);
    // Se crea una estructura tipo tm* (predefinida por libreria <time.c>
    tm *time = localtime(&final);

    Clientes_actuales[k].t.momento[1].dia = time->tm_yday;
    Clientes_actuales[k].t.momento[1].hora = time->tm_hour;
    Clientes_actuales[k].t.momento[1].minu = time->tm_min;
    Clientes_actuales[k].t.momento[1].seg = time->tm_sec;

    int total_final = Clientes_actuales[k].t.momento[1].dia * 86400 + Clientes_actuales[k].t.momento[1].hora * 3600 + Clientes_actuales[k].t.momento[1].minu * 60 + Clientes_actuales[k].t.momento[1].seg;
    int total_inicio = Clientes_actuales[k].t.momento[0].dia * 86400 + Clientes_actuales[k].t.momento[0].hora * 3600 + Clientes_actuales[k].t.momento[0].minu * 60 + Clientes_actuales[k].t.momento[0].seg;

    float diferencia = total_final - total_inicio;

    Clientes_actuales[k].t.momento[3].hora = diferencia / 3600;
    Clientes_actuales[k].t.momento[3].minu = (diferencia - Clientes_actuales[k].t.momento[3].hora * 3600) / 60;
    Clientes_actuales[k].t.momento[3].seg = diferencia - (Clientes_actuales[k].t.momento[3].hora * 3600 + Clientes_actuales[k].t.momento[3].minu * 60);

    Clientes_actuales[k].t.momento[0].seg = 100;

    return diferencia / 3600;
}

void estacionamiento_detallado()
{
    system("cls");
    dibujo();
    reloj();
    system("cls");
}
void dibujo()
{

    // LINEAS VERTICALES
    // LA PRIMERA SERA EN X= 41 Y = 2
    int x = 55, y = 1;

    // El primer for es para escribir en un aumento y+=1 23 veces una serie ' |        |        | '
    for (int i = 0; i < 27; i++)
    {
        // El segundo for escribira la serie determinada de '|' cada 21 espacios en x solo 3 veces
        for (int j = 0; j < 3; j++)
        {
            gotoxy(x, y);
            cout << "|";
            x += 21;
        }
        // Pasamos a la siguiente linea
        x = 55;
        y += 1;
    }

    // LINEAS HORIZONTALES
    x = 33;
    y = 7;

    // Primer for escribira el 'salto' a la siguiente linea con un y+=6
    for (int i = 0; i < 3; i++)
    {
        // El segundo for escribira '--' 83 veces desdes la posicion x = 21
        for (int j = 0; j < 83; j++)
        {
            gotoxy(x, y);
            cout << "--";
            x++;
        }
        x = 33;
        y += 7;
    }
}
void reloj()
{

    int columna = 0;
    int fila = 0;
    int tecla;
    bool cambio = true;
    gotoxy(aux[fila][columna].xpuntero, aux[fila][columna].ypuntero);
    cout << char(223) << char(223) << char(223) << char(223);

    // MIENTRAS NO SE PRESIONE ENTER SE MOSTRARAN LOS CRONOMETROS
    do
    {
        // SE MUESTRAN LOS 16 CRONOMETROS
        for (int i = 0; i < 16; i++)
        {
            mostrar_crono(i);
        }

        // TOMAMOS LOS TICS DESDE QUE SE INICIO EL PROGRAMA
        clock_t inicio = clock();

        // SI DURANTE 0.1 SEGUNDOS NO SE HA DETECTADO EL ENTER, SE SEGUIRAN MOSTRANDO LOS RELOJES

        while ((clock() - inicio) / CLOCKS_PER_SEC < 0.1)
        {
            if (cambio == true)
            {
                mostrar_detalles(fila, columna);
                cambio = false;
            }

            if (kbhit())
            {
                tecla = getch();
                if (tecla != ENTER && (tecla == TECLA_ARRIBA || tecla == TECLA_ABAJO || tecla == TECLA_DERECHA || tecla == TECLA_IZQUIERDA))
                {
                    gotoxy(aux[fila][columna].xpuntero, aux[fila][columna].ypuntero);
                    cout << "    ";
                    gotoxy(0, 0);
                    seleccionador(tecla, fila, 4, TECLA_ARRIBA, TECLA_ABAJO);
                    cout << fila;
                    gotoxy(1, 0);
                    seleccionador(tecla, columna, 4, TECLA_IZQUIERDA, TECLA_DERECHA);
                    cout << columna;
                    gotoxy(aux[fila][columna].xpuntero, aux[fila][columna].ypuntero);
                    cout << char(223) << char(223) << char(223) << char(223);
                    cambio = true;
                    // mostrar_detalles(fila,columna);
                }
            }
        }
    } while (tecla != ENTER);
}

void seleccionador(int tecla, int &lugar, int opciones, int botonaum, int botondism)
{
    string punto = "----";

    if (tecla == botonaum)
    {
        if (lugar == 0)
        {
            // gotoxy(x, y); cout<<"  ";
            lugar = opciones - 1;
        }
        else if (lugar > 0 && lugar <= opciones - 1)
        {
            // gotoxy(x,y); cout<<"  ";
            lugar--;
        }
    }
    else if (tecla == botondism)
    {
        if (lugar == opciones - 1)
        {
            // gotoxy(x, y); cout<<"  ";
            lugar = 0;
        }
        else if (lugar >= 0 && lugar < opciones - 1)
        {
            // gotoxy(x,y); cout<<"  ";
            lugar++;
        }
    }
}

/*

    0	1	2	3
0	0	1	2	3
1	4	5	6	7
2	8	9	10	11
3	12	13	14	15

*/

void mostrar_detalles(int i, int j)
{
    int x = 0, y = 3;

    Sleep(1);

    for (int i = 0; i < 20; i++)
    {
        gotoxy(x, y + i);
        cout << "                          ";
    }

    if (Clientes_actuales[i * 4 + j].t.ocupado != 1)
    {

        texto_centrado(36, y + 6, "NO SE");
        texto_centrado(36, y + 9, "ENCUENTRA");
        texto_centrado(36, y + 12, "NINGUN CARRO");
    }
    else
    {
        texto_centrado(36, y + 5, "CARRO TIPO:");
        texto_centrado(36, y + 6, Clientes_actuales[i * 4 + j].Vehiculo.Tipo);

        texto_centrado(36, y + 9, "COLOR DEL CARRO:");
        texto_centrado(36, y + 10, Clientes_actuales[i * 4 + j].Vehiculo.Color);

        texto_centrado(36, y + 13, "PLACA DEL CARRO:");
        texto_centrado(36, y + 14, Clientes_actuales[i * 4 + j].Vehiculo.Placa);
    }
}

void mostrar_crono(int k)
{

    int total_act = 0, total_inicio = 0, diferencia = 0;
    // MOSTRAR DETALLES DEL INICIO Y FINAL
    // gotoxy(t[k].x,t[k].y);
    // cout<<"INICO: "<<t[k].momento[0].hora<<":"<<t[k].momento[0].minu<<":"<<t[k].momento[0].seg<<endl;
    // gotoxy(t[k].x,t[k].y+1);
    // cout<<"Final: "<<t[k].momento[1].hora<<":"<<t[k].momento[1].minu<<":"<<t[k].momento[1].seg<<endl;

    // CALCULAMOS EN SEGUNDOS LA CANTIDAD DE SEGUNDOS DESDE INICIADO EL DIA EN QUE SE RETIRARA EL CARRO
    total_inicio = Clientes_actuales[k].t.momento[0].dia * 86400 + Clientes_actuales[k].t.momento[0].hora * 3600 + Clientes_actuales[k].t.momento[0].minu * 60 + Clientes_actuales[k].t.momento[0].seg;
    // Las siguientes funciones toman el tiempo actual del sistema (pc)
    // Almacenan el tiempo actual en una varible tipo time_t
    time_t now = time(NULL);
    // Se crea una estructura tipo tm* (predefinida por libreria <time.c>
    tm *act = localtime(&now);

    // ALMACENAMOS LAS HORAS, MINUTOS Y SEGUNDOS EN EL VECTOR RESPECTIVO
    Clientes_actuales[k].t.momento[2].dia = act->tm_yday;
    Clientes_actuales[k].t.momento[2].minu = act->tm_min;
    Clientes_actuales[k].t.momento[2].seg = act->tm_sec;
    Clientes_actuales[k].t.momento[2].hora = act->tm_hour;

    // MOSTRAR DETALLES DE LA HORA ACTUAL Y LOS CALCULOS
    // gotoxy(t[k].x,t[k].y+2);
    // cout<<"Actual: "<<t[k].momento[2].hora<<":"<<t[k].momento[2].minu<<":"<<t[k].momento[2].seg<<endl;

    // Se calcula la cantidad de segundos que pasaron desde que se inicio el dia hasta la actualidad
    total_act = Clientes_actuales[k].t.momento[2].dia * 86400 + Clientes_actuales[k].t.momento[2].hora * 3600 + Clientes_actuales[k].t.momento[2].minu * 60 + Clientes_actuales[k].t.momento[2].seg;
    // gotoxy(t[k].x,t[k].y+3);
    // cout<<total_fin<<" "<<total_act;

    // SE HACEN LOS CALCULOS PARA DETERMINAR LA HORA, MINUTO Y SEGUNDOS RESTANTES
    diferencia = total_act - total_inicio;
    Clientes_actuales[k].t.momento[3].hora = diferencia / 3600;
    Clientes_actuales[k].t.momento[3].minu = (diferencia - Clientes_actuales[k].t.momento[3].hora * 3600) / 60;
    Clientes_actuales[k].t.momento[3].seg = diferencia - (Clientes_actuales[k].t.momento[3].hora * 3600 + Clientes_actuales[k].t.momento[3].minu * 60);

    // SI AUN EXISTE TIEMPO RESTANTE
    if (Clientes_actuales[k].t.momento[0].seg != 100)
    {
        Clientes_actuales[k].t.ocupado = 1;
        // SE MOSTRARAN LAS HORAS, MINUTOS Y SEGUNDOS
        gotoxy(Clientes_actuales[k].t.x, Clientes_actuales[k].t.y + 5);
        // cout<<"Tiempo restante: ";
        // gotoxy(t[k].x+17,t[k].y+4);

        cout << "        ";
        gotoxy(Clientes_actuales[k].t.x, Clientes_actuales[k].t.y + 5);
        // gotoxy(t[k].x+17,t[k].y+4);
        if (Clientes_actuales[k].t.momento[3].hora < 10)
            cout << "0";
        cout << Clientes_actuales[k].t.momento[3].hora << ":";
        if (Clientes_actuales[k].t.momento[3].minu < 10)
            cout << "0";
        cout << Clientes_actuales[k].t.momento[3].minu << ":";
        if (Clientes_actuales[k].t.momento[3].seg < 10)
            cout << "0";
        cout << Clientes_actuales[k].t.momento[3].seg;

        gotoxy(Clientes_actuales[k].t.x - 6, Clientes_actuales[k].t.y + 6);
        cout << "        ______";
        gotoxy(Clientes_actuales[k].t.x - 6, Clientes_actuales[k].t.y + 7);
        cout << "   ___/___|___" << char(92) << "___";
        gotoxy(Clientes_actuales[k].t.x - 6, Clientes_actuales[k].t.y + 8);
        cout << " (_---_______ _---_)";
        gotoxy(Clientes_actuales[k].t.x - 6, Clientes_actuales[k].t.y + 9);
        cout << "   (o)         (o)";
    }
    else
    {
        Clientes_actuales[k].t.ocupado = 0;
        gotoxy(Clientes_actuales[k].t.x, Clientes_actuales[k].t.y + 5);
        cout << "00:00:00";
    }
}

void menu_cliente(string nom)
{
    int opcion;
    Ingreso_datos(nom);
    bool condicion_2 = true;
    while (condicion_2)
    {
        opcion = Estacionar_o_retirar();
        switch (opcion)
        {
        case 1:
            system("cls");
            esc_y_mos_est();
            condicion_2 = false;
            break;
        case 2:
            retiro_de_veh();
            condicion_2 = false;
            break;
        case 3:
            system("cls");
            Recuperar_estacionamiento();
            mostrar_est();
            getch();
            break;
        case 4:
            system("cls");
            opciones_miembros();
            break;
        case 5:
            condicion_2 = false;
            break;
        default:
            break;
        }
    }
}
int Estacionar_o_retirar()
{
    int op;
    system("cls");
    cout << char(168) << "Que desea hacer?:\n";
    cout << "1. Estacionar mi veh" << char(161) << "culo\n";
    cout << "2. Retirar mi veh" << char(161) << "culo\n";
    cout << "3. Ver estacionamiento\n";
    cout << "4. Volverse miembro\n";
    cout << "5. Atras\n";
    cout << "\n>>";
    while (!(cin >> op) || (op < 1) || (op > 5))
    {
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Opci" << char(162) << "n inv" << char(160) << "lida\n>>";
    }
    return op;
}
void Ingreso_datos(string nom)
{
    comprobar_miembro(0, nom);
    cout << "Hola " << nom;
    if (C_Temp.Persona.Miembro)
        cout << " (miembro)\n";
    else
        cout << endl;
    bool datos_correctos = false;
    while (!datos_correctos)
    {
        string opt;
        cout << "\nIngresa tus datos, por favor:\n";
        cout << "Edad:\n>>";
        while (!(cin >> C_Temp.Persona.Edad) || (C_Temp.Persona.Edad <= 0))
        {
            cin.clear();
            cin.ignore(123, '\n');
            cout << "Edad inv" << char(160) << "lida\n>>";
        }
        cout << "Ahora, brindanos informaci" << char(162) << "n sobre el veh" << char(161) << "culo que deseas estacionar\n";
        cout << "Ingresa la Placa de tu veh" << char(161) << "culo\n>>";
        cin >> C_Temp.Vehiculo.Placa;
        cout << "Ingresa el color de tu veh" << char(161) << "culo\n>>";
        cin >> C_Temp.Vehiculo.Color;
        cout << "Selecciona el tipo de veh" << char(161) << "culo\n";
        C_Temp.Vehiculo.Tipo = menu_tipo_vehiculo();
        system("cls");
        cout << "Nombre: " << C_Temp.Persona.Nombre << endl;
        cout << "Edad: " << C_Temp.Persona.Edad << endl;
        cout << "Veh" << char(161) << "culo:\n";
        cout << "   - Placa: " << C_Temp.Vehiculo.Placa << endl;
        cout << "   - Color: " << C_Temp.Vehiculo.Color << endl;
        cout << "   - Tipo: " << C_Temp.Vehiculo.Tipo << endl;
        cout << "\n"
             << char(168) << "Los datos son correctos? (si/no):\n>>";
        cin >> opt;
        for (char &c : opt)
        {
            c = toupper(c);
        }
        if (opt == "SI")
        {
            datos_correctos = true;
        }
        else
        {
            cout << "Reiniciando...";
            Sleep(1000);
        }
        system("cls");
    }
}
string menu_tipo_vehiculo()
{
    int op;
    cout << "1. Pesado\n";
    cout << "2. Liviano\n";
    cout << "3. Motocicleta\n";
    cout << "Escoja una opci" << char(162) << "n\n>>";
    while (!(cin >> op) || ((op > 3) || (op < 1)))
    {
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Opci" << char(162) << "n inv" << char(160) << "lida\n>>";
    }
    switch (op)
    {
    case 1:
        return "Pesado";
        break;
    case 2:
        return "Liviano";
        break;
    case 3:
        return "Motocicleta";
        break;
    default:
        return "";
        break;
    }
}
void mostrar_est()
{
    gotoxy(0, 0);
    for (int iterador_x = 0; iterador_x < 15; iterador_x++)
    {
        for (int iterador_y = 0; iterador_y < 36; iterador_y++)
        {
            gotoxy(pos_inic_x + iterador_y, pos_inci_y + iterador_x);
            if (Estacionamiento[iterador_x][iterador_y] == 0)
            {
                color_cnsl(0, 0);
                cout << 'o';
                color_cnsl(15, 0);
            }
            if (Estacionamiento[iterador_x][iterador_y] == 1)
                cout << " ";
            if (Estacionamiento[iterador_x][iterador_y] == 2)
                cout << char(178);
            if (Estacionamiento[iterador_x][iterador_y] == 3)
                cout << '#';
        }
        cout << endl;
    }
}
void escoger_lugar()
{
    system("cls");
    mostrar_est();
    bool condicion_fin_elecc = true;
    int incremento_x = 6, incremento_y = 4;
    int k;
    while (condicion_fin_elecc)
    {
        gotoxy(pos_inic_x + incremento_x, pos_inci_y + incremento_y);

        if (Estacionamiento[incremento_y][incremento_x] == 3)
            color_cnsl(9, 15);

        else
            color_cnsl(9, 9);
        cout << "####";
        color_cnsl(15, 0);
        int tecla = getch();
        if (tecla == TECLA_DERECHA || tecla == TECLA_d || tecla == TECLA_D)
        {
            if (incremento_x == 6 || incremento_x == 20)
            {
                incremento_x += 6;
            }
            else if (incremento_x == 12)
            {
                incremento_x += 8;
            }
            else if (incremento_x == 26)
            {
                incremento_x = 6;
            }
        }
        if (tecla == TECLA_IZQUIERDA || tecla == TECLA_a || tecla == TECLA_A)
        {
            if (incremento_x == 12 || incremento_x == 26)
            {
                incremento_x -= 6;
            }
            else if (incremento_x == 20)
            {
                incremento_x -= 8;
            }
            else if (incremento_x == 6)
            {
                incremento_x = 26;
            }
        }
        if (tecla == TECLA_ABAJO || tecla == TECLA_S || tecla == TECLA_s)
        {
            if (incremento_y != 12)
            {
                incremento_y += 2;
            }
            if (incremento_y == 12)
            {
                incremento_y = 4;
            }
        }
        if (tecla == TECLA_ARRIBA || tecla == TECLA_w || tecla == TECLA_W)
        {
            if (incremento_y != 2)
            {
                incremento_y -= 2;
            }
            if (incremento_y == 2)
            {
                incremento_y = 10;
            }
        }
        if (tecla == ENTER)
        {
            Estacionamiento[incremento_y][incremento_x] = 3;
            Estacionamiento[incremento_y][incremento_x + 1] = 3;
            Estacionamiento[incremento_y][incremento_x + 2] = 3;
            Estacionamiento[incremento_y][incremento_x + 3] = 3;
            if (incremento_x <= 12)
            {
                int i = (incremento_x - 6) / 6;
                int j = (incremento_y - 4) / 2;
                establecer_horario(j * 4 + i);
                k = j * 4 + i;
            }
            else if (incremento_x >= 20)
            {
                int i = (incremento_x - 20) / 6;
                int j = (incremento_y - 4) / 2;
                establecer_horario(j * 4 + i + 2);
                k = j * 4 + i + 2;
            }

            condicion_fin_elecc = false;
        }
        mostrar_est();
    }
    Guardar_clientes(k);
    Guardar_estacionamiento();
    reiniciar_C_Temp();
}
void esc_y_mos_est()
{
    mostrar_est();
    escoger_lugar();
    mostrar_est();
}
void retirar(retiro &p, bool &retiro)
{
    system("cls");
    Recuperar_estacionamiento();
    mostrar_est();
    bool condicion_fin_elecc = true;
    int incremento_x = 6, incremento_y = 4;
    int k;
    while (condicion_fin_elecc)
    {
        gotoxy(pos_inic_x + incremento_x, pos_inci_y + incremento_y);
        if (Estacionamiento[incremento_y][incremento_x] == 3)
            color_cnsl(9, 15);

        else
            color_cnsl(9, 9);
        cout << "####";
        color_cnsl(15, 0);
        int tecla = getch();
        if (tecla == TECLA_DERECHA || tecla == TECLA_d || tecla == TECLA_D)
        {
            if (incremento_x == 6 || incremento_x == 20)
            {
                incremento_x += 6;
            }
            else if (incremento_x == 12)
            {
                incremento_x += 8;
            }
            else if (incremento_x == 26)
            {
                incremento_x = 6;
            }
        }
        if (tecla == TECLA_IZQUIERDA || tecla == TECLA_a || tecla == TECLA_A)
        {
            if (incremento_x == 12 || incremento_x == 26)
            {
                incremento_x -= 6;
            }
            else if (incremento_x == 20)
            {
                incremento_x -= 8;
            }
            else if (incremento_x == 6)
            {
                incremento_x = 26;
            }
        }
        if (tecla == TECLA_ABAJO || tecla == TECLA_S || tecla == TECLA_s)
        {
            if (incremento_y != 12)
            {
                incremento_y += 2;
            }
            if (incremento_y == 12)
            {
                incremento_y = 4;
            }
        }
        if (tecla == TECLA_ARRIBA || tecla == TECLA_w || tecla == TECLA_W)
        {
            if (incremento_y != 2)
            {
                incremento_y -= 2;
            }
            if (incremento_y == 2)
            {
                incremento_y = 10;
            }
        }
        if (tecla == ENTER)
        {
            if (incremento_x <= 12)
            {
                int i = (incremento_x - 6) / 6;
                int j = (incremento_y - 4) / 2;
                k = j * 4 + i;
            }
            else if (incremento_x >= 20)
            {
                int i = (incremento_x - 20) / 6;
                int j = (incremento_y - 4) / 2;
                k = j * 4 + i + 2;
            }
            if (coinciden_datos(k))
            {
                Estacionamiento[incremento_y][incremento_x] = 1;
                Estacionamiento[incremento_y][incremento_x + 1] = 1;
                Estacionamiento[incremento_y][incremento_x + 2] = 1;
                Estacionamiento[incremento_y][incremento_x + 3] = 1;
                retiro = true;
            }
            condicion_fin_elecc = false;
        }
        mostrar_est();
    }
    if (retiro)
    {
        p.posicionc = (k) % 4;
        p.posicionf = (k) / 4;
        Guardar_estacionamiento();
    }
    else
    {
        system("cls");
        gotoxy(20, 14);
        cout << "El veh" << char(161) << "culo no le corresponde o el espacio se encuentra vac" << char(161) << "o\n";
        getch();
    }
}
bool coinciden_datos(int k)
{
    if (C_Temp.Persona.Edad != Clientes_actuales[k].Persona.Edad)
        return false;
    if (C_Temp.Persona.Nombre != Clientes_actuales[k].Persona.Nombre)
        return false;
    if (C_Temp.Vehiculo.Color != Clientes_actuales[k].Vehiculo.Color)
        return false;
    if (C_Temp.Vehiculo.Placa != Clientes_actuales[k].Vehiculo.Placa)
        return false;
    if (C_Temp.Vehiculo.Tipo != Clientes_actuales[k].Vehiculo.Tipo)
        return false;
    return true;
}
void Guardar_clientes(int k)
{
    Clientes_actuales[k].Persona.Edad = C_Temp.Persona.Edad;
    Clientes_actuales[k].Persona.Miembro = C_Temp.Persona.Miembro;
    Clientes_actuales[k].Persona.Nombre = C_Temp.Persona.Nombre;
    Clientes_actuales[k].Vehiculo.Color = C_Temp.Vehiculo.Color;
    Clientes_actuales[k].Vehiculo.Placa = C_Temp.Vehiculo.Placa;
    Clientes_actuales[k].Vehiculo.Tipo = C_Temp.Vehiculo.Tipo;
    ofstream archivo_clientes;
    archivo_clientes.open("Clientes_actuales.txt", ios::out);
    if (archivo_clientes.fail())
    {
        cout << "No se pudo abrir el archivo\n";
        return;
    }
    for (int i = 0; i < 16; i++)
    {
        archivo_clientes << Clientes_actuales[i].Persona.Edad << endl;
        archivo_clientes << Clientes_actuales[i].Persona.Miembro << endl;
        archivo_clientes << Clientes_actuales[i].Persona.Nombre << endl;
        archivo_clientes << Clientes_actuales[i].Vehiculo.Color << endl;
        archivo_clientes << Clientes_actuales[i].Vehiculo.Placa << endl;
        archivo_clientes << Clientes_actuales[i].Vehiculo.Tipo << endl;
    }
    archivo_clientes.close();
}
void crear_archivo_clientes()
{
    ofstream archivo_clientes;
    archivo_clientes.open("Clientes_actuales.txt", ios::out);
    if (archivo_clientes.fail())
    {
        cout << "No se pudo abrir el archivo\n";
        return;
    }
    for (int i = 0; i < 16; i++)
    {
        archivo_clientes << Clientes_actuales[i].Persona.Edad << endl;
        archivo_clientes << Clientes_actuales[i].Persona.Miembro << endl;
        archivo_clientes << Clientes_actuales[i].Persona.Nombre << endl;
        archivo_clientes << Clientes_actuales[i].Vehiculo.Color << endl;
        archivo_clientes << Clientes_actuales[i].Vehiculo.Placa << endl;
        archivo_clientes << Clientes_actuales[i].Vehiculo.Tipo << endl;
    }
    archivo_clientes.close();
}
void retiro_de_veh()
{
    system("cls");
    retiro p;
    bool ret = false;
    bool finalizacion = false;
    while (!finalizacion)
    {
        retirar(p, ret);
        finalizacion = true;
        if (ret)
        {
            Guardar_estacionamiento();
            Sleep(1500);
            system("cls");
        }
    }
    if (ret)
    {
        Sleep(500);
        voucher(p);
    }
}
void voucher(retiro p)
{
    p.tiempo_en_h = hora_salida(p.posicionf * 4 + p.posicionc);
    int k = p.posicionf * 4 + p.posicionc;
    // cout << "digite el tiempo en horas a establecerse: ";
    // cin >> p.tiempo_en_h;
    string tiempo;
    tiempo = to_string(Clientes_actuales[k].t.momento[3].hora) + ":" + to_string(Clientes_actuales[k].t.momento[3].minu) + ":" + to_string(Clientes_actuales[k].t.momento[3].seg);
    cout << "\n";
    cout << "\t\tImprimiendo voucher " << endl;
    cout << "Tiempo estacionado: " << tiempo << endl;
    cout << "Datos del cliente: " << Clientes_actuales[k].Persona.Nombre << endl;
    cout << "Placa de vehiculo: " << Clientes_actuales[k].Vehiculo.Placa << endl;
    // cout<<"Tiempo total de servicio: "<<
    p.pago = 750 * p.tiempo_en_h;
    float aux = p.pago * 1000;
    int aux1 = aux;
    aux = aux1;
    p.pago = aux / 1000;
    cout << "\nTotal: " << p.pago;

    cout << "\nDescuento: ";
    if (Clientes_actuales[k].Persona.Miembro)
    {
        cout << "S/." << p.pago * 0.25;
    }
    else
    {
        cout << "S/.0";
    }
    if (Clientes_actuales[k].Persona.Miembro)
    {
        p.pago = p.pago * 0.75;
    }
    cout << "\nTotal a pagar: S/." << p.pago;
    // guardar_historial(k, p.pago, tiempo, p.tiempo_en_h);
    guardar_historial(k, p.pago, p.tiempo_en_h);
    reiniciar_C_Temp();
    Limpiar_espacio(k);
    Guardar_clientes(k);
    getch();
}
void Limpiar_espacio(int k)
{
    Clientes_actuales[k].Persona.Edad = 0;
    Clientes_actuales[k].Persona.Miembro = false;
    Clientes_actuales[k].Persona.Nombre = "";
    Clientes_actuales[k].Vehiculo.Color = "";
    Clientes_actuales[k].Vehiculo.Placa = "";
    Clientes_actuales[k].Vehiculo.Tipo = "";
}

float stofl(string numero)
{

    float resultado;

    sscanf(numero.c_str(), "%f", &resultado);

    return resultado;
}

int stoin(string numero)
{
    int resultado;

    sscanf(numero.c_str(), "%d", &resultado);

    return resultado;
}

void texto_centrado(int largo, int linea, string cadena)
{
    gotoxy(largo / 2 - cadena.length() / 2, linea);
    cout << cadena;
}
void opciones_miembros()
{
    bool flag = true;
    do
    {
        const char *titulo = "BIENVENIDO AL MENU DE MIEMBROS";
        const char *inicio[] = {"[1] Registrarse", "[2] Salir"};
        int opc = menu_miembros(titulo, inicio, 2);
        switch (opc)
        {
        case 1:
            Registro_miembros();
            break;
        case 2:
            flag = false;
            break;
        }
    } while (flag);
}
void Registro_miembros()
{
    system("cls");
    comprobar_miembro(0, C_Temp.Persona.Nombre);
    switch (C_Temp.Persona.Miembro)
    {
    case true:
        cout << "Usted ya es un miembro\n";
        break;
    case false:
        agregar_miembro();
        break;
    }
}
void agregar_miembro()
{
    const char *titulo2 = "...::: CONFIRMAR REGISTRO :::...";
    const char *miem_o_clien[] = {"[1] ACEPTAR", "[2] RECHAZAR"};
    switch (menu_miembros(titulo2, miem_o_clien, 2))
    {
    case 1:
        cout << "\nCliente " << C_Temp.Persona.Nombre << " fue agregado a la lista de miembros" << endl;
        registro_miembros_archivo();
        break;
    case 2:
        cout << "\nRegresando...\n";
        Sleep(500);
    default:
        break;
    }
}
int menu_miembros(const char titulo[], const char *opciones[], int n)
{
    int opcionSeleccionada = 1; // Indica la opcionSeleccionada
    int tecla;
    bool repite = true; // controla el bucle para regresar a la rutina que lo llamo, al presionar ENTER
    do
    {
        system("cls");
        gotoxy(0, 0);
        gotoxy(43, 13 + opcionSeleccionada);
        cout << char(175) << endl;

        // Imprime el título del menú
        gotoxy(50, 12);
        cout << titulo;

        // Imprime las opciones del menú
        for (int i = 0; i < n; ++i)
        {
            gotoxy(45, 14 + i);
            cout << i + 1 << ") " << opciones[i];
        }
        // Solo permite que se ingrese ARRIBA, ABAJO o ENTER
        do
        {
            tecla = getch();
            // gotoxy(15, 15); cout << "tecla presionada: " << (char)tecla << " = " << tecla;
        } while (tecla != TECLA_ARRIBA && tecla != TECLA_W && tecla != TECLA_w && tecla != TECLA_ABAJO && tecla != TECLA_S && tecla != TECLA_s && tecla != ENTER);

        switch (tecla)
        {
        case TECLA_ARRIBA:
        case TECLA_W:
        case TECLA_w: // En caso que se presione ARRIBA

            opcionSeleccionada--;
            if (opcionSeleccionada < 1)
            {
                opcionSeleccionada = n;
            }
            break;

        case TECLA_ABAJO:
        case TECLA_S:
        case TECLA_s:
            opcionSeleccionada++;
            if (opcionSeleccionada > n)
            {
                opcionSeleccionada = 1;
            }
            break;

        case ENTER:
            repite = false;
            break;
        }

    } while (repite);
    return opcionSeleccionada;
}
void registro_miembros_archivo()
{
    ofstream miembros;
    miembros.open("miembros.txt", ios::app);
    if (miembros.fail())
    {
        cout << "\nEl registro fracas" << char(162) << "\n";
        return;
    }
    string ag = comprobar_miembro_duplicado(C_Temp.Persona.Nombre);
    miembros << C_Temp.Persona.Nombre << ag << endl;
    miembros.close();
    system("cls");
    gotoxy(50, 14);
    cout << "REGISTRO EXITOSO";
    gotoxy(30, 15);
    cout << "La pr" << char(162) << "xima vez ingrese con el siguiente nombre: " << C_Temp.Persona.Nombre << ag;
    gotoxy(45, 16);
    getch();
}
string comprobar_miembro_duplicado(string nom)
{
    ifstream miembros;
    miembros.open("miembros.txt", ios::in);
    string buffer;
    int i = 0;
    string n_bus = nom + "*";
    while (!miembros.eof())
    {
        n_bus = nom + "*";
        for (int j = 0; j < i; j++)
        {
            n_bus += "*";
        }
        getline(miembros, buffer);
        if (n_bus == buffer)
        {
            i++;
        }
    }
    miembros.close();
    string agregar = "*";
    for (int j = 0; j < i; j++)
    {
        agregar += "*";
    }
    return agregar;
}
/*void guardar_historial(int k, int pago, string tiempo, float tenhoras)
{
}*/
void guardar_historial(int k, float pago, float horas)
{
    // TIEMPO
    string tiempo = "";

    if (Clientes_actuales[k].t.momento[3].hora < 10)
    {
        tiempo += "0" + to_string(Clientes_actuales[k].t.momento[3].hora) + ":";
    }
    else
    {
        tiempo += to_string(Clientes_actuales[k].t.momento[3].hora) + ":";
    }

    if (Clientes_actuales[k].t.momento[3].minu < 10)
    {
        tiempo += "0" + to_string(Clientes_actuales[k].t.momento[3].minu) + ":";
    }
    else
    {
        tiempo += to_string(Clientes_actuales[k].t.momento[3].minu) + ":";
    }

    if (Clientes_actuales[k].t.momento[3].seg < 10)
    {
        tiempo += "0" + to_string(Clientes_actuales[k].t.momento[3].seg) + ":";
    }
    else
    {
        tiempo += to_string(Clientes_actuales[k].t.momento[3].seg);
    }

    FILE *archivo_clientess;
    archivo_clientess = fopen("historial.txt", "a");
    if (archivo_clientess == NULL)
    {
        printf("No se pudo abrir el archivo de clientes\n");
        return;
    }

    // Guardar los datos del cliente actual en el archivo
    fprintf(archivo_clientess, "%s\n", Clientes_actuales[k].Persona.Nombre.c_str());
    fprintf(archivo_clientess, "%s\n", Clientes_actuales[k].Vehiculo.Placa.c_str());
    fprintf(archivo_clientess, "%.4f\n", pago);
    fprintf(archivo_clientess, "%s\n", tiempo.c_str());
    fprintf(archivo_clientess, "%f\n", horas);
    fclose(archivo_clientess);
}
void imprimir_informe()
{
    leer_historial_e_imprimir();
}
void leer_historial_e_imprimir()
{
    ifstream leer_historial;
    leer_historial.open("historial.txt", ios::in);
    if (leer_historial.fail())
    {
        cout << "No hay historial\n";
        return;
    }
    string nombre, placa, nombre_min, placa_min, nombre_max, placa_max, tiempo, hora_min, hora_max;
    float pago, Pago_total = 0, horas, horamin, horamax;
    bool temp = true;
    int clientestotales = 0;
    while (!leer_historial.eof())
    {
        getline(leer_historial, nombre);
        getline(leer_historial, placa);
        leer_historial >> pago;
        leer_historial.ignore();
        getline(leer_historial, tiempo);
        leer_historial >> horas;
        leer_historial.ignore();
        if (temp)
        {
            nombre_min = nombre;
            nombre_max = nombre;
            placa_min = placa;
            placa_max = placa;
            horamin = horas;
            horamax = horas;
            hora_min = tiempo;
            hora_max = tiempo;
        }
        if (horas > horamax)
        {
            placa_max = placa;
            horamax = horas;
            nombre_max = nombre;
            hora_max = tiempo;
        }
        if (horas < horamin)
        {
            placa_min = placa;
            horamin = horas;
            nombre_min = nombre;
            hora_min = tiempo;
        }
        Pago_total += pago;
        clientestotales++;
    }
    leer_historial.close();
    cout << "\n\tInforme de ventas\n";
    cout << "\t-----------------\n";
    cout << "Empresa: APARKED\t\tFecha:04/07/2023\n";
    cout << "Total de ganacias percibidas: " << Pago_total << endl;
    cout << "Clientes totales: " << clientestotales << endl;
    cout << "Periodo m" << char(160) << "ximo de estacionamiento\n";
    cout << "  Nombre: " << nombre_max << endl;
    cout << "  Placa: " << placa_max << endl;
    cout << "  Tiempo: " << hora_max << endl;
    cout << "Periodo m" << char(161) << "nimo de estacionamiento\n";
    cout << "  Nombre: " << nombre_min << endl;
    cout << "  Placa: " << placa_min << endl;
    cout << "  Tiempo: " << hora_min << endl;
    cout << "Fin del informe";
    guardar_informe(Pago_total, clientestotales, nombre_max, nombre_min, placa_max, placa_min, hora_min, hora_max);
}
void guardar_informe(float PagoT, int CliT, string nmax, string nmmin, string plmax, string plmin, string hmin, string hmax)
{
    ofstream guardar;
    guardar.open("Informe.txt", ios::out);
    guardar << "\n\tInforme de ventas\n";
    guardar << "\t-----------------\n";
    guardar << "Empresa: APARKED\t\tFecha:04/07/2023\n";
    guardar << "Total de ganacias percibidas: " << PagoT << endl;
    guardar << "Clientes totales: " << CliT << endl;
    guardar << "Periodo m" << char(160) << "ximo de estacionamiento\n";
    guardar << "  Nombre: " << nmax << endl;
    guardar << "  Placa: " << plmax << endl;
    guardar << "  Tiempo: " << hmax << endl;
    guardar << "Periodo m" << char(161) << "nimo de estacionamiento\n";
    guardar << "  Nombre: " << nmmin << endl;
    guardar << "  Placa: " << plmin << endl;
    guardar << "  Tiempo: " << hmin << endl;
    guardar << "Fin del informe";
}