#include<iostream>
#include<string.h>
#include<conio.h>

using namespace std;

struct retiro{
	string nombre;
	string placa;
	int posicionf;
	int posicionc;
	double pago;
	double tiempo_en_h;
}p;

void retiro_veh(retiro, int m[4][4]);
void voucher(retiro, int m[4][4]); 
int m[4][4];
int main(){
	
	cout<<"\tMostrando mapa de estacionamiento  ";
	int m[4][4]= {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};

	cout<<"\n"<<endl;
	for(int i=0;i<4;i++){
		for (int j=0;j<4;j++){
				cout<<"\t\t "<<m[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
	retiro_veh(p,m);
	cout<<"\n";
	voucher(p,m);

	
	getch();
	return 0;
}
void retiro_veh(retiro p, int m[4][4]){
	cout<<"digite la posicion de la fila de su vehiculo: ";
	cin>>p.posicionf;
	cout<<"digite la posicion de la columna de su vehiculo: ";
	cin>>p.posicionc;
	
	m[p.posicionf][p.posicionc]=0;
	
	cout<<"\t\nMostrando nuevo mapa de estacionamiento ";
	cout<<"\n"<<endl;
	
	for (int i=0;i<4;i++){
		for (int j=0;j<4;j++){
			if(m[i][j]!=m[p.posicionf][p.posicionc]){
				cout<<"\t\t "<<m[i][j]<<" ";
			}else{
				cout<<"\t\t "<<m[p.posicionf][p.posicionc];
			}
		}
		cout<<"\n";
	}
	
}
void voucher(retiro p, int m[4][4]){
	cout<<"digite su nombre: ";
	cin>>p.nombre;
	cout<<"digite su placa: ";
	cin>>p.placa;
	cout<<"digite el tiempo en horas a establecerse: ";
	cin>>p.tiempo_en_h;
	cout<<"\n";
	cout<<"\t\tImprimiendo voucher "<<endl;
	cout<<" Datos del cliente: "<<p.nombre<<endl;
	cout<<" Placa de vehiculo: "<<p.placa<<endl;
	//cout<<"Tiempo total de servicio: "<<
	p.pago=7.5*p.tiempo_en_h;
	cout<<"\n Total a pagar: "<<p.pago;

}