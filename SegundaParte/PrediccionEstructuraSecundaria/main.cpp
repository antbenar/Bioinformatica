#include <iostream>
#include "estructura.cpp"

using namespace std;

int main(){
	vector<string> sequencias;

	sequencias.push_back("GGAAAUCC");
	sequencias.push_back("GGAAAUCC");
	
	Estructura alg(sequencias[0],sequencias[1]);
	alg.desarrollo();

	return 0;
}


//g++ -std=c++11 seqGlobal.cpp -o seqGlobal.exe
//http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch
