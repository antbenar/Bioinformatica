#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <queue> 

using namespace std; 

class node{
public:
	node* izq;
	node* der;
	node* parent;
	vector<int> nombre;
	double distanciaUnida;
	double acumulado;

	node(vector<int> nombre, double distanciaUnida, double acumulado, node* parent, node* izq, node* der):
		nombre(nombre), 
		distanciaUnida(distanciaUnida), 
		acumulado(acumulado),
		parent(parent),
		izq(izq), 
		der(der){}
	
	node(vector<int> nombre, double distanciaUnida, double acumulado, node* parent):
		nombre(nombre), 
		distanciaUnida(distanciaUnida), 
		acumulado(acumulado),
		parent(parent),
		izq(nullptr), 
		der(nullptr){}
};


class Tree{
public:
	node* root;
	
	Tree(){
		root = nullptr;
	}
	
	node* search(node* temp, vector<int> A){
		if(temp == NULL) 
			return nullptr;
		
		for(int i=0; i<A.size();++i){
			for(int j=0; j<temp->nombre.size();++j){
				if(temp->nombre[j] == A[i])
					cout << "ENCONTRADO!!--------";
					return temp;
			}
		}
		
		return search(temp->izq, A); 
		return search(temp->der, A); 
	}
	
	void insert(vector<int> nombreA, int nombeDatoAInsertar, double distanciaUnida){//insertar solo un nodo
		if(!root){
			root = new node({-1}, -1, distanciaUnida, nullptr);
			
			node* izq = new node({nombreA}, distanciaUnida, distanciaUnida, root);
			node* der = new node( {nombeDatoAInsertar}, distanciaUnida, distanciaUnida, root);
			
			root->der = der;
			root->izq = izq;
			return;
		}
	
		node* temp = search(root, nombreA);
		cout << "nombre: "; printNombre(temp->nombre); cout << "a buscar: "; printNombre(nombreA);
		if(temp){
			root = new node({-1}, -1, distanciaUnida + temp->acumulado, nullptr);
			
			temp->parent = root;
			node* der = new node( {nombeDatoAInsertar}, distanciaUnida, distanciaUnida, root);
			
			root->izq = temp;
			root->der = der;
		}		
	}
	
	void imprimir(node* pointer, string buffer = ""){
		if(pointer){
			imprimir(pointer->izq,buffer+"\t");
			cout<<endl;
			if(pointer->nombre[0] != -1){
				cout << buffer;  printNombre(pointer->nombre); cout<< "[" << pointer->distanciaUnida <<"]";
			}
			else cout << buffer << "---[" << pointer->distanciaUnida <<"]";
			cout<<endl; 
			imprimir(pointer->der,buffer+"\t");
		}
	}
	
	void printNombre(vector<int> A){
		//cout<< "nombree: __________" << endl;
		for(int i=0; i<A.size();++i){
			cout << A[i] << ", ";
		}
	}
};


class UPGMA{	
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
	double distancia(string a, string b){
		return 0.0;
	}
	
	void inicializarMatrices(){
		for(int i=0; i<secuencias.size(); ++i){
			//cout << secuencias[i] << endl;
			for(int j=i+1; j<secuencias.size(); ++j){
				pair<string,string> aux;//DARLE VALOR
				scores[j][i] = scores[i][j];
				
				//almacenar el mejor alineamiento por cada par de secuencias
				mejoresSecuenciasFirst[i][j] = mejoresSecuenciasFirst[j][i] = aux.first;
				mejoresSecuenciasSecond[i][j] = mejoresSecuenciasSecond[j][i] = aux.second;
				
				//calcular matriz de distancias
				double distancia_ = distancia(aux.first, aux.second);
				matrizDistancias[i][j] = matrizDistancias[j][i] = distancia_;
			}
		}
	}
	
