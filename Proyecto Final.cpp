#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <ctype.h>
#define TECLA_ARRIBA 119
#define TECLA_ABAJO 115
#define ENTER 13
#define TECLA_DERECHA 100
#define TECLA_IZQUIERDA 97
using namespace std;
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
void menu_empleado(string);
void menu_cliente(string);
void ocultar_cursor();
void reiniciar_C_Temp();
void Ingreso_datos(string);
int Estacionar_o_retirar();
void mostrar_est(int[][36]);
void escoger_lugar();
void esc_y_mos_est();
string menu_tipo_vehiculo();
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
struct CLIENTE
{
    PERSONA Persona;
    VEHICULO Vehiculo;
} *Clientes_actuales, C_Temp;
int pos_inic_x = 41;
int pos_inci_y = 2;
int Estacionamiento[15][36] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
    Clientes_actuales = new CLIENTE[16];
    system("color F0");
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
            cout << "Empleado";
        }
        else
        {
            menu_cliente(C_Temp.Persona.Nombre);
        }
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
    cout << "Hola " << nom << " (empleado)";
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
            break;
        case 2:
            break;
        case 3:
            system("cls");
            mostrar_est(Estacionamiento);
            getch();
            break;
        case 4:
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
    cout << "4. Atras\n";
    cout << "\n>>";
    while (!(cin >> op) || (op < 1) || (op > 4))
    {
        cin.clear();
        cin.ignore(123, '\n');
        cout << "Opci" << char(162) << "n inv" << char(160) << "lida\n>>";
    }
    return op;
}
void Ingreso_datos(string nom)
{
    cout << "Hola " << nom << endl;
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
void mostrar_est(int est[][36])
{
    for (int iterador_x = 0; iterador_x < 15; iterador_x++)
    {
        for (int iterador_y = 0; iterador_y < 36; iterador_y++)
        {
            gotoxy(pos_inic_x + iterador_y, pos_inci_y + iterador_x);
            if (est[iterador_x][iterador_y] == 0)
                cout << char(219); // █
            if (est[iterador_x][iterador_y] == 1)
                cout << " ";
            if (est[iterador_x][iterador_y] == 2)
                cout << char(178); // ▓
            if (est[iterador_x][iterador_y] == 3)
                cout << char(35); // #
        }
        cout << endl;
    }
}
void escoger_lugar()
{
    system("cls");
    mostrar_est(Estacionamiento);
    bool condicion_fin_elecc = true;
    int incremento_x = 6, incremento_y = 4;
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
        if (tecla == TECLA_DERECHA)
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
        if (tecla == TECLA_IZQUIERDA)
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
        if (tecla == TECLA_ABAJO)
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
        if (tecla == TECLA_ARRIBA)
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
            condicion_fin_elecc = false;
        }
        mostrar_est(Estacionamiento);
    }
}
void esc_y_mos_est()
{
    mostrar_est(Estacionamiento);
    escoger_lugar();
    mostrar_est(Estacionamiento);
    getch();
}