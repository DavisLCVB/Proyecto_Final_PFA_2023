/*Informe de ventas*/

#include<iostream>
using namespace std;

struct cliente
{
	string nombre;
	char tipo;
	int piso;
	float pago;
	string miembro;	 
}*C;

void ingreso_datos(cliente C[],int n);
void mostrar_datos(cliente C[], int n);
void reporte_ventas(cliente C[], int n, int un, int dos, int tr);

int main(){
	int n, un=0, dos=0, tr=0;
	cout<<"\nBIENVENIDO AL SISTEMA DE ESTACIONAMIENTO"<<endl;
	cout<<"\n�Cuantos clientes registrara?: ";
	cin>>n;
	C = new cliente[n];
	
	ingreso_datos(C,n);
	mostrar_datos(C,n);
	reporte_ventas(C,n,un,dos,tr);
			
	return 0;
}

void ingreso_datos(cliente C[], int n){
	cout<<"\nINGRESO DE DATOS"<<endl;
	for(int i=0; i<n; i++){
		cout<<"\nCliente "<<i+1<<endl;
		cout<<"\nNombre: ";
		cin>>C[i].nombre;
		cout<<"\nAuto = a";
		cout<<"\nMotocicleta = m";
		cout<<"\nCamiones = c";
		cout<<"\nTipo de vehiculo: ";
		cin>>C[i].tipo;
		cout<<"\nPisos: (1-3)";
		cout<<"\nPiso: ";
		cin>>C[i].piso;
		cout<<"Pago: ";
		cin>>C[i].pago;
		cout<<"\nSi = si";
		cout<<"\nNo = no";
		cout<<"\nMiembro: ";
		cin>>C[i].miembro;
		cout<<endl;
		cout<<"--------------------";
		cout<<endl;
    }  
   	cout<<"--------------------";
}

void mostrar_datos(cliente C[], int n){
	cout<<"\nCOMPROBANTES DE PAGO"<<endl;
	for(int i=0; i<n; i++){
		cout<<"\nCliente "<<i+1<<endl;
		cout<<"\nNombre: "<<C[i].nombre;
		cout<<"\nTipo: "<<C[i].tipo;
		cout<<"\nPiso: "<<C[i].piso;
		cout<<"\nPago: "<<C[i].pago;
		cout<<"\nMiembro: "<<C[i].miembro;
		cout<<endl;	
		cout<<"--------------------";			
	}	
}

void reporte_ventas(cliente C[], int n, int un, int dos, int tr){
	int ganancias=0, au=0, mo=0, ca=0, mi=0;
	cout<<"\nINFORME DE VENTAS"<<endl;
	
	for(int i=0; i<n; i++){
		ganancias += C[i].pago;
	}
	
	for(int i=0; i<n; i++){
		if(C[i].miembro == "si"){
			mi++;
	    }
    }
	
	for(int i=0; i<n; i++){
		if(C[i].tipo == 'a'){
			au++;
		}else if(C[i].tipo== 'm' ){
			mo++;		
		}else if(C[i].tipo== 'c'){
			ca++;
		}		
	}
	
	for(int i=0; i<n; i++){
		if(C[i].piso == 1){
			un++;
		}else if(C[i].piso== 2 ){
			dos++;		
		}else if(C[i].piso== 3){
			tr++;
		}		
	}
	cout<<"\nVehiculos que se estacionaron durante el dia: "<<n;
	cout<<"\nNumero de autos estacionados durante el dia: "<<au;
	cout<<"\nNumero de motocicletas estacionados durante el dia: "<<mo;
	cout<<"\nNumero de camiones estacionados durante el dia: "<<ca;
	cout<<"\nAutos que se estacionaron en el piso 1: "<<un;
	cout<<"\nAutos que se estacionaron en el piso 2: "<<dos;
	cout<<"\nAutos que se estacionaron en el piso 3: "<<tr;
	cout<<"\nGanancias del dia: "<<ganancias<<" soles";
	cout<<"\nMiembros nuevos en el dia: "<<mi;
} 