#include <iostream>
#include <vector>
#include <iomanip>

using namespace std; 

class node{
public:
	node* izq;
	node* der;
	vector<string> uniones;
	
	node(size_t tam):
		uniones(tam,""), 
		izq(nullptr), 
		der(nullptr){}
	
	node(string secuencia):
		uniones(secuencia.size(),""), 
		izq(nullptr), 
		der(nullptr)
	{
		for(int i=0; i<secuencia.size(); ++i){
			uniones[i] = uniones[i]+secuencia[i];
		}
	}
	
};


void imprimir(node* pointer, string buffer = ""){
	
	if(pointer){
		imprimir(pointer->izq,buffer+"\t");
		cout<<endl;
		
		cout << buffer << "["; 
		for(int i=0; i<pointer->uniones.size()-1;++i){
			cout << pointer->uniones[i] << ",";
		}cout << pointer->uniones[pointer->uniones.size()-1] << "]" << endl;

		
		cout<<endl; 
		imprimir(pointer->der,buffer+"\t");
	}
	
}


