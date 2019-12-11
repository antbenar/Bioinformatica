#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
using namespace std; 


class Estructura{	
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
	
	bool coinciden(char a, char b){
		if(a=='C' && b == 'G') return true;
		if(b=='C' && a == 'G') return true;
		if(a=='A' && b == 'U') return true;
		if(b=='A' && a == 'U') return true;
		return false;
	}
	
	void globalDp(vector<vector<int>>& matrix){
		int temp, i, j;
		
		for(int pos=0; pos<a.size(); ++pos){
			for(int pos2=pos; pos2<b.size()-1; ++pos2){
				i = pos2;
				j = pos2 + 1;
				temp = min(matrix[i+1][j], matrix[i][j-1]);
				if(coinciden(a[i], b[j])){
					temp = min(temp, matrix[i+1][j-1]-1);
				}
				
				for(int k=i+1; k<j; k++){
					temp = min(temp, matrix[i][k]+matrix[k+1][j]);
				}
				matrix[i][j] = temp;
				//print(matrix);
			}
		}
	}
	
	
public:
	string a, b;

	Estructura(string a_, string b_):a(a_), b(b_){
		if(b.size() > a.size()) swap(a,b);//para que la cadena mayor esté a la izquierda
	}
	
	void desarrollo(){
		//********************************************inicializar matriz para calcular alineacion global
		vector<vector<int>> matrix(a.size(), vector<int>(b.size(), 0));
		globalDp(matrix);
		
		
		///******************************REALIZAR BACKTRACKING******************************************////
		//calcular las aliniaciones obtenidas
		//vector<pair<string,string>> seqResult;
		//btGlobalPile(matrix, seqResult);

		print(matrix);
	}
	

	void print(vector<vector<int>>& matrix){
		for(int i=0; i<a.size(); ++i){
			for(int j=0; j<b.size(); ++j){
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}


};



