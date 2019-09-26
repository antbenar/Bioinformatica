#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>
using namespace std; 


class ProgressiveAlignment{	
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
		
		//while(!btStack.empty() and count < 100){
		while(!btStack.empty()){
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
		double conGap = 0;
		double sinGap = 0;
		
		for(int i=0; i<a.size(); ++i){
			if(a[i] == '_' or b[i] == '_')
				conGap+=1;
		}
		
		sinGap = a.size() - conGap;
		return conGap/sinGap;
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

	//-----------------------------------------------------Funciones calcular Q
	double sumatoriaMatrizDistancias( int pos ){
		double result = 0;
		for(int i=0; i<matrizDistancias.size(); ++i){
			if(pos != i){
				result += matrizDistancias[pos][i];
			}
		}
		return result;
	}
	
	vector<vector<double>> calcularMatrizQ(){
		vector<vector<double>> q(matrizDistancias.size(),vector<double>(matrizDistancias.size(),0));
	
		double factor = 1/double(matrizDistancias.size()-2);
		
		for(int i=0; i<matrizDistancias.size(); ++i){
			for(int j=i+1; j<matrizDistancias.size(); ++j){
				q[i][j] = q[j][i] = matrizDistancias[i][j] - factor*( sumatoriaMatrizDistancias(i) + sumatoriaMatrizDistancias(j) );
			}
		}
		return q;
	}
	
	//-------------------------------------------------------FUNCIONES REDUCIR matrizDistancias
	pair<int, int> getMinPos(vector<vector<double>> q){
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
		for(int i = 0; i<matrizDistancias.size(); ++i){
			if(i != min_i && i!= min_j){
				nuevaMatriz[0][curPos] = nuevaMatriz[curPos][0] = (matrizDistancias[min_i][i] + matrizDistancias[min_j][i] - matrizDistancias[min_i][min_j])/2;
				++curPos;
			}
		}
		matrizDistancias.clear();
		matrizDistancias = nuevaMatriz;
	}
	
	
public:
	vector<string> secuencias;
	vector<vector<double>> matrizDistancias;
	
	vector<vector<string>> mejoresSecuenciasFirst;
	vector<vector<string>> mejoresSecuenciasSecond;
	vector<vector<int>> scores;
	
	
	void progressiveAlignment(){
		cout << "-----------------matriz distancias: " << endl;
		print(matrizDistancias);
		
		//-posiciones de la matriz
		vector<vector<int>> clusters(matrizDistancias.size(), vector<int>(1,0));
		for(int i=0; i<matrizDistancias.size(); ++i){
			clusters[i][0] = i;
		}
		
		
		for(int i=0; matrizDistancias.size() != 2 ; ++i){
			cout << "_____________________________________________________________iteracion " << i << endl;
			vector<vector<double>> q = calcularMatrizQ();
			cout << "-----------------Q matrix: " << endl;
			print(q);
			pair<int, int> positions = getMinPos(q);
			
			
			//------------------------------------------------------------INICIO IMPRIMIR NUEVOS CLUSTER
			cout << "se agruparon clusters " << positions.first << " y " << positions.second << " con Q-distance de: " << q[positions.first][positions.second] << endl;
			//cout << "se agruparon: " << pos[positions.first] << " - " << pos[positions.second] << endl;
			
			//---------quitar posiciones de mi vector
			int pos1 = max(positions.first, positions.second);
			int pos2 = min(positions.first, positions.second);
			
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
	}
	
	
	ProgressiveAlignment(vector<string>& secuencias_):
		secuencias(secuencias_), 
		matrizDistancias(secuencias.size(),vector<double>(secuencias.size(),0)), 
		mejoresSecuenciasFirst(secuencias.size(),vector<string>(secuencias.size(),"")), 
		mejoresSecuenciasSecond(secuencias.size(),vector<string>(secuencias.size(),"")),
		scores(secuencias.size(),vector<int>(secuencias.size(),0))
	{
		
		inicializarMatrices();
		progressiveAlignment();
	}
	
	ProgressiveAlignment(vector<vector<double>>& matrizDistancias_): matrizDistancias(matrizDistancias_)
	{
		progressiveAlignment();
	}
};