	//-------------------------------------------------------FUNCIONES REDUCIR matrizDistancias
	pair<int, int> getMinPos(vector<vector<double>>& q){
		double min = 100000;
		int min_i, min_j;
		for(int i=0; i<q.size(); ++i){
			for(int j=i+1; j<q.size(); ++j){
				if(q[i][j] < min){
					min_i = i;
					min_j = j;
					min = q[i][j];
				}
			}
		}
		return make_pair(min_i, min_j);
	}
	
	
	double promedio(vector<int>cluster1, vector<int>cluster2){
		double promedio = 0;
		
		for(int i=0; i<cluster1.size(); ++i){
			for(int j=0; j<cluster2.size(); ++j){
				promedio+= matrizDistanciasOriginal[cluster1[i]][cluster2[j]];
			}
		}
		return promedio / (cluster1.size() * cluster2.size());
	}
	
	
	void reducirMatriz( int min_i, int min_j){
		//-----------------crear una nueva matriz y colocar los pesos que no se mueven en el lugar que les corresponde
		vector<vector<double>> nuevaMatriz(matrizDistancias.size()-1,vector<double>(matrizDistancias.size()-1,0));
		int i_nuevaMatriz = 1;
		int j_nuevaMatriz = 1;
		
		for(int i=0; i<matrizDistancias.size(); ++i){
			if(min_i != i && min_j != i){
				for(int j=0; j<matrizDistancias.size(); ++j){
					if(min_i != j && min_j != j){
						nuevaMatriz[i_nuevaMatriz][j_nuevaMatriz] = matrizDistancias[i][j];
						++j_nuevaMatriz;
					}
				}
				j_nuevaMatriz = 1;
				++i_nuevaMatriz;
			}
		}
		
		//insertamos los nuevos pesos del agrupamiento recien hecho en la columna 0 y en la fila 0
		int curPos = 1;
		for(int i = 0; i<nuevaMatriz.size(); ++i){
			if(i != min_i && i!= min_j){
				nuevaMatriz[0][curPos] = nuevaMatriz[curPos][0] = promedio(clusters[0],clusters[curPos]);
				++curPos;
			}
		}
		matrizDistancias.clear();
		matrizDistancias = nuevaMatriz;
	}
	
	
public:
	vector<string> secuencias;
	vector<vector<double>> matrizDistancias;
	vector<vector<double>> matrizDistanciasOriginal;
	
	vector<vector<string>> mejoresSecuenciasFirst;
	vector<vector<string>> mejoresSecuenciasSecond;
	vector<vector<int>> scores;
	
	vector<vector<int>> clusters;
	
	void desarrollo(){
		cout << "-----------------matriz distancias: " << endl;
		print(matrizDistancias);
		
		
		//-posiciones de la matriz
		for(int i=0; i<matrizDistancias.size(); ++i){
			clusters[i][0] = i;
		}
		
		Tree historial;
		
		for(int i=0; matrizDistancias.size() != 1 ; ++i){
			cout << "_____________________________________________________________iteracion " << i << endl;

			pair<int, int> positions = getMinPos(matrizDistancias);
			double distanciaUnida = matrizDistancias[positions.first][positions.second]/2;
			
			//------------------------------------------------------------INICIO IMPRIMIR NUEVOS CLUSTER
			cout << "se agruparon clusters " << positions.first << " y " << positions.second << " con distancia de: " << matrizDistancias[positions.first][positions.second] << endl;

			int pos1 = max(positions.first, positions.second);
			int pos2 = min(positions.first, positions.second);
			
			
			historial.insert(clusters[pos1],clusters[pos2][0],distanciaUnida);
			
			vector<int> aux(clusters[pos1]);
			aux.insert(aux.end(), clusters[pos2].begin(), clusters[pos2].end());
			
			clusters.erase(clusters.begin()+pos1);
			clusters.erase(clusters.begin()+pos2);
			clusters.insert(clusters.begin(),aux);
			
			cout << "clusters actuales: " << endl;
			print(clusters);
			//------------------------------------------------------------FIN IMPRIMIR NUEVOS CLUSTER
			
			reducirMatriz(positions.first, positions.second);	
			cout << "-----------------matriz distancias: " << endl;
			print(matrizDistancias);
		}	
		
		historial.imprimir(historial.root);
	}
	
	
	UPGMA(vector<string>& secuencias_):
		secuencias(secuencias_), 
		matrizDistancias(secuencias.size(),vector<double>(secuencias.size(),0)), 
		mejoresSecuenciasFirst(secuencias.size(),vector<string>(secuencias.size(),"")), 
		mejoresSecuenciasSecond(secuencias.size(),vector<string>(secuencias.size(),"")),
		scores(secuencias.size(),vector<int>(secuencias.size(),0))
	{
		//inicializarMatrices();
		//desarrollo();
	}
	
	UPGMA(vector<vector<double>>& matrizDistancias_): 
		matrizDistancias(matrizDistancias_), 
		matrizDistanciasOriginal(matrizDistancias_),
		clusters(matrizDistancias.size(), vector<int>(1,0))
	{
		desarrollo();
	}
};









