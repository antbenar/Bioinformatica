#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
using namespace std; 


class AlineacionesGlobalLocal{	
private:
	void swap(string& a, string& b){
		string aux = a;
		a = b;
		b = aux;
	}
	
	struct ss{
		string cur1;
		string cur2;
		int i, j;
		ss(int i_, int j_, string cur1_, string cur2_):cur1(cur1_), cur2(cur2_), i(i_), j(j_){}
	};
	
	///------------------------------------------------MODO CON PILAAAAA
	void btGlobalPile(vector<vector<int>>& matrix, vector<pair<string,string>>& seqResult){	//backtracking de la matriz
		stack<ss*> btStack;
		btStack.push(new ss(matrix.size()-1, matrix[0].size()-1, "", ""));
		
		int count = 0;
		
		//while(!btStack.empty() and count < 100){
		while(!btStack.empty()){
			//if(seqResult.size()%10000)cout seqResult.size();
			
			int i = btStack.top()->i;
			int j = btStack.top()->j;
			string cur1 = btStack.top()->cur1;
			string cur2 = btStack.top()->cur2;
			
			ss* aux = btStack.top();
			btStack.pop();
			delete aux;
			
			if(i == 0){
				string temp(j,'_');
				seqResult.push_back(make_pair(temp + cur1, a.substr(0,j) + cur2));
				count++;
				continue;
			}
			else if(j == 0){
				string temp(i,'_');
				seqResult.push_back(make_pair(a.substr(0,i) + cur1, temp + cur2));
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
	}
	
	void globalDp(vector<vector<int>>& matrix){
		for(int i=1; i<a.size()+1; ++i){
			for(int j=1; j<b.size()+1; ++j){
				int temp = max(matrix[i-1][j] - 2, matrix[i][j-1] - 2);
				if(a[i-1] == b[j-1]) matrix[i][j] = max(matrix[i-1][j-1] + 1, temp);
				else matrix[i][j] = max(matrix[i-1][j-1] - 1, temp);
			}
		}
	}
	
	vector<pair<string, string>> btLocal(vector<vector<int>>& matrix){	//backtracking de la matriz
		vector < pair<int,int> > indexes;	//I store the i and j index
		
		int max = -1;
		for(int i=1; i<a.size()+1; ++i){
			for(int j=1; j<b.size()+1; ++j){
				if(matrix[i][j] > max){
					max = matrix[i][j];
					indexes.clear();//nuevos max
					indexes.push_back(make_pair(i,j));
				}
				else if(matrix[i][j] == max){
					indexes.push_back(make_pair(i,j));
				}
			}
		}
		
		vector<pair<string, string>> result;
		
		for(int i=0; i<indexes.size(); ++i){
			int i_max = indexes[i].first;
			int j_max = indexes[i].second;
			
			string aux1(b.size()-j_max,'_');
			string aux2(a.size()-i_max,'_');
			string temp1 = a.substr(i_max) + aux1;
			string temp2 = aux2 + b.substr(j_max);
			
			string substr="";
			
			
			while(i_max> 0 && j_max>0 && matrix[i_max][j_max]>0){
				substr = a[--i_max] + substr;
				/*temp1 = a[--i_max] + temp1;
				temp2 = a[i_max] + temp2;*/
				--j_max;
			}
			cout<<"substrings: " << substr << endl;
			
			
			string aux3(j_max,'_');
			string aux4(i_max,'_');
			temp1 = a.substr(0,i_max) + aux3 + substr + temp1;
			temp2 = aux4 + b.substr(0,j_max) + substr + temp2;
			
			result.push_back(make_pair(temp1, temp2));
		}
		
		return result;
	}
	
	void localDp(vector<vector<int>>& matrix){
		for(int i=1; i<a.size()+1; ++i){
			for(int j=1; j<b.size()+1; ++j){
				if(a[i-1] == b[j-1]) matrix[i][j] = max(matrix[i-1][j-1] + 1, 0);
			}
		}
	}
	
public:
	string a, b;

	AlineacionesGlobalLocal(string a_, string b_):a(a_), b(b_){
		if(b.size() > a.size()) swap(a,b);//para que la cadena mayor esté a la izquierda
	}
	
	void alineacionGlobal(){
		//********************************************inicializar matriz para calcular alineacion global
		vector<vector<int>> matrix(a.size() + 1, vector<int>(b.size() + 1, 0));
		for(int i=1; i<a.size()+1; ++i)
			matrix[i][0] = matrix[i-1][0] - 2;
			
		for(int j=1; j<b.size()+1; ++j)
			matrix[0][j] = matrix[0][j-1] - 2;
		
		globalDp(matrix);
		
		///******************************REALIZAR BACKTRACKING******************************************////
		//calcular las aliniaciones obtenidas
		vector<pair<string,string>> seqResult;
		btGlobalPile(matrix, seqResult);
		/*
		cout << "_________ALINEAMINETOS:____________" << endl;
		for(int i=0; i<seqResult.size(); ++i){
			cout << seqResult[i].first << endl;
			cout << seqResult[i].second << endl;
			cout << "_____________________" << endl;
		}
		*/
		cout << "score: " << matrix[a.size()][b.size()] << endl;
		cout << "CANTIDAD DE CADENAS: " << seqResult.size() << endl;
		cout << "TAMANIO DEL ALINEAMIENTO: " << seqResult[0].first.size() << " __ " << seqResult[0].second.size() << endl;
		//print(matrix);
	}
	
	void alineacionLocal(){
		vector<vector<int>> matrix2(a.size() + 1, vector<int>(b.size() + 1, 0));
		localDp(matrix2);
		
		///******************************REALIZAR BACKTRACKING******************************************////
		//calcular las aliniaciones obtenidas
		vector<pair<string, string>> commonString = btLocal(matrix2);
		cout << "----------------_____________ALINEAMIENTO LOCAL:___________--------------------------commonStrings: " << endl << endl;
		for(int i=0; i<commonString.size(); ++i){
			cout << commonString[i].first << endl;
			cout << commonString[i].second << endl;
			cout << "********" << endl;
		}
		cout<< "tamanio alineamiento: " << commonString[0].first.size() << endl;
		//cout<<commonString.size() << endl;
		//print(matrix2);
	}	

	void print(vector<vector<int>>& matrix){
		for(int i=0; i<a.size()+1; ++i){
			for(int j=0; j<b.size()+1; ++j){
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}

	int score(string a, string b){
		int result = 0;
		for(int i =0 ; i<a.size(); ++i){
			if(a[i] == b[i]) result += 1;
			else if(a[i] == '_' or b[i] == '_') result -= 2;
			else result -= 1;
		}
		return result;
	}

	string randSequnce(int size){
		string result(size,' ');
		
		for(int i =0; i<size; ++i){
			result[i] = (char)rand()%4+65;
		}
		return result;
	}

};



