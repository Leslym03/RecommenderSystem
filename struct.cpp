#include <iostream>
#include <vector>
#include <fstream>
#include "struct.h"
using namespace std;

//Nodo
Nodo::Nodo(){
    next=NULL;
}

int Nodo::getData(){
    return data;
}

float Nodo::getRating(){
    return rating;
}

void Nodo::setData(int newData, char newRating){
    data=newData;
    rating=newRating;
}

// Linkedlist
Linkedlist::Linkedlist(int setkey){
    head=NULL;
    size=0;
    key=setkey;
}

void Linkedlist::insert(int data, float rating){
    Nodo* newNodo=new Nodo;
    newNodo->data=data;
    newNodo->rating=rating;
    Nodo* aux1;
    Nodo* aux2;
    aux1=head;
    while(aux1&&aux1->data<data){
        aux2=aux1;
        aux1=aux1->next;
    }
    if(head==aux1)
        head=newNodo;
    else
    {
        aux2->next=newNodo;
    }
    newNodo->next=aux1;
    size++;
}

int Linkedlist::search(int data){
    int pos=0;
    Nodo* aux1=head;
    while(aux1->data!=data){
        aux1=aux1->next;
        pos++;
        if(!aux1)
            break;
    }
    return ++pos;
}

void Linkedlist::remove(int data){
    Nodo* aux1=head;
    Nodo* aux2=NULL;
    while(aux1->data!=data){
        aux2=aux1;
        aux1=aux1->next;
        if(!aux1)
            break;
    }
    if(!aux2){
        head=aux1->next;
        delete aux1;
        size--;
        return;
    }
        
    if(aux1){
        aux2->next=aux1->next;
        delete aux1;
        size--;
    }
}

void Linkedlist::printlist(){
    Nodo* aux1=head;
    while(aux1){
        cout<<aux1->data<<"->"<<aux1->rating <<"   ";
        aux1=aux1->next;
    }
    cout<<endl;
}

int Linkedlist::getSize(){
    return size;
}

Linkedlist::~Linkedlist(){
    Nodo* aux1=head;
    Nodo* aux2;
    while(aux1){
        aux2=aux1->next;
        delete aux1;
        aux1=aux2;
    }
}



// Btree

BNode::BNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys.reserve(2*t-1);
    childs.reserve(2*t);
    n = 0;
}

void BNode::traverse() {
    int i;
    for (i = 0; i < n; i++){
        if (leaf == false)
            childs[i]->traverse();

        cout << " " << keys[i];
    }

    if (leaf == false)
        childs[i]->traverse();
}

void BNode::printListL(){
    for (int i = 0; i < lists_mr.size(); i++) {
        lists_mr.at(i)->printlist();
        //cout << endl;
    }
}

// Función para buscar la clave k en el subárbol enraizado con este nodo
BNode *BNode::search(int k) {
    int i = 0;
    // Encuentra la primera clave mayor o igual a k
    while (i < n && k > keys[i])
        i++;

    // Si la clave encontrada es igual a k, devuelve este nodo
    if (keys[i] == k){
        return this;
    }

    // Si la clave no se encuentra aquí y este es un nodo hoja
    if (leaf == true)
        return NULL;

    return childs[i]->search(k);
}

void BTree::printlist_node(int k){
    BNode *temp_node = search(k);
    temp_node->printListL();
}

void BTree::insert(int k, int data, float rating) {
    if (search(k) ==NULL){
        // Si el árbol está vacío
        if (root == NULL) {
            // Asignar memoria para root
            root = new BNode(t, true);
            root->keys[0] = k; // Insertar clave
            root->n = 1;// Actualizar el número de claves en la raíz

            ///////// Linkedlist
            Linkedlist* lista = new Linkedlist(k);
            lista->insert(data, rating);
            root->lists_mr.push_back(lista);
            root->printListL();
            cout << endl;
            //lista->printlist();
            //cout << &lista <<"  "<< endl;
            
            //root->linkList(*lista);
            //root->ptrList->printlist();
        } else  { // Si el árbol no está vacío
            if (root->n == 2*t-1){ // Si la raíz está llena, entonces el árbol crece en altura
                // Asignar memoria para nueva raíz
                BNode *s = new BNode(t, false); 

                // Hacer root viejo como hijo de root nuevo
                s->childs[0] = root;
                // Dividir la raíz antigua y mover 1 tecla a la raíz nueva
                s->splitChild(0, root);
                // New root tiene dos hijos ahora. Decide cuál de los dos niños va a tener llave nueva
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->childs[i]->insertNonFull(k, data, rating);
                
                // Cambiar raíz
                root = s;
                root->printListL();
                cout << endl;
            }
            else // Si la raíz no está llena, llame a insertNonFull para la raíz
                root->insertNonFull(k, data, rating);
                root->printListL();
                cout << endl;
        }

    }
    
    else{
        ///////// Linkedlist
        Linkedlist* lista = new Linkedlist(k);
        lista->insert(data, rating);
        //root->lists_mr.push_back(lista);
        //root->printListL();
        //cout << endl;
        //lista->printlist();
        BNode *temp_node = search(k);
        temp_node->lists_mr.push_back(lista);
        temp_node->printListL();
        cout << endl;
    }

    
}

