#include <iostream>
#include <chrono>
#include <cstdlib>
#include <algorithm>  
#include <vector>  
#include <time.h>

using namespace std;
pair<int,int> busqueda1(int , vector<int>,int );
pair<int,int> busqueda2(int , vector<int>,int );
pair<int,int> busqueda3(int , vector<int>,int );
int main()
{
	vector<int> num;
	int c, X ;
    srand(time(NULL));
    int n;
    cout<<"cantidad de numeros"<<endl;   
    cin>>n;


    for(c = 0; c < n; c++)
    {
    	num.push_back(-n/2 + rand() % (n + n));
        
    } 
    X= num[(rand() % (n))];
    cout << "numero a encontrar"<< X <<endl;

    sort( num.begin(),num.end());
    /*for (c = 0; c < n; c++){
    	cout<<num[c]<< " ";
    }*/
    auto start = chrono::high_resolution_clock::now();
     busqueda1(X,num,n);
    auto finish = chrono::high_resolution_clock::now();
    auto d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    cout <<"total time busqueda1 "<< d << " [ns]" << " \n";

     start = chrono::high_resolution_clock::now();
     busqueda2(X,num,n);
     finish = chrono::high_resolution_clock::now();
    d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    cout <<"total time busqueda2 "<< d << " [ns]" << " \n";


    start = chrono::high_resolution_clock::now();
     busqueda3(X,num,n);
     finish = chrono::high_resolution_clock::now();
     d = chrono::duration_cast<chrono::nanoseconds> (finish - start).count();
    cout <<"total time busqueda3 "<< d << " [ns]" << " \n";
    

}
/*busqueda secuencial para encontrar la suma recorre n veces el arrglo por cada numero que contiene 
por lo que su complejidad es o(n^2)*/
pair<int,int> busqueda1(int x , vector<int> A, int m){
	pair <int , int > pos;

	for(int i=0;i< m;i++){

		for(int j=0;j<m;j++){
			if(A[i]+A[j]==x){
				pos.first=i;
				pos.second=j;
			//	cout<< "numero encontrado algoritmo 1 "<<A[i]<<","<<A[j]<<endl;
				//return  pos;

			}

		}
		
	}
 cout<< "numero no encontrado algoritmo 1 "<<endl;
	pos.first=-1;
	pos.second=-1;
	return pos;
}
/*recorre el arreglo secuencialmente O(n) , calcula el  resto entre el numero seleccionado y el numero buscado , 
luego para encontrar el resto realiza una busqueda binaria O (log(n)) , resultando una complejidad de O(nlog(n))  )*/

pair<int,int> busqueda2(int x , vector<int> A , int m ){
	pair<int , int > pos;
	int resto ,inf,mid,sup;
	

	for(int i=0; i<m ; i++){
		resto = x-A[i];
    inf=0;
    sup= m-1;

		while (inf <= sup)
		{
      mid = (inf + sup)/2;

      if (A[mid] == resto && i != mid  ){
      	pos.first=i;
        pos.second=mid;
        //cout<< "numero encontrado algoritmo 2 "<<A[i]<<","<<A[mid]<<endl;
       //return pos;
     }
      if (resto < A[mid])
            sup=mid-1;
      else
      	inf=mid+1;
    }
  }
  pos.first=-1;
  pos.second=-1;
  cout<< "numero no encontrado algoritmo 2 "<<endl;
  return pos;
}
/*Toma 2 elementos de cada extremo del arreglo con un limite superior e inferior ,  
compara su suma con el numero buscado , si esta suma es mayor al numero buscado el limite superior se deplaza una posición a la izquierda y
si esta suma es menor el limite inferior se desplaza  una posición a la derecha , en total el arreglo es recorrido solo una vez
por lo que la complejidad es O(n)   */
pair<int,int> busqueda3(int x , vector<int> A , int m ){
  pair<int , int > pos;
  int inf = 0;
  int sup = m-1;
  while ( inf < sup){
    if (A[inf] + A[sup] == x )
    {   pos.first=inf;
        pos.second=sup;
        //cout<< "numero encontrado algoritmo 3  "<<A[inf]<<","<<A[sup]<<endl;
       // return pos;
      }
      if (A[inf]+A[sup] < x ){
         inf++;
      }
      else{
        sup--;

      }
       
  }
  pos.first=-1;
  pos.second=-1;
  cout<< "numero  no encontrado  algoritmo 3 "<<endl;
  return pos;
}