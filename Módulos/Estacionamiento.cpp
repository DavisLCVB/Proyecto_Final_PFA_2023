#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#define TECLA_ARRIBA 119
#define TECLA_ABAJO 115
#define ENTER 13
#define TECLA_DERECHA 100
#define TECLA_IZQUIERDA 97
using namespace std;
int estacionamiento_piso1[15][36] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
int pos_inic_x=41;
int pos_inci_y=2;
void gotoxy(int coordx, int coordy);
void color_cnsl(int colorfondo, int colortexto);
void mostrar_est(int[][36]);
void escoger_lugar();
void esc_y_mos_est();
int main()
{
    system("color F0");

    esc_y_mos_est();
}
void esc_y_mos_est()
{
    mostrar_est(estacionamiento_piso1);
    escoger_lugar();
    mostrar_est(estacionamiento_piso1);
    getch();
}
void mostrar_est(int est[][36])
{
    for (int iterador_x = 0; iterador_x < 15; iterador_x++)
    {
        for (int iterador_y = 0; iterador_y < 36; iterador_y++)
        {
            gotoxy(pos_inic_x + iterador_y, pos_inci_y + iterador_x);
            if (est[iterador_x][iterador_y] == 0)
                cout << char(219);
            if (est[iterador_x][iterador_y] == 1)
                cout << " ";
            if (est[iterador_x][iterador_y] == 2)
                cout << char(178);
            if (est[iterador_x][iterador_y] == 3)
                cout << char(35);
        }
        cout << endl;
    }
}
void escoger_lugar()
{
    system("cls");
    mostrar_est(estacionamiento_piso1);
    bool condicion_fin_elecc = true;
    int incremento_x = 6, incremento_y = 4;
    while (condicion_fin_elecc)
    {
        gotoxy(pos_inic_x + incremento_x, pos_inci_y + incremento_y);
        color_cnsl(9, 15);
        cout << "    ";
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
            estacionamiento_piso1[incremento_y][incremento_x] = 3;
            estacionamiento_piso1[incremento_y][incremento_x + 1] = 3;
            estacionamiento_piso1[incremento_y][incremento_x + 2] = 3;
            estacionamiento_piso1[incremento_y][incremento_x + 3] = 3;
            condicion_fin_elecc = false;
        }
        mostrar_est(estacionamiento_piso1);
    }
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