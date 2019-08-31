#include <iostream>
#include <string.h> 
#include <fstream>

using namespace std;

class Node {
public:
    Node *n_der,*n_izq;
    Node *padre;
    
    string data;
    string valor2;
    //Node (string name, valor2) {
    Node (string name, Node *padre_) {
        data = name;
        n_izq = n_der = NULL;
        padre = padre_;
        
    }
};

class arbol_images {
public:
    Node* root;
    
    int size=0;
    int index_root;
    arbol_images () {root = NULL; }
    bool insert(string data) { 
        return insert(data,root, NULL ); 
    };
    bool insert(string name, Node* raiz_actual, Node *padre);
    
    void inorder()  { inorder(root);};
    void postorder()  { postorder(root);};
    void preorder()  { preorder(root);};
    void inorder( Node* actual) ;
    void postorder( Node*actual);
    void preorder( Node* actual) ;
    
    //print
    void print_inorder()  { print_inorder(root);};
    void print_inorder( Node* actual) ;
    
    void Graficando_inor();
    void Graficando_preor();
    void Graficando_posor();
    void Graficando_arbol();
    
    void create_archivo(string nombre, string contenido);
    
    void VerArbol( Node *actual);
    void VerArbol()  { VerArbol(root);};
    
    void eliminar(Node *actual, string name_ac);
    void eliminar_nod(Node *elimar);
    
    Node *Menor_Mayores(Node *root_e);
    Node *Mayor_Menores(Node *root_e);
    void modif_nod(Node *aelimar, Node *nuevorem);
    
    
    string grafica_orden;
    
};

bool arbol_images :: insert(string name, Node *raiz_actual, Node *padre) {
	int compar_nombre;
	compar_nombre = 0;
	
    if (root == NULL) {
        root = new Node(name, NULL);
        size++;
        //cout << " \nsize " << size ;  
        return true;
    //}else if (nombre < raiz_actual->data) {   
    }
		else if (compar_nombre = strcmp(name.c_str() ,raiz_actual->data.c_str()) < 0) {
        if (raiz_actual->n_izq == NULL) {
            raiz_actual->n_izq = new Node(name, raiz_actual);
            size++;
            return true;
        }
        else {
            return insert(name, raiz_actual->n_izq, raiz_actual);
        }
    //}else if (nombre > raiz_actual->data) {
    }
	else if (compar_nombre = strcmp(name.c_str() ,raiz_actual->data.c_str()) > 0) {
		
        if (raiz_actual->n_der == NULL) {
            raiz_actual->n_der = new Node(name, raiz_actual);
            
            size++;
            return true;
        }
        else {
            return insert(name, raiz_actual->n_der, raiz_actual);
        }
    }else {
        return false;
    }
}

void arbol_images :: inorder( Node *root) {
    if (root != NULL) {
        inorder(root -> n_izq);
        //cout << " " << root->data << " ->";
        //cout<< root->data <<endl;
        index_root++;
        if (index_root != size)
		{grafica_orden = grafica_orden + " \"" + root->data + "\" ->"; }
        else{grafica_orden = grafica_orden + " \"" + root->data + "\""; }
        
        //grafica_orden = grafica_orden + " " + root->data;
        inorder(root -> n_der);
    }
    
}


/*void arbol_images :: print_inorder( Node *root) {

    if (root != NULL) {
        print_inorder(root -> n_izq);
        index_root++;
        //cout<< root->data <<"/"<<index_root<<endl;
        if (index_root != size){
        	grafica_orden = grafica_orden + " " + root->data + " ->"; 
        	}	else	{grafica_orden = grafica_orden + "" + root->data; }
        //grafica_orden = grafica_orden + "" + root->data + " ->"; 
        
        //cout<< root->data <<endl;
        ////////////cout << " " << root->data << " ->";
        print_inorder(root -> n_der);
    }
    
}*/

void arbol_images::Graficando_inor() {
	index_root = 0;
	grafica_orden = grafica_orden + "digraph G { rankdir=LR\n";
	//print_inorder();
	inorder();
    grafica_orden = grafica_orden + "\n}\n";
    cout << "inorder: \n";
	//cout <<grafica_orden<<endl;
	//cout << "\n +index_root+ : " <<index_root<<endl;
	create_archivo("graf_in",grafica_orden);
	
}