int BTree::minimum( BNode *x) {
    return (x->leaf==true) ? x->keys[0] : minimum(x->childs[0]);
}

int BTree::maximum(BNode *x) {
    return (x->leaf==true) ? x->keys[x->n-1] : maximum(x->childs[x->n]);
}

// Una función de utilidad para insertar una nueva clave en este nodo
// La suposición es que el nodo no debe estar lleno cuando se llama a esta función
void BNode::insertNonFull(int k, int data, float rating) {
    // Inicializa el índice como índice del elemento más a la derecha
    int i = n-1;
    // Si este es un nodo hoja
    if (leaf == true) {
        // El siguiente ciclo hace dos cosas
         // a) Encuentra la ubicación de la nueva clave que se insertará
         // b) Mueve todas las teclas mayores a un lugar adelante
        while (i >= 0 && keys[i] > k){
            keys[i+1] = keys[i];
            lists_mr[i+1] = lists_mr[i];
            i--;
        }
        // Inserta la nueva clave en la ubicación encontrada
        keys[i+1] = k;

        //Linkedlist
        Linkedlist* newlista = new Linkedlist(k);
        newlista->insert(data, rating);
        lists_mr.insert(lists_mr.begin()+i+1, newlista);
        //Linkedlist

        n = n+1;
    }
    else { // Si este nodo no es hoja
        while (i >= 0 && keys[i] > k) // Encuentra el niño que va a tener la nueva clave
            i--;
        // Ver si el niño encontrado está lleno
        if (childs[i+1]->n == 2*t-1) {
            splitChild(i+1, childs[i+1]); // Si el niño está lleno, entonces divídalo
            // Después de dividir, la tecla central de C[i] sube y C[i] se divide en dos.
            // Ver cual de los dos va a tener la nueva llave
            if (keys[i+1] < k)
                i++;
        }
        childs[i+1]->insertNonFull(k, data, rating); 
    }
}


// Una función de utilidad para dividir el hijo y de este nodo
// Tenga en cuenta que y debe estar lleno cuando se llama a esta función
void BNode::splitChild(int i, BNode *y){
    // Crea un nuevo nodo que va a almacenar (t-1) claves de y
    BNode *z = new BNode(y->t, y->leaf);
    z->n = t - 1;
    // Copiar las últimas claves (t-1) de y a z
    for (int j = 0; j < t-1; j++){
        z->keys[j] = y->keys[j+t];
        z->lists_mr[j] = y->lists_mr[j+t];
    }
        

    // Copia los últimos t hijos de y a z
    if (y->leaf == false){
        for (int j = 0; j < t; j++)
            z->childs[j] = y->childs[j+t];
    }
    // Reducir el número de claves en y
    y->n = t - 1; 
    // Dado que este nodo va a tener un nuevo hijo, crear espacio de nuevo niño
    for (int j = n; j >= i+1; j--)
        childs[j+1] = childs[j];
    // Vincular el nuevo hijo a este nodo
    childs[i+1] = z;
    // Una clave de y se moverá a este nodo.
    // Encuentra la ubicación de la nueva clave y mueve todas las claves mayores un espacio adelante
    for (int j = n-1; j >= i; j--){
        keys[j+1] = keys[j];
        lists_mr[j+1] = lists_mr[j];
    }
        
    // Copia la key del medio de y a este nodo
    keys[i] = y->keys[t-1];
    lists_mr[i] = y->lists_mr[t-1];
    // Incrementa el conteo de claves en este nodo
    n = n + 1;
}


int main(){
    BTree t(3);
    t.insert(10, 3, 1.5);
    t.insert(11, 5, 2.5);
    t.insert(11, 6, 3.5);
    t.insert(12, 3, 3.5);
    cout << "El recorrido del árbol construido es ";
    t.traverse();
    cout << endl;
    cout << endl;
    t.printlist_node(10);
    cout << endl;


    /*
     
    BTree t(3);
    t.insert(10);
    t.insert(40);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "El recorrido del árbol construido es ";
    t.traverse();
    cout << endl;

    Linkedlist lista;
    Linkedlist* ptr = &lista;

    cout << ptr << endl;
    cout << &lista << endl;

    cout << "Nodos" << endl;
    lista.insert(3, 1.5);
    lista.insert(2, 1);
    lista.insert(1, 4);
    lista.insert(4, 4.5);
    lista.printlist();
    
    cout <<lista.search(2)<<endl;
    
    lista.remove(1);
    lista.remove(3);
    lista.printlist();

    cout <<"Size = "<< lista.getSize()<<endl;
    */
    return 0;
}