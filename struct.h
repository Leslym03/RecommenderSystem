
#include<iostream>
#include <vector>
#include <fstream>
using namespace std;

class Linkedlist;

class Nodo{
    private:
        
        Nodo* next;
        int data;
        float rating;
    public:
        Nodo();
        int getData();
        float getRating();
        void setData(int newData, char newRating);
friend class Linkedlist;
};


class Linkedlist{
        Nodo* head;
        int size;
    public:
        Linkedlist();

        void insert(int data, float rating);
        int search(int data);
        void remove(int data);

        void printlist();
        int getSize();

        ~Linkedlist();
friend class Nodo;
};

class BNode {
    int n;
    int t;
    bool leaf;
    vector <int> keys;
    vector <BNode *> childs;
    Linkedlist* ptrList;
public:
    BNode(int _t, bool _leaf);

    void linkList(Linkedlist list);
    void insertNonFull(int k);
    void splitChild(int i, BNode *y);
    void traverse();
    BNode *search(int k);

friend class BTree;
friend class Linkedlist;
};

class BTree{
    BNode *root;
    int t;
public:
    BTree(int _t) {
        root = NULL;  t = _t;
    }

    void traverse() {
        if (root != NULL) root->traverse();
    }

    BNode* search(int k) {
        return (root == NULL)? NULL : root->search(k);
    }

    BNode* getRoot() {
        return root;
    }

    int minimum(BNode *x);
    int maximum(BNode *x);

    void insert(int k);

friend class BNode;
};

