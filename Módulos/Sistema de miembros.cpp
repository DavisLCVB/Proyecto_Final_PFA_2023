#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h> //system color
#include <fstream>
#include <iomanip> //setw
#define color SetConsoleTextAttribute
#define ARRIBA 'w'
#define ABAJO 's'
#define ENTER 13
using namespace std;
//estructura relacionada con los miembros
struct miembros{
    string nombre;
    string placa_auto;
}persona[90];

int a=3;
void DB_miembros(){
    persona[0].nombre = "Juan Rodrigo Perez Figueroa"; persona[0].placa_auto = "BOJ134";
    persona[1].nombre = "Virginia Maria Vera Pomalaza"; persona[1].placa_auto = "AUB122";
    persona[2].nombre = "Iwo Cabezon Bejar Kalinowski"; persona[2].placa_auto = "YTJ982";
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
}
char getch2()
{
    char c = 0;
    DWORD modo, contador;
    HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);

    // Desactivamos escritura en terminal
    SetConsoleMode(ih, modo & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    ReadConsoleA(ih, &c, 1, &contador, NULL);

    if (c == 0){
        ReadConsoleA(ih, &c, 1, &contador, NULL);
    }
    SetConsoleMode(ih, modo); // Devolvemos control normal

    return c;
}

int menu(const char titulo[], const char *opciones[], int n)
{
    int opcionSeleccionada = 1; // Indica la opcionSeleccionada
    int tecla;
    bool repite = true; // controla el bucle para regresar a la rutina que lo llamo, al presionar ENTER
    do{
        system("cls");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
        system("color f0");
        gotoxy(43, 13 + opcionSeleccionada);
        cout << char(175) << endl;

        // Imprime el título del menú
        gotoxy(50, 12);
        cout << titulo;

        // Imprime las opciones del menú
        for (int i = 0; i < n; ++i){
            gotoxy(45, 14 + i);
            cout << i + 1 << ") " << opciones[i];
        }
        // Solo permite que se ingrese ARRIBA, ABAJO o ENTER
        do{
            tecla = getch2();
            // gotoxy(15, 15); cout << "tecla presionada: " << (char)tecla << " = " << tecla;
        } while (tecla != ARRIBA && tecla != ABAJO && tecla != ENTER);

        switch (tecla){
        case ARRIBA: // En caso que se presione ARRIBA
            
            opcionSeleccionada--;
            if (opcionSeleccionada < 1){
                opcionSeleccionada = n;
            }
            break;

        case ABAJO:
            opcionSeleccionada++;
            if (opcionSeleccionada > n){
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

void Cargando(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    color(hConsole, 1);
    system("cls");
    SetConsoleTextAttribute(hConsole, 2);
    cout << "\n";
	gotoxy(53,17); cout << " CARGANDO...\n";
	for(int i=0; i<=79; i++)
	{
		gotoxy(20+i,20); cout<<char(178);
		Sleep(1000/80);
	}
}
void mostrar_estacionamiento(){
    system("cls");
    gotoxy(30, 12); 
    cout<<":::...USTED ES MIEMBRO DE NUESTRO SISTEMA DE ESTACIONAMIENTO...:::"<<endl;
    gotoxy(30, 14); 
    cout<<"aqui se supone que se muestra el estacionamiento y el miembro elige su lugar.";gotoxy(30, 15);cout<<"Ademas, se le aplica descuento en el cobro final cuando retira su auto"<<endl;
    getch();
}
bool verifica_miembro(miembros z[], string placa, int p){
    for(int i=0; i<= p; i++){
        if(z[i].placa_auto == placa ){
            return true;
        }
    }
    return false;
}
void registro_miembros(miembros x[], int f){
    system("cls");
    fflush(stdin);
    gotoxy(35,6);cout<<"LISTA DE MIEMBROS DEL ESTACIONAMIENTO "<<endl;
    gotoxy(2,8);cout<<"Nombres";gotoxy(50,8);cout<<"Placa de auto";
    cout<<"\n--------------------------------------------------------------------------------";
    for (int i = 0; i <= f; i++){
        gotoxy(1,i+10); cout << x[i].nombre;
        gotoxy(50,i+10);cout << x[i].placa_auto<<endl;
    }
    getch();
}
void agregar_miembro (miembros m[], int &q, string nombre, string plac){
    const char *titulo2 = "...::: CLIENTE :::...";
    const char *miem_o_clien[] = {"[1] Pertenecer a la lista de miembros", "[2] Ingresar al estacionamiento solo como cliente (no beneficios)"};
    switch (menu(titulo2, miem_o_clien, 2)){
    case 1:
        m[q].nombre = nombre;
        m[q].placa_auto = plac;
        q++;
        cout<<"\nCliente "<<nombre<<" fue agregado a la lista de miembros"<<endl;
        registro_miembros(persona, q);
        mostrar_estacionamiento();
        break;
    case 2:
        mostrar_estacionamiento();
    default:
        break;
    }
}
void ingreso_datos(miembros y[] ){
    system("cls");
    string auxnom, auxcod;
    gotoxy(53, 12); cout<<"Ingrese su nombre completo"<<endl; fflush(stdin); gotoxy(53, 13);  getline(cin,auxnom);fflush(stdin);
    system("cls");
    gotoxy(53, 12); cout<<"Ingrese la placa de auto"<<endl; gotoxy(53, 13);  getline(cin, auxcod); fflush(stdin);
    switch (verifica_miembro (persona, auxcod,a)){
        case true:
            mostrar_estacionamiento();
            
        break;
        case false:
            agregar_miembro (persona, a, auxnom, auxcod);
        break;
    }
}

void opciones(){
    bool flag = true;
    do{
    const char *titulo = "BIENVENIDO";
    const char *inicio[] = {"[1] INICIO","[2] Mostrar lista de miembros", "[3] Salir"};
    int opc = menu(titulo, inicio, 3);
    switch (opc){
    case 1:
        ingreso_datos(persona);
        break;
    case 2:
        registro_miembros(persona, a);
        break;
    case 3:
        flag = false;
        break;
    }
    }while(flag); 
}

int main(){
    DB_miembros();
    Cargando();
    opciones();
    getch();
    return 0;
}