#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <queue> 
#include "tree.hpp"

#define MAX 10000000
using namespace std; 


class Parsimonia{	
private:
	template <typename T>
	void print(vector<vector<T>>& matrix){
		std::cout << std::fixed;
		std::cout << std::setprecision(2);
		
		cout << endl;
		for(int i=0; i<matrix.size(); ++i){
			for(int j=0; j<matrix[i].size(); ++j){
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}

	vector<node*> calcularParsimonia(vector<node*> forest, int& numCambios){
		size_t tam = secuencias[0].size();
		string interseccion;
		
		//metodo parsimonia
		while(forest.size() > 1){
			vector<node*> newForest;
			
			for(int i=1; i<forest.size();i+=2){
				node* root = new node(tam);
				
				root->izq = forest[i-1];
				root->der = forest[i];
				
				
				for(int j=0; j < tam; ++j){
					interseccion = "";
					
					for(int k=0; k < forest[i]->uniones[j].size(); ++k){
						if(forest[i-1]->uniones[j][k] == forest[i]->uniones[j][k]){
							interseccion += forest[i-1]->uniones[j][k];
						}
					}
					
					if(interseccion.size() > 0){
						root->uniones[j] = interseccion;
					}
					else{
						root->uniones[j] = forest[i-1]->uniones[j] + forest[i]->uniones[j];
						numCambios += 1;
					}
				}
				newForest.push_back(root);
			}
			
			if(forest.size()%2==1)newForest.push_back(forest[forest.size()-1]);
			forest = newForest;
		}
		return forest;
	}


public:
	vector<string> secuencias;
	
	void desarrollo(){		
		vector<node*> forest, auxForest;
		int numCambios = MAX, curCambios = 0;
		
		do {
			//inicializar forest con las secuencias permutadas
			auxForest.clear();
			for(int i=0; i<secuencias.size();++i){
				auxForest.push_back(new node(secuencias[i]));
			}
			
			//calcular mediante Parsimonia
			auxForest = calcularParsimonia(auxForest, curCambios);
			
			//evaluar si tenemos el arbol con la menor cantidad de cambios
			if(curCambios < numCambios){
				forest = auxForest;
				numCambios = curCambios;
			}
			
		} while ( next_permutation(secuencias.begin(),secuencias.end()) );
		
		
		cout << "numero de cambios: " << numCambios << endl << endl;
		imprimir(forest[0]);
	}
	
	
	Parsimonia(vector<string>& secuencias_):secuencias(secuencias_)
	{
		desarrollo();
	}
	
};
