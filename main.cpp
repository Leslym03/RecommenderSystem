#include <iostream>
#include "struct.h"
using namespace std;


int main(){
    Linkedlist lista;
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