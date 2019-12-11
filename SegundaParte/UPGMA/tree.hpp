#include <iostream>
#include <vector>
#include <iomanip>

using namespace std; 

class node{
public:
	node* izq;
	node* der;
	node* parent;
	vector<int> nombre;
	double distanciaUnida;
	double acumulado;
	
	node(){}
	
	node(vector<int> nombre, double distanciaUnida, double acumulado, node* parent, node* izq, node* der):
		nombre(nombre), 
		distanciaUnida(distanciaUnida), 
		acumulado(acumulado),
		parent(parent),
		izq(izq), 
		der(der){}
	
	node(vector<int> nombre, double distanciaUnida, double acumulado, node* parent):
		nombre(nombre), 
		distanciaUnida(distanciaUnida), 
		acumulado(acumulado),
		parent(parent),
		izq(nullptr), 
		der(nullptr){}
};


class Tree{
public:
	node* root;
	
	Tree(){
		root = nullptr;
	}
	
	Tree(node* root_){
		root = root_;
	}
	
	Tree(vector<int> nombreA, int nombeDatoAInsertar, double distanciaUnida){//insertar solo un nodo
		vector<int> nombres(nombreA);
		nombres.push_back(nombeDatoAInsertar);		
		root = new node(nombres, 0, distanciaUnida, nullptr);
		
		node* izq = new node({nombreA}, distanciaUnida, distanciaUnida, root);
		node* der = new node( {nombeDatoAInsertar}, distanciaUnida, distanciaUnida, root);
		
		root->der = der;
		root->izq = izq;
	}
	
	node* search(node* temp, vector<int> A){
		
		if(temp == NULL) 
			return nullptr;
		
		for(int i=0; i<A.size();++i){
			for(int j=0; j<temp->nombre.size();++j){
				if(A[0] == 1 or A[0] == 3) cout << temp->nombre[j] << " " << A[i] << endl;
				if(temp->nombre[j] == A[i]){
					return temp;
				}
			}
		}
		
		return search(temp->izq, A); 
		return search(temp->der, A); 
	}
	
	bool insert(node* temp, int nombeDatoAInsertar, double distanciaUnida){//insertar solo un nodo
		vector<int> nombreA = temp->nombre;
		vector<int> nombres(nombreA);
		nombres.push_back(nombeDatoAInsertar);
		
		if(!root){
			root = new node(nombres, 0, distanciaUnida, nullptr);
			
			node* izq = new node({nombreA}, distanciaUnida, distanciaUnida, root);
			node* der = new node( {nombeDatoAInsertar}, distanciaUnida, distanciaUnida, root);
			
			root->der = der;
			root->izq = izq;
			return true;
		}
			
		if(temp){
			root = new node(nombres, 0, distanciaUnida, nullptr);
			
			temp->parent = root;
			temp->distanciaUnida = distanciaUnida - temp->acumulado;
			node* der = new node( {nombeDatoAInsertar}, distanciaUnida, distanciaUnida, root);
			
			root->izq = temp;
			root->der = der;
			return true;
		}	
		return false;
	}
	
	void imprimir(node* pointer, string buffer = ""){
		if(pointer){
			imprimir(pointer->izq,buffer+"\t");
			cout<<endl;
			if(pointer->nombre.size() == 1){
				cout << buffer << "[" << pointer->distanciaUnida <<"]";  printNombre(pointer->nombre); 
			}
			else cout << buffer << "--[" << pointer->distanciaUnida <<"]";
			cout<<endl; 
			imprimir(pointer->der,buffer+"\t");
		}
	}
	
	void printNombre(vector<int> A){
		//cout<< "nombree: __________" << endl;
		for(int i=0; i<A.size();++i){
			cout << A[i] << ", ";
		}
	}
};


class ArbolFilogenetico{
	void imprimir(node* pointer, string buffer = ""){
		if(pointer){
			imprimir(pointer->izq,buffer+"\t");
			cout<<endl;
			if(pointer->nombre.size() == 1){
				cout << buffer << "[" << pointer->distanciaUnida <<"]" << pointer->nombre[0]; 
			}
			else cout << buffer << "--[" << pointer->distanciaUnida <<"]";
			cout<<endl; 
			imprimir(pointer->der,buffer+"\t");
		}
	}
public:
	vector<Tree*> forest;
	
	void insert(vector<int> nombreA, vector<int> nombeDatoAInsertar, double distanciaUnida){
		if(forest.empty()){
			forest.push_back(new Tree(nombreA,nombeDatoAInsertar[0],distanciaUnida));
			return;
		}
		
		node* temp, *temp2;
		size_t pos1 = 0, pos2 = 0;
		
		for(int i = 0; i<forest.size(); ++i){
			if(temp = forest[i]->search(forest[i]->root,nombreA)){
				pos1 = i;
				break;
			}
		}
		
		for(int i = 0; i<forest.size(); ++i){
			if(temp2 = forest[i]->search(forest[i]->root,nombeDatoAInsertar)){
				pos2 = i;
				break;
			}
		}
		
		if(temp && temp2){//unir ambos arboles
			vector<int> nombres(nombreA);
			nombres.insert(nombres.begin(), nombeDatoAInsertar.begin(),nombeDatoAInsertar.end());	
			
			node* root = new node(nombres, 0, distanciaUnida, nullptr);
			
			temp->parent = root;
			temp->distanciaUnida = distanciaUnida - temp->acumulado;
			
			temp2->parent = root;
			temp2->distanciaUnida = distanciaUnida - temp2->acumulado;
			
			root->izq = temp;
			root->der = temp2;
			
			if(pos1 > pos2){int temp = pos1; pos1 = pos2; pos2=temp;}
			forest.erase(forest.begin()+pos2);
			forest.erase(forest.begin()+pos1);
			forest.push_back(new Tree(root));
			return;
		}
		else if(temp){//insertar en primer arbol
			cout << "temp1: " << nombeDatoAInsertar[0] << endl;
			forest[pos1]->insert(temp, nombeDatoAInsertar[0], distanciaUnida);//insertar solo un nodo
			return;
		}
		else if(temp2){//insertar en el segundo arbol
			forest[pos2]->insert(temp2, nombreA[0], distanciaUnida);//insertar solo un nodo
			return;
		}

		forest.push_back(new Tree(nombreA,nombeDatoAInsertar[0],distanciaUnida));	
	}
	
	void imprimir(){
		forest[0]->imprimir(forest[0]->root);
	}	
};
