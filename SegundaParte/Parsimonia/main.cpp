#include <iostream>
#include "Parsimonia.cpp"

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
	Parsimonia eSim(sequencias);
	*/
	
	//segundo bloque de secuencias de prueba de filogenia
	sequencias.push_back("AGTAGTTCAGTAGGGCAGTAGGGC");
	sequencias.push_back("AGTAGTTAAGTAGGGCAGTAGTAA");
	sequencias.push_back("AGTAGTAAAGTAGTAAAGTAGTAA");
	sequencias.push_back("AGTAGGGGAGTAGTAAAGTAGGGC");
	sequencias.push_back("AGTAGGGCAGTAGGGCAGTAGGGC");
	Parsimonia eSim(sequencias);


	return 0;
}


//g++ -std=c++11 seqGlobal.cpp -o seqGlobal.exe
//http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch
