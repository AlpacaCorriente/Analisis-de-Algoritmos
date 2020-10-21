#include <bits/stdc++.h>
using namespace std;

const int  infinito = 99999999;

// objeto caja que procesa los elementos 
class caja {
	
private:
	vector <pair<char, int >> objetos;// objetos insertados
	int *costos ,*niveles;
	vector<vector<int>> tabla_valores;
	int ancho ,cantidad_de_objetos;// atributos que definen la caja ancho y cantidad de objetos

public:
	caja(int, int );

	void agregar_objetos(vector <pair<char, int >>);
	void procesar_objetos();// calcula los valores que se ingresan en la tabla de valores
	void ordenar_objetos();// recorre la tabla de valores para encontrar el ordenamiento optimo dentro de la caja 
};

caja::caja(int tam,int numero_de_objetos ){

	cantidad_de_objetos= numero_de_objetos;
	costos = new int[numero_de_objetos+1]{infinito};
	niveles= new int[numero_de_objetos];
	tabla_valores.resize(numero_de_objetos+1);
	ancho=tam;
   // inicializando los arreglos auxiliares
	for(int i = 0 ; i<numero_de_objetos ; i++){
		costos[i+1]=infinito;
		niveles[i]=-2;
		tabla_valores[i].resize(numero_de_objetos+1);
	}
	// inicializando tabla de valores 
	for(int i = 0 ; i<numero_de_objetos ; i++){

		for(int j = 0 ; j<numero_de_objetos ; j++){
			if(i<=j){
				tabla_valores[i][j]=infinito;
			}
			else{ tabla_valores[i][j]=-2;
			}
		}
	}

}

void caja :: agregar_objetos (vector <pair<char, int >> n_objetos){

	objetos= n_objetos;
	this->procesar_objetos();
	this->ordenar_objetos();
} 

void caja :: procesar_objetos( ){
	int suma= 0;
	// para cada objeto cacula el espacio restante luego de insertalo en un nivel ya sea junto a otros objetos o el solo en un nivel
	for (int i = 0 ; i < cantidad_de_objetos ; i++){

		int j=i;
		suma = objetos[i].second;

		while(suma<=ancho && j<cantidad_de_objetos){

			tabla_valores[i][j]= (ancho-suma);
			j++;
			suma= (suma + objetos[j].second) + 1;
		}
	}


}

// recorriendo la tabla de valores se resuelve el subproblema optimo  
void caja:: ordenar_objetos(){

 int i=cantidad_de_objetos-2, j=cantidad_de_objetos-1,val_optimo, niv_optimo , aux ;
	costos[cantidad_de_objetos]=0;
	costos[cantidad_de_objetos-1]=pow(tabla_valores[cantidad_de_objetos-1][cantidad_de_objetos-1],3);// es ingresado el ultimo elemento dentro de la tabla de costo considerando que este estará solo en un nivel 
	niveles[cantidad_de_objetos-1]=cantidad_de_objetos;

	while(i>= 0 && j>= 0){

		if(tabla_valores[i][j]==infinito){// Si los objetos i y j no pueden estar en un mismo nivel, contianua con  j a la izquierda hasta encontrar un elemento factible.
			j--;
			continue;
		}

		if(i==j){// si llega hasta la diagonal de la tabla sube al siguiente nivel; 
			i--;
			j=cantidad_de_objetos-1;
			continue;
		}

		val_optimo = pow(tabla_valores[i][j],3)+costos[j+1];// considera la  combinación de elementos actual como un optimo
		niv_optimo = j+1;

		for(int k=j-1; k>=i ;k--){
			aux = pow(tabla_valores[i][k],3)+costos[k+1];
			if(aux<val_optimo){// compara la combiancion anterior con el optimo actual , actualizando si esta es mejor
				val_optimo = aux;
				niv_optimo = k+1;
			}
		}
		//guardando los valores optimos en los arreglos de costos y nivel , para continuar con el siguiente nivel 
		costos[i] = val_optimo; 
		niveles[i] = niv_optimo;
		i--;
		j=cantidad_de_objetos-1; 
	}

// imprimiendo output 

  i=0;
	int k, l=1,tam_del_nivel;
	vector<int> espacio_extra;

	while(i<cantidad_de_objetos){
		tam_del_nivel=0;
		cout<<"Nivel "<<l<<": \"";
		for(j=i; j<niveles[i]; j++){
			if(j!=i){
				cout<<" ";
				tam_del_nivel++;
			}
			for(k=0;k<objetos[j].second;k++){
				cout<<objetos[j].first;
				tam_del_nivel++;
			}
		}
		for(k=0 ;k<(ancho-tam_del_nivel);k++){
			cout<<" ";
		}
		cout<<"\"... Espacio extra = "<< ancho-tam_del_nivel<<endl;
		espacio_extra.push_back(ancho-tam_del_nivel);
		i=niveles[i];
		l++;
	}
	cout<<"Suma cubos = ";
	int sum=0;
	for(i=0;i<espacio_extra.size();i++){
		if(i!=0) cout<<" + ";
		cout<<espacio_extra[i]<<"^3";
		sum+=pow(espacio_extra[i],3);
	}

	cout<<" = "<<sum<<endl;

	cout<<endl<< " Visualizacion de espacio extra por nivel "<<endl;
	l=1;
	i=0;

	while(i<cantidad_de_objetos){
		tam_del_nivel=0;
		cout<<"Nivel "<<l<<":";
		for(j=i;j<niveles[i];j++){

			if(j!=i){
				cout<<" ";
				tam_del_nivel++;
			}

			for(k=0;k<objetos[j].second;k++){
				cout<<" ";
				tam_del_nivel++;
			}
		}
		for(k=tam_del_nivel;k<ancho;k++){
			cout<<"P";
		}
		cout<<endl;
		i=niveles[i];
		l++;
	}

	delete(costos);
	delete(niveles);

}




int  main(){
	int n ,ancho , tam;
	vector <pair<char, int >> objetos_a_insetar;
	caja *C1 ;

	cout<<"numero de objetos:"<<endl;
	cin>>n;
	cout<<" ancho de la caja:"<<endl;
	cin>>ancho; 
	srand (time(NULL));
	char etiqueta = 'A';

// creación de objetos aleatorios 

	for(int i= 0 ; i<n ; i++){

		tam = (1+(rand()%(ancho/3)));// el tamaño del objeto más grande es a lo más 1/3 el ancho de la caja
		objetos_a_insetar.push_back(make_pair(etiqueta,tam));
		etiqueta ++;

	}

	for(int i= 0 ; i<n ; i++){// imprimiendo objetos

		cout <<"(" <<objetos_a_insetar[i].first<< ", "<<objetos_a_insetar[i].second<<")"<< endl; 

	}

	C1 = new caja(ancho , n );
	// agregando objetos a la caja 
	C1->agregar_objetos(objetos_a_insetar);





 
	return 0;
}