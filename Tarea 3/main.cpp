#include <bits/stdc++.h>


using namespace std;
void kruskal_listas(vector<struct Arista> , vector<int>);//Kruskal dos implementaciones
void kruskal_arboles(vector<struct Arista> , vector<int>);
vector<struct Arista> grafo_aleatorio( int);
 // aristas donde se guardan los datos de entrada
struct  Arista{
	int peso , empieza , termina;
	bool operator() (Arista i,Arista j) { return (i.peso<j.peso);}
};

//almacena la cabeza de la lista que contiene a los nodos de un conjunto
struct  lista {   

	struct nodo *siguiente;
	struct nodo *cola;
	int representante;
	int cantidad_vertices;
	
	};

// nodo de un conjunto 
struct nodo{
	
		int vertice;
		lista *representado_por;
		nodo *next;

	};
//clase que implementa las operaciones de union & find con listas 
class UFLista {
	
private:
	map <int, lista*> conjuntos; // mapea al nodo(clave) con su representante(valor) 
public:
	UFLista();
	void MakeSet(int);
	void Union(lista * , lista *);
	lista* Find(int);
	void imprimir();

};


 UFLista::UFLista(){

 }
// se realiza el make set de x

void UFLista :: MakeSet (int x){

	lista *set = new lista();
	set->representante = x;
	nodo *repre = new nodo();
	repre->vertice = x;
	repre->next = NULL;
	repre->representado_por = set;
	set->siguiente = repre;
	set->cola = repre;
	set->cantidad_vertices= 1;
	conjuntos.insert(make_pair ( x , set));
}
// al mapear las aristas
 lista * UFLista :: Find(int X){
      
 	 return conjuntos.find(X)->second;

}

void UFLista::Union(lista *Conjunto_1 , lista *Conjunto_2 ){
	nodo *iterador;

	if(Conjunto_1->cantidad_vertices > Conjunto_2->cantidad_vertices){// el conjunto con menos cantidad de vertices se une al con mayor cantidad de vertices
		
		iterador = Conjunto_2->siguiente;
		delete(iterador->representado_por);
		Conjunto_1->cola->next=iterador;

		while(iterador){


			conjuntos.erase(iterador->vertice);
			conjuntos.insert(make_pair(iterador->vertice , Conjunto_1));
			Conjunto_1->cola = iterador;
			iterador->representado_por = Conjunto_1;
			Conjunto_1->cantidad_vertices++;
			iterador= iterador->next;
		}

	}else{

       iterador = Conjunto_1->siguiente;
		delete(iterador->representado_por);
		Conjunto_2->cola->next=iterador;

		while(iterador){

			conjuntos.erase(iterador->vertice);// elimina clave valor anterior
			conjuntos.insert(make_pair(iterador->vertice , Conjunto_2));
			iterador->representado_por = Conjunto_2;
			Conjunto_2->cola = iterador;
			Conjunto_2->cantidad_vertices++;
			iterador= iterador->next;
		}

	}
	
}
void UFLista::imprimir(){
	for(map<int, lista*>::iterator it = conjuntos.begin(); it!=conjuntos.end(); ++it ){

		cout << it->first << " => " << it->second->representante << '\n';
	}
	lista *it_2 = conjuntos.begin()->second;
	nodo  *it_nodo = it_2->siguiente;
	for(int i=0 ; i < it_2->cantidad_vertices; i++){
		cout<< it_nodo->vertice<<endl;
		it_nodo=it_nodo -> next;
	}

}

// clase que implementa las operaciones de union find con arboles 
class UFArbol {
	
private:
	vector<int> Padres , Rank;

public:
	UFArbol(int);
	void MakeSet(int);
	void link(int , int);
	void Union(int,int);
	int Find(int);
	void imprimir();

}; 

UFArbol:: UFArbol(int n){
Padres.resize(n);
Rank.resize(n);
}

void UFArbol :: MakeSet(int x){
	Padres[x]=x;
	Rank[x]=0;  
}

int UFArbol:: Find(int x){
if(x != Padres[x]){
	Padres[x]=this->Find(Padres[x]);
	}
	return Padres[x];
}

void UFArbol:: link (int x , int y ){
	if (Rank[x] > Rank[y]){// aplica heuristica del mejor rank
		Padres[y] = x;
		}
   else{ 
       	Padres[x] = y;
		if (Rank[x] == Rank[y]){
		Rank[y] = (Rank[x])+1;}
	}
	
}


