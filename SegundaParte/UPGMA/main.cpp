#include <iostream>
#include "UPGMA.cpp"

using namespace std;

int main(){
	
	string a,b;
	vector<string> sequencias;
	
	/*
	//secuencias de prueba de filogenia
	sequencias.push_back("AGTAGTTC");
	sequencias.push_back("AGTAGTTA");
	sequencias.push_back("AGTAGTAA");
	sequencias.push_back("AGTAGGGG");
	sequencias.push_back("AGTAGGGC");
	UPGMA eSim(sequencias);
	*/
	
	
	
	
	//segundo bloque de secuencias de prueba de filogenia
	sequencias.push_back("AGTAGTTCAGTAGGGCAGTAGGGC");
	sequencias.push_back("AGTAGTTAAGTAGGGCAGTAGTAA");
	sequencias.push_back("AGTAGTAAAGTAGTAAAGTAGTAA");
	sequencias.push_back("AGTAGGGGAGTAGTAAAGTAGGGC");
	sequencias.push_back("AGTAGGGCAGTAGGGCAGTAGGGC");
	UPGMA eSim(sequencias);
	
	
	/*
	vector<vector<double>> matrizDistancias = {
		{0,4,10,9},
		{4,0,8,7},
		{10,8,0,9},
		{9,7,10,0}
	};
	UPGMA eSim(matrizDistancias);
	*/
	
	return 0;
}


//g++ -std=c++11 seqGlobal.cpp -o seqGlobal.exe
//http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch
