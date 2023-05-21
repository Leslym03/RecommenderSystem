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
Linkedlist::Linkedlist(){
    head=NULL;
    size=0;
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

BNode *BNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return childs[i]->search(k);
}

void BNode::linkList(Linkedlist list){
    ptrList = &list;
}

void BTree::insert(int k) {
    if (root == NULL) {
        root = new BNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else  {
        if (root->n == 2*t-1){
            BNode *s = new BNode(t, false);

            s->childs[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->childs[i]->insertNonFull(k);

            root = s;
        }
        else 
            root->insertNonFull(k);
    }
}

int BTree::minimum( BNode *x) {
    return (x->leaf==true) ? x->keys[0] : minimum(x->childs[0]);
}

int BTree::maximum(BNode *x) {
    return (x->leaf==true) ? x->keys[x->n-1] : maximum(x->childs[x->n]);
}

void BNode::insertNonFull(int k) {
    int i = n-1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k){
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    }
    else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (childs[i+1]->n == 2*t-1) {
            splitChild(i+1, childs[i+1]);
            if (keys[i+1] < k)
                i++;
        }
        childs[i+1]->insertNonFull(k); 
    }
}

void BNode::splitChild(int i, BNode *y){
    BNode *z = new BNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    if (y->leaf == false){
        for (int j = 0; j < t; j++)
            z->childs[j] = y->childs[j+t];
    }
    y->n = t - 1; 

    for (int j = n; j >= i+1; j--)
        childs[j+1] = childs[j];

    childs[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    keys[i] = y->keys[t-1];
    n = n + 1;
}


int main(){
    BTree t(3);
    t.insert(10);
    t.insert(20);
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
    
    return 0;
}