void UFArbol:: Union(int X , int Y){
	link(this->Find (X) ,this->Find(Y) );
}

void UFArbol::imprimir(){
}




int main(){

	vector<Arista> aristas;
	vector<int> vertices;
	int cant_vertices;
	cout<<"cantidad de vertices "<<endl;

	cin>>cant_vertices;

 	 for(int i = 1 ; i<=cant_vertices ; i++){
 	 	vertices.push_back(i);
 	 }

     aristas  = grafo_aleatorio(cant_vertices);


     sort(aristas.begin(), aristas.end(), Arista());



    auto start = chrono::high_resolution_clock::now();

     kruskal_listas (aristas , vertices);
  auto finish = chrono::high_resolution_clock::now();
 auto d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
     cout<<"implementa listas "<< d << " [ns]" <<endl;


     start = chrono::high_resolution_clock::now();
     kruskal_arboles(aristas , vertices);
     finish = chrono::high_resolution_clock::now();
     d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
  cout<<"implementa arboles"<< d << " [ns]" <<endl;

 	return 0; 
 }  

void kruskal_listas(vector<struct Arista> Conjunto_Aristas , vector<int> v){
	UFLista arbol_lista;
	lista *L1 , *L2;
	for (int i = 0; i < v.size() ; ++i){
 	 	arbol_lista.MakeSet(v[i]);	
 	 }
 	 for(int i = 0; i < v.size() ; ++i){
 	 //	cout<<arbol_lista.Find(v[i])->representante;
 	 }
 	 for(int i=0 ; i< Conjunto_Aristas.size() ; i++){
 	 	L1= arbol_lista.Find(Conjunto_Aristas[i].empieza);
 	 	L2=	arbol_lista.Find(Conjunto_Aristas[i].termina);

 	 	
 	 	if(L1 != L2){

 	 		arbol_lista.Union( L1, L2);


 	 	}
 	 }
 	 
 	 


    }
  void kruskal_arboles (vector<struct Arista> Conjunto_Aristas , vector<int> v){

  	UFArbol* arbol_lista= new UFArbol (v.size()+1);
  	int L1 ,L2;
	for (int i = 0; i < v.size() ; ++i){
 	 	arbol_lista->MakeSet(v[i]);	
 	 }

 	 for(int i=0 ; i< Conjunto_Aristas.size() ; i++){

 	 	L1= arbol_lista->Find(Conjunto_Aristas[i].empieza);
 	 	L2=	arbol_lista->Find(Conjunto_Aristas[i].termina);

 	 	
 	 	if(L1 != L2){
 	 		
 	 		arbol_lista->Union( L1, L2);


 	 	}
 	 }
 	 arbol_lista->imprimir();
  }



  vector<struct Arista> grafo_aleatorio( int n ){

  	srand (time(NULL));
  	int num_vertices ,aux_nodo, coun_aristas;
  	vector<int > nodos;
  	vector<struct Arista> arcos;
  	Arista arista_aux;


  	for(int i = 0; i<=n ; i++){
  		nodos.push_back(0);
  	}
  	num_vertices=0;
  	while(num_vertices<n) 
  	{   aux_nodo= rand() % n+1;
  		if( find(nodos.begin(),nodos.end() ,aux_nodo) == nodos.end()){
  			nodos[num_vertices]=aux_nodo;
  			num_vertices++;
  		}
  	}
  	for(int i =0; i<n; i++ ){
  		if(i<n-1){
  		arista_aux.empieza=nodos[i];
  		arista_aux.termina=nodos[i+1];
  		arista_aux.peso = (rand()% (n/3))+1;
  		coun_aristas;
  		arcos.push_back(arista_aux);
  
  	}
  }

  // " conecciones aleatorias" 
  int vertice_aleatorio;
  for(int i = 0; i<n; i++){
  	for (int j = 0; j<30; j){

  		vertice_aleatorio = rand()%n;

 	if(vertice_aleatorio != i+1){
  		arista_aux.empieza=nodos[i];
  		arista_aux.termina=nodos[vertice_aleatorio];
  		arista_aux.peso = 2*n - ((rand()%(n/3))+1);
  		arcos.push_back(arista_aux);
  		j++;
  		coun_aristas++;
  		}
  	}
  }
   cout<<" aristas totales" <<coun_aristas<<endl;
  return arcos;
 
  }