void arbol_images :: VerArbol( Node *root) {
	string tem_nod = "";
    if (root != NULL) {
        VerArbol(root -> n_izq /*, cont+1, "I"*/);
        //VerArbol(root -> n_der, cont+1, "D");   	
		tem_nod = "";
       	Node *tempo; 
       	tempo = root;
       	if (tempo-> n_der != NULL) {
       		
       		tem_nod = tem_nod  +"nodo"+ root->data;
       		tem_nod = tem_nod  +":C1 -> nodo"+ tempo->n_der->data + "\n";
       		
       	}
       	if (tempo-> n_izq != NULL) {
       		
       		tem_nod = tem_nod  +"nodo"+ root->data ;
       		tem_nod = tem_nod  +":C0 -> nodo"+ tempo->n_izq->data + "\n";
       		
       	}
       	
       	
       	
       	grafica_orden = grafica_orden + tem_nod;
       	
       	if (root->padre != NULL) {
       		grafica_orden = grafica_orden +"nodo"+ root->data  +" [ label =\"<C0>|"+ root->data + " p("+ root->padre->data +") |<C1>\"]; \n";
       	
       	}
       	else {
       	grafica_orden = grafica_orden +"nodo"+ root->data  +" [ label =\"<C0>|"+ root->data + "|<C1>\"]; \n";
		}
		   
		//   grafica_orden = grafica_orden +"nodo"+ root->data  +" [ label =\"<C0>|"+ root->data + "|<C1>\"]; \n";
		//////cout  << root->data <<endl;
        VerArbol(root -> n_der /*, cont+1, "D"*/ );
        //VerArbol(root -> n_izq, cont+1, "I");
    }
    
}

/*graficando arbol binario*/
void arbol_images::Graficando_arbol() {
	//index_root = 0;
	grafica_orden = "";
	
	grafica_orden = grafica_orden + "digraph G { \n";
	grafica_orden = grafica_orden + "rankdir=TB;\n";
	//grafica_orden = grafica_orden + "graph [splines=ortho, nodesep=0.5];\n";
	grafica_orden = grafica_orden + "graph [nodesep=0.5 ];\n";
	//grafica_orden = grafica_orden + "node [shape = record, fillcolor=seashell2, width=0.7,height=0.2];\n";
	grafica_orden = grafica_orden + "node [shape = record, fillcolor=seashell2];\n";
	VerArbol();
    grafica_orden = grafica_orden + "\n}\n";
    //cout << "arbol bonario: \n";
    //cout << "grafica_orden: "<<grafica_orden <<endl;
	create_archivo("graf_arbol",grafica_orden);
	
}

void arbol_images::Graficando_preor() {
	index_root = 0;
	grafica_orden = grafica_orden + "digraph G { rankdir=LR\n";
	preorder();
    grafica_orden = grafica_orden + "\n}\n";
    cout << "preorder: \n";
	//cout <<grafica_orden<<endl;
	//cout << "\n +index_root+ : " <<index_root<<endl;
	create_archivo("graf_pre",grafica_orden);
}

void arbol_images::Graficando_posor() {
	index_root = 0;
	grafica_orden = grafica_orden + "digraph G { rankdir=LR\n";
	postorder();
    grafica_orden = grafica_orden + "\n}\n";
    cout << "posorder: \n";
	//cout <<grafica_orden<<endl;
	//cout << "\n +index_root+ : " <<index_root<<endl;
	create_archivo("graf_pos",grafica_orden);
}

void arbol_images :: preorder( Node *root) {
    if (root != NULL) {
        //cout << " " << root->data << " ->";
        index_root++;
        if (index_root != size)
		{grafica_orden = grafica_orden + "\"" + root->data + "\" ->"; }
        else{grafica_orden = grafica_orden + "\"" + root->data + "\""; }
        //cout<< root->data <<endl;
        preorder(root -> n_izq);
        preorder(root -> n_der);
    }
    
}
void arbol_images :: postorder( Node *root) {
    if (root != NULL) {
        postorder(root -> n_izq);
        postorder(root -> n_der);
        //cout << " " << root->data << " ->";
        //cout<< root->data <<endl;
        index_root++;
        if (index_root != size)
		{grafica_orden = grafica_orden + "\"" + root->data + "\" ->"; }
        else{grafica_orden = grafica_orden + "\"" + root->data + "\""; }
    }
    
}

void arbol_images::create_archivo(string nombre, string contenido) {
	
	string nom_ar = "";
	nom_ar = nombre + ".txt";
	ofstream file;
	file.open(nom_ar.c_str());
	//file.open(nombre.c_str());
	file <<contenido;
	file.close();
	string dot, ima;
	dot = "dot -Tpng "+ nom_ar + " -o "+nombre + ".jpg";
	ima = nombre + ".jpg";
	//cout << " \n dot *** " << dot ;
	//cout << " \n ima *** " << ima ;
	system(dot.c_str());
    system(ima.c_str());
	
}

void arbol_images::eliminar(Node *root, string name) {
	int  compar_nombre = 0;
	if (root != NULL) {
		
		if (compar_nombre = strcmp(name.c_str() ,root->data.c_str()) < 0) {
			eliminar(root -> n_izq, name);
		}
		else if (compar_nombre = strcmp(name.c_str() ,root->data.c_str()) > 0) {
			eliminar(root -> n_der, name);
		}
		else
		{
			//cout << "valor encontrado *** " << root->data<<endl ;
			eliminar_nod(root);
		}    
    }	
}

void arbol_images::modif_nod(Node *aelimar, Node *nuevorem) {	

	string tempo_dat_iz = "";
	string tempo_dat_der = "";
	if ( aelimar->padre ) {
		//para izquierdo
		//cout <<"1 aelimar->data*** " << aelimar->data<<endl ;
		////cout <<"1.2 aelimar->padre->data*** " << aelimar->padre->data <<endl ;
		//cout <<"2 aelimar->padre->n_der->data*** " << aelimar->padre->n_der->data <<endl ;
		
		//cout <<"entra y tien padre"<<endl;
		
		if (aelimar->padre->n_izq != NULL) {	
			tempo_dat_iz = aelimar->padre->n_izq->data;
		} else  {tempo_dat_iz = "";} 
		
		if (aelimar->padre->n_der != NULL) {	
			tempo_dat_der = aelimar->padre->n_der->data;
		} else  {tempo_dat_der = "";}
		
		//if (aelimar->data == aelimar->padre->n_izq->data) {	
		if (aelimar->data == tempo_dat_iz) {	
			//cout <<"if 1"<<endl;
			aelimar->padre->n_izq = nuevorem;
		}
		//else if (aelimar->data == aelimar->padre->n_der->data) {
		else if (aelimar->data == tempo_dat_der) {
			//cout <<"if 2"<<endl;
			//cout <<"////////"<<aelimar->data<<endl;
			aelimar->padre->n_der = nuevorem;
		} 
		
		
		/*if (aelimar->padre->n_izq != NULL ) {
			if (aelimar->data == aelimar->padre->n_izq->data) {
			cout <<"if 1"<<endl;
			aelimar->padre->n_izq = nuevorem;
			}
		}
		else if (aelimar->padre->n_der != NULL ) {
			if (aelimar->data == aelimar->padre->n_der->data) {
			cout <<"if 2"<<endl;
			cout <<"////////"<<aelimar->data<<endl;
			aelimar->padre->n_der = nuevorem;
			}
		} */
		
	}
	//cout <<"pasa"<<endl;
	
	if (nuevorem) {
		nuevorem->padre = aelimar->padre;
	}
	
}

