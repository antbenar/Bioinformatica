#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <queue> 

using namespace std; 


class Aditivo{	
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
	
	
	int energia(string a){
		const int p = 2;
		const int q = 1;
		bool nuevoRompimiento = true;
		int result = 0;
		
		for(int i=0; i<a.size(); ++i){
			if(a[i] == '_'){
				if(i==0 && nuevoRompimiento){
					result += q;
					nuevoRompimiento = false;
				}
				else if(nuevoRompimiento) {
					result += p;
					nuevoRompimiento = false;
				}
				else result += q;
			}
			else nuevoRompimiento = true;
		}
		return result;
	}
	
	struct ss{
		string cur1;
		string cur2;
		int i, j;
		ss(int i_, int j_, string cur1_, string cur2_):cur1(cur1_), cur2(cur2_), i(i_), j(j_){}
	};
	
	///------------------------------------------------MODO CON PILAAAAA
	pair<string, string> btGlobalPile(string a, string b, vector<vector<int>>& matrix){	//backtracking de la matriz
		stack<ss*> btStack;
		btStack.push(new ss(matrix.size()-1, matrix[0].size()-1, "", ""));
		
		int minEnergy = 10000;
		pair<string, string> curResult;
		int count = 0;
		
		while(!btStack.empty() and count < 5000){
		//while(!btStack.empty()){
			int i = btStack.top()->i;
			int j = btStack.top()->j;
			string cur1 = btStack.top()->cur1;
			string cur2 = btStack.top()->cur2;
			
			ss* aux = btStack.top();
			btStack.pop();
			delete aux;			
			
			if(i == 0){
				string temp(j,'_');
				string aux1 = temp + cur1;
				string aux2 = a.substr(0,j) + cur2;
				
				int energia_ = energia(aux1) + energia(aux2);
				if(minEnergy > energia_){
					curResult = make_pair(aux1, aux2);
					minEnergy = energia_;
				}
				count++;
				continue;
			}
			else if(j == 0){
				string temp(i,'_');
				string aux1 = a.substr(0,i) + cur1;
				string aux2 = temp + cur2;
				
				int energia_ = energia(aux1) + energia(aux2);
				if(minEnergy > energia_){
					curResult = make_pair(aux1, aux2);
					minEnergy = energia_;
				}
				count++;
				continue;
			}
			
			if( a[i-1] == b[j-1] and matrix[i][j] - matrix[i-1][j-1] == 1)
					btStack.push(new ss(i-1, j-1, a[i-1]+cur1, b[j-1]+cur2));
			
			else if( a[i-1] != b[j-1] and matrix[i][j] - matrix[i-1][j-1] == -1)
				btStack.push(new ss(i-1, j-1, a[i-1]+cur1, b[j-1]+cur2));
			
			if(matrix[i][j] - matrix[i-1][j] == -2)
				btStack.push(new ss(i-1, j, a[i-1]+cur1, "_"+cur2));
			
			if(matrix[i][j] - matrix[i][j-1] == -2)
				btStack.push(new ss(i, j-1, "_"+cur1, b[j-1]+cur2));
		}
		return curResult;
	}
	
	void globalDp(string a, string b, vector<vector<int>>& matrix){
		for(int i=1; i<a.size()+1; ++i){
			for(int j=1; j<b.size()+1; ++j){
				int temp = max(matrix[i-1][j] - 2, matrix[i][j-1] - 2);
				if(a[i-1] == b[j-1]) matrix[i][j] = max(matrix[i-1][j-1] + 1, temp);
				else matrix[i][j] = max(matrix[i-1][j-1] - 1, temp);
			}
		}
	}
	
	pair<string,string> alineacionGlobal(string a, string b, int& score){
		//********************************************inicializar matriz para calcular alineacion global
		vector<vector<int>> matrix(a.size() + 1, vector<int>(b.size() + 1, 0));
		for(int i=1; i<a.size()+1; ++i)
			matrix[i][0] = matrix[i-1][0] - 2;
			
			for(int j=1; j<b.size()+1; ++j)
				matrix[0][j] = matrix[0][j-1] - 2;
				
				globalDp(a, b, matrix);
				
				///******************************REALIZAR BACKTRACKING******************************************////
				//calcular la mejor aliniacion con menor energia
				score = matrix[a.size()][b.size()];
				
				return btGlobalPile(a, b, matrix);
	}
	
	double distancia (string& a, string& b){
		double iguales = 0;

		for(int i=0; i<a.size(); ++i){
			if(a[i] == b[i])
				iguales+=1;
		}
		
		return iguales/a.size()*10;
	}
	
	void inicializarMatrices(){
		for(int i=0; i<secuencias.size(); ++i){
			//cout << secuencias[i] << endl;
			for(int j=i+1; j<secuencias.size(); ++j){
				pair<string,string> aux = alineacionGlobal(secuencias[i], secuencias[j],scores[i][j]);
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
	
	int reducirMatriz( int min_i, int min_j, int& pos){
		//-----------------crear una nueva matriz y colocar los pesos que no se mueven en el lugar que les corresponde
		vector<vector<double>> nuevaMatriz(matrizDistancias.size()-1,vector<double>(matrizDistancias.size()-1,0));
		int i, j, k, z;
		int i_nueva, j_nueva;
		
		//-----operaciones reducir matriz
		z = matrizDistancias[min_i][min_j]/2;
		if(matrizDistancias[min_i][min_j] - z*2 <= 0){
			z = (z>1) ? (z-1) : 0;
		}
		double toSubtract = z*2.0;
		
		for(i=0; i<matrizDistancias.size(); ++i){
			for(j=0; j<matrizDistancias.size(); ++j){
				if(i!=j)
					matrizDistancias[i][j] -= toSubtract;
			}
		}
		
		//operaciones calcular propiedad triangular
		for(k=0; k<matrizDistancias.size(); ++k){
			for(i=0; i<matrizDistancias.size(); ++i){
				if(i == k) continue;
				for(j=i+1; j<matrizDistancias.size(); ++j){
					if(j == k) continue;
					if(matrizDistancias[i][j] == matrizDistancias[i][k] + matrizDistancias[k][j]){
						pos = k;
					}
				}
			}
		}
		
		cout << endl << "-----------------matriz distancias reducida: " << endl;
		print(matrizDistancias);
		
		//cuando no cumple la propiedad triangular
		if(pos == -1) return -1;	
		
		
		
		//----------reducir matriz
		
		for(i=0, i_nueva=0 ; i<matrizDistancias.size(); ++i){
			if(i==pos)continue;
			for(j=0, j_nueva=0; j<matrizDistancias.size(); ++j){
				if(j!= pos){
					//cout << "i: " << i << ", j:" << j << endl;
					//cout << "---i_nueva: " << i_nueva << ", j_nueva:" << j_nueva << endl;
					nuevaMatriz[i_nueva][j_nueva] = matrizDistancias[i][j];
					++j_nueva;
				}
			}
			++i_nueva;
			//print(nuevaMatriz);
		}

		matrizDistancias.clear();
		matrizDistancias = nuevaMatriz;
		return z;
	}
	
	void construirArbol(stack <pair<int,int>> historial){
		double distancia;
		int pos;
		int base1 = historial.top().first; historial.pop();
		int base2 = historial.top().first; historial.pop();
		bool par = false;
		
		cout << endl << endl << "__________________________ARBOL_________________" << endl << endl;
		cout << "\t\t\t" << base1 << endl;
		cout << "\t\t\t|" << endl;
		while (!historial.empty()) 
		{ 
			pos = historial.top().first; 
			//distancia = matrizDistanciasOriginal[base1][pos] - historial.top().second; 
			distancia = historial.top().second; 
			historial.pop();
			cout << "\t\t\t|" << endl;
			cout << "\t\t\t|" << endl;
			
			if(par) cout << "\t" << pos << "------" << distancia << "------"  << endl;
			else cout << "\t\t\t------" << distancia << "------" << pos << endl;
			
			par = !par;
			
			cout << "\t\t\t|" << endl;
			cout << "\t\t\t|" << endl;
		} 
		cout << "\t\t\t|" << endl;
		cout << "\t\t\t" << base2 << endl;
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
		int pos;
		stack <pair<int,int>> historial;
		
		//-posiciones de la matriz
		for(int i=0; i<matrizDistancias.size(); ++i){
			clusters[i][0] = i;
		}
		
		
		for(int i=0; matrizDistancias.size() != 2 ; ++i){
			cout << "_____________________________________________________________iteracion " << i << endl;
			cout << endl << "-----------------matriz distancias: " << endl;
			print(matrizDistancias);
			
			pair<int, int> positions = getMinPos(matrizDistancias);
			pos = -1;
			int z = reducirMatriz(positions.first, positions.second, pos);	
			if(pos == -1){
				cout << endl << "------NO CUMPLE CON LA PROPIEDAD TRIANGULAR------" << endl;
				return;
			}
			
			
			historial.push(make_pair(clusters[pos][0], z));
			clusters.erase(clusters.begin()+pos);	
			
		}	
		cout << "_____________________________________________________________ultima iteracion " << endl;
		cout << endl << "-----------------matriz distancias: " << endl;
		print(matrizDistancias);
		
		historial.push(make_pair(clusters[0][0], 0));
		historial.push(make_pair(clusters[1][0], 0));
		construirArbol(historial);
	}
	
	
	Aditivo(vector<string>& secuencias_):
		secuencias(secuencias_), 
		matrizDistancias(secuencias.size(),vector<double>(secuencias.size(),0)), 
		mejoresSecuenciasFirst(secuencias.size(),vector<string>(secuencias.size(),"")), 
		mejoresSecuenciasSecond(secuencias.size(),vector<string>(secuencias.size(),"")),
		scores(secuencias.size(),vector<int>(secuencias.size(),0)),
		clusters(matrizDistancias.size(), vector<int>(1,0))
	{
		inicializarMatrices();
		matrizDistanciasOriginal = matrizDistancias;
		desarrollo();
	}
	
	Aditivo(vector<vector<double>>& matrizDistancias_): 
		matrizDistancias(matrizDistancias_), 
		matrizDistanciasOriginal(matrizDistancias_),
		clusters(matrizDistancias.size(), vector<int>(1,0))
	{
		desarrollo();
	}
};
