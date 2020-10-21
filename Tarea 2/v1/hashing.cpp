#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
// bucket segundo nivel
class bucket_ {

  int p= 10000019;
  int dat[3];// almacena la tripleta a,b,m
  int *B;// almacena las claves 
public:
  bucket_ (int);
  ~bucket_();
 void hash( vector<int> );
 void limpiar_bucket();// limpia el bucket es utilizada cuando la funcion hash  del segundo nivel genera coliciones
 void elementos();
 bool busca(int);

};

/*tabla hash*/
class tablahash{

private:
  int n,p,a,b;
  vector<bucket_*> T;// vector de bucket para el segundo nivel

public: 
  tablahash(int);
  ~tablahash();
  void insertar(vector<int>);// comienza la insercion en un bucket con un vector de los elementos direccionados en el primer nivel
  void imprimir();
  bool buscar(int);//busca un elemento en la tabla

};



int main(void) {
  vector<int> prueba;
  int cantidad , num;
  bool aux;
  cout<< "cantidad de numeros "<<endl;
  cin>>cantidad;
  srand(time(NULL));

 /*while(cantidad > prueba.size()){// creado un set al azar
   num= rand()% 10000019;
   aux=true;
  for (int i=0; i< prueba.size() ; i++ )
  {
    if(prueba[i]== num){
      aux= false;
      break;
    }
  }*/

 
  for (int i=0; i< cantidad ; i++ ){

    prueba.push_back(i);
 }
 //  sort(prueba.begin(), prueba.end());// conjunto de elementos ordenados

 /*for(int i=0 ; i< prueba.size(); i++ ){
  cout<< prueba[i]<< " ";
 }*/
 auto start = chrono::high_resolution_clock::now();
 tablahash *TBL = new tablahash(cantidad);

 TBL->insertar(prueba);

 auto finish = chrono::high_resolution_clock::now();
 auto d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
 cout<<"total time hash "<< d << " [ns]" <<endl;

 //TBL->imprimir();
 bool D;
 D=true; int bsu;
 while(D){
  
  cout<<"buscar elemento"<< endl;
  cin>>bsu;
 if(TBL->buscar(bsu)){
  cout<<" elemento encontrado : "<< bsu <<endl;
 }else cout<<" elemento NO encontrado : "<< bsu <<endl;
 cout<<"quieres buscar mas elementos ? 1 si , 0 No"<< endl;
 cin>>D;
 }

 }


 tablahash::tablahash(int cant){
  p=10000019;// primo siguiente a 10 millones
  n = cant;
  T.resize(n);// se ajusta el tamaño de la tabla a n
  
  for (int i = 0; i < n; i++)
  {
    T[i]=NULL;
  }
}
 
void tablahash::insertar(vector<int> ins){
  vector<int> temp[n];
  int coliciones;
  coliciones= 4*n+1;
  srand(time(NULL));
 cout<<"n->"<< n<<endl; 

  while(coliciones > 4*n){ // comprobando que el total de coliciones sea menor a 4 *n 
    coliciones=0;

    a=rand()%(p);
    b=rand()%(p);

      for(int i = 0; i<ins.size();i++){

        temp[(((a*ins[i]+b)%p)%n)].push_back(ins[i]);
      }
       for(int i=0; i<n; i++){// contando cada coincidencia en el primer nivel

        if(temp[i].size()>0){
          coliciones = coliciones + pow(temp[i].size(),2);
        }
      }

   }

    for(int i =0 ; i<n; i++){// se imprime la tabla que deberia quedar
     //cout<<i<< "  --->> "; 
    for(int j = 0 ;j<temp[i].size();j++){
     // cout<<"  "<<temp[i][j];
    }
    //cout<<endl;
   }


  // cout<<coliciones <<" A = "<<a<<" B = "<< b << endl;  

    for(int i = 0; i< n ; i++){// comienza la insercion por cada bucket 
        int tam = temp[i].size();
       if(tam > 0){

      T[i]= new bucket_(tam);// se crea el bucket correspondiente 

      T[i]->hash(temp[i]);// se le entrega el vector de elementos que cayeron en el bucket i

    }
    
  }
}
bool tablahash::buscar(int x){
  int it;
  it=(((a*x+b)%p)%n);
  if(T[it]){
  if(T[it]->busca(x)){
    return true;
  }
  else return false;
}
else return false;

}

void tablahash::imprimir(){

  for (int i = 0; i <n ; ++i)
  {
    if(T[i]!=0){
      cout<<"bucket  "<<i<<endl;
    T[i]->elementos();
  }

  }
}


/*se inicializa un bucket vacio */
 bucket_ ::bucket_(int nh){

  dat[2]=nh*nh;// asignado tamaño del bucket
  B= new int [nh*nh];
  for (int it = 0; it < nh*nh; it++ ){
      this->B[it]= -2;
    }
}

 

 void bucket_ :: hash(vector<int> v){
  
  int a1, b1,tamv ,coliciones,dir; coliciones = 1; 
  tamv = v.size();

  while(coliciones >= 1){
    coliciones=0;
    a1=rand()%(p); 
    b1=rand()%(p);

    for(int i = 0; i<tamv;i++){

      dir=(((a1*v[i]+b1)%p)%(tamv*tamv));// se aplica funcion hash de segundo nivel

    if(this->B[dir] > -1) { // comprueba que no haya un elemento ya insertado en la posicion i (colición)
      this->limpiar_bucket();
      coliciones++;
      break;
    }else{
     this->B[dir]=v[i];// si no hay colicion se agrega el valor
    }
   }
}

dat[0]=a1;// finalmente  guarda el a y b que no generan colicion 
dat[1]=b1;

 }
bool bucket_:: busca(int y){

  if(B[(((dat[0]*y+dat[1])%p)%dat[2])]== y){
    return true;
  }
  else return false;
}

 void bucket_ :: limpiar_bucket(){

  for (int i = 0; i< dat[2]; i++){
    this->B[ i ]= -2;
   }
  
 }


 void bucket_ :: elementos (){
  //cout<<"a="<<dat [0]<<"b="<<dat[1]<< endl;
  for (int i =0;i<dat[2]; i++){
    if(B[i] > -2){
     // cout<<B[i]<<"   ";

    }

  }
  //cout<<endl;


 }