void arbol_images::eliminar_nod(Node *elimar) {
	
	/*si tiene dos hijo
	el menor de los mayores, por la derecha*/
	if (elimar->n_izq && elimar->n_der ) {
		//////cout <<"2 hijos"<<endl;
		//Node *men_may = Menor_Mayores(elimar -> n_der);
		Node *men_may = Mayor_Menores(elimar -> n_izq);		
		elimar->data = men_may->data;
		eliminar_nod(men_may);
	}
	/*elimiar cuando solo tiene 1 hijo*/
	else if (elimar->n_izq) {
		//////cout <<"1 hijo iz"<<endl;
		modif_nod(elimar, elimar->n_izq );
		//elimiando 
		elimar->n_izq = NULL;
		elimar->n_der = NULL;
		delete elimar;
		
	}
	else if (elimar->n_der) {
		/////cout <<"1 hijo der"<<endl;
		modif_nod(elimar, elimar->n_der );
		//elimiando 
		elimar->n_izq = NULL;
		elimar->n_der = NULL;
		delete elimar;
		
	}
	else  {
		////////cout <<"sin hijos, hoja"<<endl;
		modif_nod(elimar, NULL );
		elimar->n_izq = NULL;
		elimar->n_der = NULL;
		delete elimar;
	}
		
}

Node *arbol_images::Menor_Mayores(Node *root_men) {
	if (root_men != NULL) {
		
		if (root_men->n_izq) {
			return Menor_Mayores(root_men->n_izq);
		}
		else
		{
			return root_men;
		}
	}
	else
	{
		return NULL;
	}		
}


Node *arbol_images::Mayor_Menores(Node *root_men) {
	if (root_men != NULL) {
		
		if (root_men->n_der) {
			return Mayor_Menores(root_men->n_der);
		}
		else
		{
			return root_men;
		}
	}
	else
	{
		return NULL;
	}		
}




int main()
{
    arbol_images ar_ima;
    
    cout <<"Insertar luigi, hammer, mario, peach, pow, fermin"<<endl;
    ar_ima.insert("luigi");
	ar_ima.insert("hammer");
    ar_ima.insert("mario");
    ar_ima.insert("peach");
    ar_ima.insert("pow");
    ar_ima.insert("fermin");
    ar_ima.Graficando_arbol();
    system("pause");

	/*ar_ima.insert("nose");
	ar_ima.insert("s");
    ar_ima.insert("h");
    ar_ima.insert("j");
    ar_ima.insert("i"); 
    ar_ima.insert("d");
    ar_ima.insert("v");
    ar_ima.insert("r");*/
    
    
    /*ar_ima.insert("b");
    ar_ima.insert("a");
    ar_ima.insert("5");
    ar_ima.insert("6");
    ar_ima.insert("10");
    ar_ima.insert("4");
    ar_ima.insert("9");
    ar_ima.insert("15");*/
    //
	

    //ar_ima.Graficando_inor();
    //ar_ima.grafica_orden = "";
    //ar_ima.Graficando_preor();
    //ar_ima.Graficando_posor();
    //ar_ima.grafica_orden = "";
    
   
    
   // ar_ima.eliminar(ar_ima.root, "nose" );
	cout <<"Eliminar peach"<<endl;
	ar_ima.eliminar(ar_ima.root, "peach" );
	ar_ima.Graficando_arbol();
	system("pause");
   	
   	cout <<"Insertar shy_guy, edd"<<endl;
    ar_ima.insert("shy_guy");
    ar_ima.insert("edd");
    ar_ima.Graficando_arbol();
	system("pause");
    
    cout <<"Eliminar pow"<<endl;
    ar_ima.eliminar(ar_ima.root, "pow" );
    ar_ima.Graficando_arbol();
	system("pause");
	
	cout <<"Insertar Boo, Kamek, star, whomp"<<endl;
	ar_ima.insert("Boo");
    ar_ima.insert("Kamek");
    ar_ima.insert("star");
    ar_ima.insert("whomp");
    ar_ima.Graficando_arbol();
	system("pause");
    
    
    cout <<"Eliminar shy_guy"<<endl;
    ar_ima.eliminar(ar_ima.root, "shy_guy" );
    ar_ima.Graficando_arbol();
	system("pause");
    
    cout <<"Eliminar mario"<<endl;
    ar_ima.eliminar(ar_ima.root, "mario" );   
	ar_ima.Graficando_arbol();
    system("pause");
    
    cout << " \n --- " << ar_ima.size ;
    
    
   /* //cout << "NULL\n";
    ar_ima.inorder();
    
    cout << "---\n";
    ar_ima.preorder();
   //// 
    cout << "---\n";
    ar_ima.postorder();*/
}

