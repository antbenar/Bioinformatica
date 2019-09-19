#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std; 


class AlineacionEstrella{	
private:
	template <typename T>
	void print(vector<vector<T>>& matrix){
		for(int i=0; i<matrix.size(); ++i){
			for(int j=0; j<matrix[0].size(); ++j){
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
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
	
	void calcularScores(){
		for(int i=0; i<secuencias.size(); ++i){
			//cout << secuencias[i] << endl;
			for(int j=i+1; j<secuencias.size(); ++j){
				pair<string,string> aux = alineacionGlobal(secuencias[i], secuencias[j],scores[i][j]);
				scores[j][i] = scores[i][j];
				
				mejoresSecuenciasFirst[i][j] = aux.first;
				mejoresSecuenciasFirst[j][i] = aux.first;
				mejoresSecuenciasSecond[i][j] = aux.second;
				mejoresSecuenciasSecond[j][i] = aux.second;
			}
		}
	}
	
public:
	vector<string> secuencias;
	vector<vector<int>> scores;
	vector<vector<string>> mejoresSecuenciasFirst;
	vector<vector<string>> mejoresSecuenciasSecond;
	
	AlineacionEstrella(vector<string>& secuencias_):secuencias(secuencias_), scores(secuencias.size(),vector<int>(secuencias.size(),0)), mejoresSecuenciasFirst(secuencias.size(),vector<string>(secuencias.size(),"")), mejoresSecuenciasSecond(secuencias.size(),vector<string>(secuencias.size(),"")){
		calcularScores();
		print(mejoresSecuenciasFirst);
		print(mejoresSecuenciasSecond);

		int max = -1000000;
		int index = -1;
		
		for(int i=0; i<secuencias.size(); ++i){
			int sum = 0;
			for(int j=0; j<secuencias.size(); ++j)
				sum+=scores[i][j];

			if(sum>max){
				max = sum;
				index = i;
			}
		}
		
		//algoritmo para alinearlos
		cout<< "se tomo como base la secuencia numero: " << index << endl;
		
		//-----------------FUNCIONES ENCONTRAR PIVOT
		string pivot = mejoresSecuenciasFirst[index][(index+1)%mejoresSecuenciasFirst.size()];
		
		for(int i=0; i < mejoresSecuenciasFirst.size(); ++i){
			if( i != index ){
				int pos1 = 0, pos2 = 0;
				while( pos1 < pivot.size() && pos2 < mejoresSecuenciasFirst[index][i].size()){
					if(mejoresSecuenciasFirst[index][i][pos2] != pivot[pos1]){
						if(pivot[pos1] == '_'){
							++pos1;
						}
						else{//mejoresSecuenciasFirst[index][i][pos2] == '_'
							pivot.insert(pivot.begin()+pos1,'_');	
							++pos2;
							++pos1;
						}
					}
					else {
						++pos2;
						++pos1;
					}
				}
				if(pos2 < mejoresSecuenciasFirst[index][i].size()){//completar con el substring faltante
					string temp(mejoresSecuenciasFirst[index][i].size()-pos2,'_');
					pivot+=temp;
				}
			}
		}
	
		//-----------------FUNCIONES ALINEAR CADENAS
		vector<string> result;
		result.push_back(pivot);
		
		for(int i=0; i < mejoresSecuenciasSecond[index].size(); ++i){
			if(i == index)continue;
			int posSec = 0;
			string auxSequence = "";
			for(int j=0; j < pivot.size(); ++j){
				if(mejoresSecuenciasFirst[index][i][posSec] == pivot[j]){
					auxSequence += mejoresSecuenciasSecond[index][i][posSec];
					++posSec;
				}
				else{//pivot has a new gap 
					auxSequence += '_';
				}
			}
			result.push_back(auxSequence);
		}

		/*for(int j=0; j < result.size(); ++j)
			cout<<result[j]<<endl;
		*/
	}

};



