#include <iostream>
//#include "seqLocalGlobal.cpp"
//#include "estrella.cpp"
//#include "progressiveAlignment.cpp"
#include "estrategiasSimilitud.cpp"

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
	
	/*
	sequencias.push_back("ATTGCCATT");
	sequencias.push_back("ATGGCCATT");
	sequencias.push_back("ATCCAATTTT");
	sequencias.push_back("ATCTTCTT");
	sequencias.push_back("ACTGACC");
	*/
	//AlineacionEstrella aEstrella(sequencias);
	
	/*
	vector<vector<double>> matrizDistancias = {
		{0,5,4,7,6,8},
		{5,0,7,10,9,11},
		{4,7,0,7,6,8},
		{7,10,7,0,5,9},
		{6,9,6,5,0,8},
		{8,11,8,9,8,0}
	};
	
	
	sequencias.push_back("CAAATGCAGGGACACCACA");
	sequencias.push_back("TTCTGGGTCACGGTGCTAGGGG");
	sequencias.push_back("AGCAGCAATGGTGGTTTCCCTGCTTGGGAGCC");
	sequencias.push_back("ATTTTCCCTATTCATCCAGGGAAAATGTTATGTT");
	sequencias.push_back("TGAAGAGTATGGACCAACATTAAAGAAAGCACACCAC");
	
	*/
	
	//ProgressiveAlignment pAlg(sequencias);
	//ProgressiveAlignment pAlg(matrizDistancias);
	
	
	vector<vector<double>> matrizDistancias = {
		{0,2.15,0.7,1.07,1.56},
		{2.15,0,1.38,1.01,2.83},
		{0.7,1.38,0,0.29,1.86},
		{1.07,1.01,0.29,0,2.04},
		{1.56,2.83,1.86,2.04,0},
	};
	
	EstrategiaSimilitud eSim(matrizDistancias,"min");
	//EstrategiaSimilitud eSim(matrizDistancias,"max");
	//EstrategiaSimilitud eSim(matrizDistancias,"avg");
	
	return 0;
}


//g++ -std=c++11 seqGlobal.cpp -o seqGlobal.exe
//http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch
