#include <iostream>
#include "UPGMA.cpp"

using namespace std;

int main(){
	
	string a,b;
	vector<string> sequencias;
		
	/*
	sequencias.push_back("CAAATGCAGGGACACCACA");
	sequencias.push_back("TTCTGGGTCACGGTGCTAGGGG");
	sequencias.push_back("AGCAGCAATGGTGGTTTCCCTGCTTGGGAGCC");
	sequencias.push_back("ATTTTCCCTATTCATCCAGGGAAAATGTTATGTT");
	sequencias.push_back("TGAAGAGTATGGACCAACATTAAAGAAAGCACACCAC");
	*/	
	
	vector<vector<double>> matrizDistancias = {
		{0,4,10,9},
		{4,0,8,7},
		{10,8,0,9},
		{9,7,10,0}
	};
	
	UPGMA eSim(matrizDistancias);

	return 0;
}


//g++ -std=c++11 seqGlobal.cpp -o seqGlobal.exe
//http://rna.informatik.uni-freiburg.de/Teaching/index.jsp?toolName=Needleman-Wunsch
