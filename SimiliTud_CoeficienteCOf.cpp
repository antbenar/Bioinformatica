#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <math.h>
using namespace std; 

class Operacion{
public:
	virtual double operator() (double value1, double value2){};
};

class Min: public Operacion
{ public: 
	double operator () (double value1, double value2) const { 
		if(value1<value2)
			return value1;
		return value2;
		//return min(value1,value2); 
	} 
}; 
class Max: public Operacion
{ public: 
	double operator () (double value1, double value2) const { 
		return max(value1,value2); 
	} 
}; 
class Avg: public Operacion
{ public: 
	double operator () (double value1, double value2) const { 
		return (value1+value2)/2; 
	} 
}; 


class EstrategiaSimilitud{	
private:
	
	//---------------------OPERACIONES MATRIZ
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
	
	double avgMatrix(vector<vector<double>>& matrix){
		double result = 0;
		double dividendo = (matrix.size()*matrix.size() - matrix.size())/2;
		for(int i=1; i<matrix.size(); ++i){
			for(int j=0; j<i; ++j){
				result+=matrix[i][j];
			}
		}
		return result/dividendo;
	}
	
	double Varianza(vector<vector<double>>& matrix){
		double result = 0;
		double dividendo = (matrix.size()*matrix.size() - matrix.size())/2;
		double mean = avgMatrix(matrix);
		
		for(int i=1; i<matrix.size(); ++i){
			for(int j=0; j<i; ++j){
				result+=(matrix[i][j]-mean)*(matrix[i][j]-mean);
			}
		}
		return result/dividendo;
	}
	
	double Covrianza(vector<vector<double>>& matrix1, vector<vector<double>>& matrix2){
		double result = 0;
		double aux1;
		double aux2;
		double dividendo = (matrix1.size()*matrix1.size() - matrix1.size())/2;
		double mean1 = avgMatrix(matrix1);
		double mean2 = avgMatrix(matrix2);
		
		for(int i=1; i<matrix1.size(); ++i){
			for(int j=0; j<i; ++j){
				aux1 = matrix1[i][j]-mean1;
				aux2 = matrix2[i][j]-mean2;
				result+= aux1*aux2;
			}
		}
		return result/dividendo;
	}
	
	double calcularCoeficienteCofenetico(){
		double cov = Covrianza(matrizDistancias,matrizCofenetica);
		return cov*cov/sqrt(Varianza(matrizDistancias)*Varianza(matrizCofenetica));
		
	}
	//---------------------FIN OPERACIONES MATRIZ
	
	
	
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
	
	
	void reducirMatrizMin( int min_i, int min_j){
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
				//cout << matrizDistancias[min_i][i]<<",,,,"<<matrizDistancias[min_j][i] << "->" << op(matrizDistancias[min_i][i],matrizDistancias[min_j][i]) << endl ;
				nuevaMatriz[0][curPos] = nuevaMatriz[curPos][0] = min(matrizDistancias[min_i][i],matrizDistancias[min_j][i]);
				++curPos;
			}
		}
		matrizDistancias.clear();
		matrizDistancias = nuevaMatriz;
	}
	
	void reducirMatrizMax( int min_i, int min_j){
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
				//cout << matrizDistancias[min_i][i]<<",,,,"<<matrizDistancias[min_j][i] << "->" << op(matrizDistancias[min_i][i],matrizDistancias[min_j][i]) << endl ;
				nuevaMatriz[0][curPos] = nuevaMatriz[curPos][0] = max(matrizDistancias[min_i][i],matrizDistancias[min_j][i]);
				++curPos;
			}
		}
		matrizDistancias.clear();
		matrizDistancias = nuevaMatriz;
	}
	
	void reducirMatrizAvg( int min_i, int min_j){
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
				//cout << matrizDistancias[min_i][i]<<",,,,"<<matrizDistancias[min_j][i] << "->" << op(matrizDistancias[min_i][i],matrizDistancias[min_j][i]) << endl ;
				nuevaMatriz[0][curPos] = nuevaMatriz[curPos][0] = (matrizDistancias[min_i][i]+matrizDistancias[min_j][i])/2;
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
	
	vector<vector<double>>matrizCofenetica;
	
	void desarrollo(string tipoOperacion){
		cout << "-----------------matriz distancias: " << endl;
		print(matrizDistancias);
		
		//-posiciones de la matriz
		vector<vector<int>> clusters(matrizDistancias.size(), vector<int>(1,0));
		for(int i=0; i<matrizDistancias.size(); ++i){
			clusters[i][0] = i;
		}
		
		
		for(int i=0; matrizDistancias.size() != 1 ; ++i){
			cout << "_____________________________________________________________iteracion " << i << endl;
			
			pair<int, int> positions = getMinPos(matrizDistancias);
			double distanciaUnida = matrizDistancias[positions.first][positions.second];
			//------------------------------------------------------------INICIO IMPRIMIR NUEVOS CLUSTER
			cout << "se agruparon clusters " << positions.first << " y " << positions.second << " con distancia de: " << distanciaUnida << endl;
			
			int pos1 = max(positions.first, positions.second);
			int pos2 = min(positions.first, positions.second);
			
			vector<int> aux(clusters[pos1]);
			aux.insert(aux.end(), clusters[pos2].begin(), clusters[pos2].end());
			
			//-----ANADIR A COFENETICA
			int p1, p2;
			for(int i=0; i<clusters[pos1].size();++i){
				p1= clusters[pos1][i];
				for(int j=0; j<clusters[pos2].size();++j){
					p2 = clusters[pos2][j];
					if(matrizCofenetica[p1][p2] == 0)
						matrizCofenetica[p1][p2] = matrizCofenetica[p2][p1] = distanciaUnida;
				}
			}
			//-----FIN ANADIR A COFENETICA
			
			clusters.erase(clusters.begin()+pos1);
			clusters.erase(clusters.begin()+pos2);
			clusters.insert(clusters.begin(),aux);
			
			cout << "clusters actuales: " << endl;
			print(clusters);
			//------------------------------------------------------------FIN IMPRIMIR NUEVOS CLUSTER
			if(tipoOperacion == "min") {
				reducirMatrizMin(positions.first, positions.second);	
			}
			else if(tipoOperacion == "max") {
				reducirMatrizMax(positions.first, positions.second);	
			}
			else {
				reducirMatrizAvg(positions.first, positions.second);	
			}
			
			cout << "-----------------matriz distancias: " << endl;
			print(matrizDistancias);
		}		
	}
	
	
	EstrategiaSimilitud(vector<string>& secuencias_, string tipoOperacion):
		secuencias(secuencias_), 
		matrizDistancias(secuencias.size(),vector<double>(secuencias.size(),0)), 
		matrizCofenetica(secuencias.size(),vector<double>(secuencias.size(),0)),
		mejoresSecuenciasFirst(secuencias.size(),vector<string>(secuencias.size(),"")), 
		mejoresSecuenciasSecond(secuencias.size(),vector<string>(secuencias.size(),"")),
		scores(secuencias.size(),vector<int>(secuencias.size(),0))
	{
		inicializarMatrices();
		desarrollo(tipoOperacion);
		/*
		if(tipoOperacion == "min") {
		//Min op;
		desarrollo(op);
		}
		else if(tipoOperacion == "max") {
		//Max op;
		desarrolloMax(op);
		}
		else {
		//Avg op;
		desarrolloAvg(op);
		}
		*/
	}
	
	EstrategiaSimilitud(vector<vector<double>>& matrizDistancias_, string tipoOperacion): 
		matrizDistancias(matrizDistancias_),
		matrizCofenetica(matrizDistancias_.size(),vector<double>(matrizDistancias_.size(),0))
	{
		inicializarMatrices();
		desarrollo(tipoOperacion);
		cout << "coeficiente COfenetico es: " << calcularCoeficienteCofenetico() << endl;
	}
};
