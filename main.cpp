#include <iostream>
#include "seqLocalGlobal.cpp"
#include "estrella.cpp"
#include "progressiveAlignment.cpp"
using namespace std;

int main(){
	
	string a,b;
	vector<string> sequencias;

	/*
	//cout << "Ingrese sequencia a: ";
	cin >> a;
	//cout << "Ingrese sequencia b: ";
	cin >> b;
	
	
	AlineacionesGlobalLocal alg(a,b);
	alg.alineacionGlobal();
	//alg.alineacionLocal();
	*/
	
	
	sequencias.push_back("ATTGCCATT");
	sequencias.push_back("ATGGCCATT");
	sequencias.push_back("ATCCAATTTT");
	sequencias.push_back("ATCTTCTT");
	sequencias.push_back("ACTGACC");
	
	/*
	sequencias.push_back("GCTCGAC");
	sequencias.push_back("GCTCG");
	sequencias.push_back("AAATCGA");
	sequencias.push_back("CATTGCC");
	AlineacionEstrella aEstrella(sequencias);
	*/
	
	
	vector<vector<double>> matrizDistancias = {
		{0,5,4,7,6,8},
		{5,0,7,10,9,11},
		{4,7,0,7,6,8},
		{7,10,7,0,5,9},
		{6,9,6,5,0,8},
		{8,11,8,9,8,0}
	};
	
	ProgressiveAlignment pAlg(sequencias);
	//ProgressiveAlignment pAlg(matrizDistancias);
	return 0;
}


//g++ -std=c++11 seqGlobal.cpp -o seqGlobal.exe
//http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch

/*CAACAGGCCTCATGCAGTAAACACTGGATGGGCTATGCTG
GCTCTCATTGAGGCTGAACAGGCAA
*/
