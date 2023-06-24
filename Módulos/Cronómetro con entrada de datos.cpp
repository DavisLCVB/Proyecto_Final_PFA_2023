#include<iostream>
#include<string.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<ctime>

using namespace std;

struct crono{
	int hora;
	int minu;
	int seg;
};

struct tiempos{
	int x;
	int y;
	int ocupado;
	crono momento[4]; //0 es inicio 1 es final 2 es actual 3 es restante
	string nombre;
	string placa;
	string color;
	string tipo;
};

tiempos t[16];

HANDLE wHnd;
void establecer_tamanio_consola();
const int ancho=720;
const int alto=480;
const int limite_ancho=124;

COORD coordenada={0,0};
void gotoxy(int, int);


void reloj(int k);
void reloj_y_ingresodatos(int k);
void mostrar_crono(int k);
void leer_estacionamientos();
void dibujo();
void centrar_texto(string texto, int fila);

int main(){
	establecer_tamanio_consola(); //NO FUNCIONA, CREO
	leer_estacionamientos();
    //ESTE DATO ES DONDE SE ESTACIONARA EL NUEVO AUTO, NOS LO PASARAN DE OTRA FUNCION
    //POR LO CUAL, POR AHORA LO DETERMINAMOS COMO UN ALEATORIO
	int a_ocupar = 10;
    //DIBUJAMOS EL ESTACIONAMIENTO
	dibujo();
	reloj_y_ingresodatos(a_ocupar);
	system("cls");
	cout<<"Nombre: "<<t[a_ocupar].nombre<<endl;
	getch();
	system("cls");
	dibujo();
	reloj(a_ocupar);


	return 0;
}

void dibujo(){

    //LINEAS VERTICALES
    //LA PRIMERA SERA EN X= 41 Y = 2
	int x = 41, y = 2;
	
    //El primer for es para escribir en un aumento y+=1 23 veces una serie ' |        |        | '
	for(int i =0; i<23;i++){
        //El segundo for escribira la serie determinada de '|' cada 21 espacios en x solo 3 veces
		for(int j=0; j<3;j++){
			gotoxy(x,y);
			cout<<"|";
			x+=21;
		}
        //Pasamos a la siguiente linea
		x=41;
		y+=1;
	}
	
	//LINEAS HORIZONTALES
	x=21;
	y=7;
	
	//Primer for escribira el 'salto' a la siguiente linea con un y+=6
	for(int i=0; i<3;i++){
		//El segundo for escribira '--' 83 veces desdes la posicion x = 21
		for(int j=0; j<83;j++){
			gotoxy(x,y);
			cout<<"--";
			x++;
		}
		x=21;
		y+=6;
	}
}

void reloj_y_ingresodatos(int k){
	//PRIMERO UBICAMOS EL LUGAR A ASIGNAR 'K'
	//OCULTAMOS EL CURSOS PORQUE SE VAN A ESCRIBIR DATOS A CADA INSTANTE EN DISTINTOS LUGARES
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	//DETERMINAMOS EL TIEMPO QUE SE QUEDARA EL CARRO, POSTERIORMENTE DEBE SER POR ELECCION
	int aumento_min = 0;
	int aumento_seg = 10;
	int aumento_hor = 0;

	//Escribimos el primer campo a ingresar
	gotoxy(30,26);
	cout<<"[>] DIGITE SU NOMBRE: ";

	//La variable texto almacenara temporalmente el nombre y m controlara donde se muestra lo escrito
	//ES UN INTENTO DE SIMULACION DEL CIN>>
	char texto[100];
    int m = 0;

    char c;

	//MIENTRAS NO SE DETECTE QUE SE PRESIONO ENTER O SE COMPLETARON LOS 100 CARACTERES
	do
    {	
		//El for permitira mostrar el cronometro por cada espacio
		//En el caso del espacio 'k', se pausa para mostrarlo una vez se digiten todos los datos
    	for(int i=0; i<16; i++){
    		if( i == k){
    			gotoxy(t[k].x,t[k].y+4);
    			cout<<aumento_hor<<":"<<aumento_min<<":"<<aumento_seg;
			}else{
				mostrar_crono(i);
			}
		}
        
		//Establecemos el puntero en la posicion donde se mostrara el caracter recibido
		gotoxy(55+m,26);

		//Almacenamos el antes de empezar a detectar los caracteres 
		//En base a cuando se corre el programa contabilizado por TICS
		clock_t inicio = clock();

		//Mientras el tiempo desde que se entro al while sea menor a 0.1 segundos
		//CLOCK() toma los TICKS desde que se inicio el programa
		while ((clock() - inicio)/CLOCKS_PER_SEC< 0.1)
    	{	
			
       		if (kbhit()) // Si se ha presionado una tecla
       		{
				//Almacena la tecla presionada en c
       			c = getch();
        		if (c != '\r') // Ignorar el caracter de retorno de carro ('\r') que es enter
      	 		{
				
				//Almacena el caracter preisonado en la cadena
      	   		texto[m] = c;
				//Muestra en pantalla que caracter se guardo
      	  	 	cout<<c;
				//Aumenta la posicion del cursor para el siguiente caracter a ingresar
     	 		m++;
    	 	  }
        	}
    	}
    } while (c != '\r' && m < 99);
    
	//Agregamos el caracter finalizador de la cadena
	texto[m]= '\0';
	//Determinamos que la cadena almacenada en texto pase al campo que corresponda
    t[k].nombre = texto; 
	
}

void reloj(int k){
	
	//DADO QUE LA FUNCION ESTA EN UN BUCLE, ESTO APLICARA PARA TODOS LOS RELOJES

	//PRIMERO UBICAMOS EL LUGAR A ASIGNAR 'K'
	//OCULTAMOS EL CURSOS PORQUE SE VAN A ESCRIBIR DATOS A CADA INSTANTE EN DISTINTOS LUGARES
    CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);

	//Las siguientes funciones toman el tiempo actual del sistema (pc)
	//Almacenan el tiempo actual en una varible tipo time_t 
	time_t inicio = time(NULL);
	//Se crea una estructura tipo tm* (predefinida por libreria <time.c>
	tm* time = localtime(&inicio);

	//Asignamos las horas, minutos y segundos al momento inicial
	t[k].momento[0].hora = time->tm_hour;
	t[k].momento[0].minu = time->tm_min;
	t[k].momento[0].seg = time->tm_sec;

	//gotoxy(t[k].x,t[k].y+1);
	//cout<<"INICO: "<<t[k].momento[0].hora<<":"<<t[k].momento[0].minu<<":"<<t[k].momento[0].seg<<endl;
	
	//DETERMINAMOS EL TIEMPO QUE SE QUEDARA EL CARRO, POSTERIORMENTE DEBE SER POR ELECCION
	int aumento_min = 0;
	int aumento_seg = 10;
	int aumento_hor = 0;
	

	//ESTABLECER EL MOMENTO DE SALIDA PARA EL ESPACIO
	t[k].momento[1].seg = t[k].momento[0].seg+aumento_seg;
	t[k].momento[1].minu = t[k].momento[0].minu+aumento_min;
	t[k].momento[1].hora = t[k].momento[0].hora+aumento_hor;
	
	if(t[k].momento[1].seg >=60){
		t[k].momento[1].minu+=1;
		t[k].momento[1].seg-=60;
	}
	if(t[k].momento[1].minu>=60){
		t[k].momento[1].seg+=1;
		t[k].momento[1].minu-=60;
	}
	if(t[k].momento[1].hora>=24){
		t[k].momento[1].hora = 1;
	}
	

	//gotoxy(t[k].x,t[k].y+2);
	//cout<<"Final: "<<t[k].momento[1].hora<<":"<<t[k].momento[1].minu<<":"<<t[k].momento[1].seg<<endl;

	//MIENTRAS NO SE PRESIONE ENTER SE MOSTRARAN LOS CRONOMETROS
    char c;
	do
    {
		//SE MUESTRAN LOS 16 CRONOMETROS
    	for(int i=0; i<16; i++){
			mostrar_crono(i);
		}
          
		//TOMAMOS LOS TICS DESDE QUE SE INICIO EL PROGRAMA
		clock_t inicio = clock();

		//SI DURANTE 0.1 SEGUNDOS NO SE HA DETECTADO EL ENTER, SE SEGUIRAN MOSTRANDO LOS RELOJES
		
		while ((clock() - inicio)/CLOCKS_PER_SEC< 0.1)
    	{
       		if (kbhit())
       		{
       			c = getch();
        	}
    	}
    } while (c != '\r');
    
}

void leer_estacionamientos(){

    //ESTO SE DEBE HACER POR ARCHIVOS, POR LO CUAL AUN ES TEMPORAL
    //Establecemos las coordenadas (x,y) desde donde se colocaran los relojes
	int espaciadox = 27; 
	int espaciadoy = -2; //Es -2 porque al escribir se da un aumento de "+4" en la funcion mostrar_crono()
                         //EN CASO SE QUIERAN MOSTRAR LOS RELOJOS COMPLETOS (INICIO, FINAL, ACTUAL, RESTANTE), COLOCAR 0
	
    //DETERMINAMOS LOS DATOS PARA CADA ESPACIO DE LOS 16 EXISTENTES
	for(int i=0; i<16; i++){
        //coordenadas del reloj i
		t[i].x = espaciadox;
		t[i].y = espaciadoy;
        //Momento inicial del reloj i
		t[i].momento[0].seg = 20;
		t[i].momento[0].minu = 20;
		t[i].momento[0].hora = 13;
        //Momento final del reloj i
		t[i].momento[1].seg = 14;
		t[i].momento[1].minu = 16;
		t[i].momento[1].hora = 14;
        //EN CASO LAS COORDENDAS X SOBREPASEN LOS 80, SE PASARA A LA SIGUIENTE LINEA
		if(espaciadox>=80){
			espaciadox=27;
			espaciadoy+=6;
		}else{              //CASO CONTRARIO SE AUMENTARA +22 PARA EL SIGUIENTE RELOJ i+1
			espaciadox+=22;
		}
	}

}

void mostrar_crono(int k){

	int total_act = 0, total_fin = 0, diferencia = 0;
	//MOSTRAR DETALLES DEL INICIO Y FINAL
	//gotoxy(t[k].x,t[k].y);
	//cout<<"INICO: "<<t[k].momento[0].hora<<":"<<t[k].momento[0].minu<<":"<<t[k].momento[0].seg<<endl;
	//gotoxy(t[k].x,t[k].y+1);
	//cout<<"Final: "<<t[k].momento[1].hora<<":"<<t[k].momento[1].minu<<":"<<t[k].momento[1].seg<<endl;

	//CALCULAMOS EN SEGUNDOS LA CANTIDAD DE SEGUNDOS DESDE INICIADO EL DIA EN QUE SE RETIRARA EL CARRO
	total_fin = t[k].momento[1].hora*3600 + t[k].momento[1].minu*60 + t[k].momento[1].seg;
	
	//Las siguientes funciones toman el tiempo actual del sistema (pc)
	//Almacenan el tiempo actual en una varible tipo time_t 
	time_t now = time(NULL);
	//Se crea una estructura tipo tm* (predefinida por libreria <time.c>
	tm* act = localtime(&now);
	
	//ALMACENAMOS LAS HORAS, MINUTOS Y SEGUNDOS EN EL VECTOR RESPECTIVO
	t[k].momento[2].minu = act->tm_min;
	t[k].momento[2].seg  = act->tm_sec;
	t[k].momento[2].hora = act->tm_hour;

	//MOSTRAR DETALLES DE LA HORA ACTUAL Y LOS CALCULOS
	//gotoxy(t[k].x,t[k].y+2);
	//cout<<"Actual: "<<t[k].momento[2].hora<<":"<<t[k].momento[2].minu<<":"<<t[k].momento[2].seg<<endl;

	//Se calcula la cantidad de segundos que pasaron desde que se inicio el dia hasta la actualidad
	total_act = t[k].momento[2].hora*3600 + t[k].momento[2].minu*60 + t[k].momento[2].seg;
	//gotoxy(t[k].x,t[k].y+3);
	//cout<<total_fin<<" "<<total_act;

	//SE HACEN LOS CALCULOS PARA DETERMINAR LA HORA, MINUTO Y SEGUNDOS RESTANTES
	diferencia = total_fin - total_act;
	t[k].momento[3].hora = diferencia/3600;
	t[k].momento[3].minu = (diferencia - t[k].momento[3].hora*3600)/60;
	t[k].momento[3].seg = diferencia - (t[k].momento[3].hora*3600 + t[k].momento[3].minu*60);
	
	//SI AUN EXISTE TIEMPO RESTANTE
	if(diferencia > 0){

		//SE MOSTRARAN LAS HORAS, MINUTOS Y SEGUNDOS
		gotoxy(t[k].x,t[k].y+4);
		//cout<<"Tiempo restante: ";
		//gotoxy(t[k].x+17,t[k].y+4);

		cout<<"        ";
		gotoxy(t[k].x,t[k].y+4);
		//gotoxy(t[k].x+17,t[k].y+4);
		cout<<t[k].momento[3].hora<<":"<<t[k].momento[3].minu<<":"<<t[k].momento[3].seg<<endl;

		/*POR EL MOMENTO EL CARRO ES MUY GRANDE, SE BUSACAR OTRA FIGURA
		DIBUJAR CARRO SI EL ESPACIO ESTA OCUPADO
		gotoxy(t[k].x+5,t[k].y+5);
		for(int i=1; i<=20;i++){
			cout<<char(176);
		}
		gotoxy(t[k].x+5,t[k].y+6);
		for(int i=1;i<=5;i++){
			cout<<char(176);
		}
		cout<<char(220)<<char(219)<<char(223)<<char(223)<<char(219)<<char(223)<<char(223)<<char(219)<<char(220);
		for(int i=1;i<=6;i++){
			cout<<char(176);
		}
		gotoxy(t[k].x+5,t[k].y+7);
		cout<<char(176)<<char(176);
		for(int i=1;i<=15;i++){
			cout<<char(219);
		}
		cout<<char(176)<<char(176)<<char(176);
		gotoxy(t[k].x+5,t[k].y+8);
		cout<<char(176)<<char(176)<<char(176)<<char(223)<<char(223)<<"0";
		for(int i=1; i<=6;i++){
			cout<<char(223);
		}
		cout<<"0"<<char(223)<<char(223)<<char(223)<<char(176)<<char(176)<<char(176)<<char(176);
		gotoxy(t[k].x+5,t[k].y+9);
		for(int i=1; i<=21; i++){
			cout<<char(178);
		}*/
		
	}else if(diferencia <= 0){
		gotoxy(t[k].x,t[k].y+4);
		cout<<"00:00:00";
		/*
		for(int i=0;i<5;i++){
			for(int j=0; j<21; j++){
				gotoxy(t[k].x+5+j,t[k].y+5+i);
				cout<<" ";
			}
		}
		*/
	}
}

void establecer_tamanio_consola(){
	
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = {0, 0, ancho, alto};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
}

void gotoxy(int x, int y){
	coordenada.X=x;
	coordenada.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordenada);
}

void centrar_texto(string texto, int fila){
	gotoxy(limite_ancho/2-texto.length()/2,fila);
	cout<<texto;
}