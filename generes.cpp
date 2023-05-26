#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <string>
#include <map>
#include<cmath>
#include <iterator>
#include <algorithm>
using namespace std;

class Linkedlist;

class Nodo{
    private:
        
        Nodo* next;
        double data;
    public:
        Nodo();
        int getData();
        void setData(int newData);
friend class Linkedlist;
};


class Linkedlist{
        int key;
        Nodo* head;
        int size;
    public:
        Linkedlist(int setkey);
        Linkedlist();

        void insert(int data);
        int search(int data);
        void remove(int data);
        double cosine(Linkedlist * l1, Linkedlist * l2);
        Nodo* search_node(int data);

        void printlist();
        int getSize();
        int getKey();

        ~Linkedlist();
friend class Nodo;
};

//Nodo
Nodo::Nodo(){
    next=NULL;
}

int Nodo::getData(){
    return data;
}

void Nodo::setData(int newData){
    data=newData;
}

// Linkedlist
Linkedlist::Linkedlist(int setkey){
    head=NULL;
    size=0;
    key=setkey;
}

Linkedlist::Linkedlist(){
    head=NULL;
    size=0;
}

void Linkedlist::insert(int data){
    Nodo* newNodo=new Nodo;
    newNodo->data=data;
    
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

double Linkedlist::cosine(Linkedlist * l1, Linkedlist * l2){
    double ppunto = 0;
    double logx = 0;
    double logy = 0;

    Linkedlist* lista1 = new Linkedlist();
    Linkedlist* lista2 = new Linkedlist();

    //union
    for (int i=1;i<=19;i++){
        int pos1 = l1->search(i);
        int pos2 = l2->search(i);
        //cout << pos1 << "  " << pos2<<endl;

        if (pos1 != -1 && pos2 == -1){
            Nodo* aux1 = l1->search_node(i);
            if(aux1->data == i ){
                lista1->insert(i);
                lista2->insert(0);
            }
        }

        if (pos1 == -1 && pos2 != -1){
            Nodo* aux2 = l2->search_node(i);
            if(aux2->data == i ){
                lista1->insert(0);
                lista2->insert(i);
            }
        }

        if (pos1 != -1 && pos2 != -1){
            Nodo* aux1 = l1->search_node(i);
            Nodo* aux2 = l2->search_node(i);
            if(aux1->data == i &&  aux2->data == i){
                lista1->insert(i);
                lista2->insert(i);
            }
        }

    }
    //lista1->printlist();
    //lista2->printlist();

    if (lista1->getSize() == 0 && lista2->getSize()== 0){
        return -2;
    }

    Nodo* aux1=lista1->head;
    Nodo* aux2=lista2->head;
    for (int i=0;i<lista1->getSize();i++){
        ppunto += (double)aux1->data * (double)aux2->data;
        logx += (double)aux1->data * (double)aux1->data;
        logy += (double)aux2->data * (double)aux2->data;
        aux1=aux1->next;
        aux2=aux2->next;
    }
    
    int denominator = sqrt(logx) * sqrt(logy);
    if (denominator == 0){
        return -2; //es indefinido
    }
    int res= ppunto / denominator;
    return res;
}


int Linkedlist::search(int data){
    int pos=0;
    Nodo* aux1=head;
    while(aux1->data!=data){
        aux1=aux1->next;
        pos++;
        if(!aux1)
            return -1;
    }
    return ++pos;
}

Nodo* Linkedlist::search_node(int data){
    int pos=0;
    Nodo* aux1=head;
    while(aux1->data!=data){
        aux1=aux1->next;        
        pos++;
        if(!aux1)
            return NULL;
    }
    return aux1;
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
        cout<<aux1->data<<"   ";
        aux1=aux1->next;
    }
    cout<<endl;
}

int Linkedlist::getSize(){
    return size;
}

int Linkedlist::getKey(){
    return key;
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


int main(){
    vector <Linkedlist *> lists;
    Linkedlist * prt_list2;
    prt_list2 = new Linkedlist(1);
    prt_list2->insert(2);
    prt_list2->insert(3);
    //prt_list2->printlist();
    //Nodo * ptr_nodo = prt_list2->search_node(2);
    //cout << ptr_nodo->getData() <<endl;
    //cout<< prt_list2->search(5)<<endl;

    map<string, int> map;
    map["Adventure"] = 1;
    map["Animation"] = 2;
    map["Children"] = 3;
    map["Comedy"] = 4;
    map["Fantasy"] = 5;
    map["Romance"] = 6;
    map["Drama"] = 7;
    map["Action"] = 8;
    map["Crime"] = 9;
    map["Thriller"] = 10;
    map["Horror"] = 11;
    map["Mystery"] = 12;
    map["Sci-Fi"] = 13;
    map["IMAX"] = 14;
    map["Documentary"] = 15;
    map["War"] = 16;
    map["Musical"] = 17;
    map["Western"] = 18;
    map["Film-Noir"] = 19;

    string fname= "data/ml-20m/genres.csv";
    vector<string> row;
    string line, word;

    fstream file (fname, ios::in);
	if(file.is_open())
	{
        getline(file, line);
		while(getline(file, line)){
			row.clear();
			stringstream str(line);
			while(getline(str, word, ','))
				row.push_back(word);
            
            string user = row[0];
            int i = stoi(user);
            //cout << row[0] << endl;
            Linkedlist * prt_list;
            prt_list = new Linkedlist(i);
            //cout <<row[1]<< endl;
            string space_delimiter = "|";
            vector<string> words;
            string token;
            stringstream ss(row[1]);
            while (getline(ss, token, '|')){
                    words.push_back(token);
                }
            for (const auto &str : words) {
                int num_gen = map[str];
                prt_list->insert(num_gen);
                //cout << str << endl;
            }
            lists.push_back(prt_list);

		}
	}
	else
		cout<<"Could not open the file\n";

    //cout << endl;
    cout << lists.size() << endl;
    lists[0]->printlist();
    lists[4]->printlist();


    //cout <<lists[0]->search(3)<< endl;
    Linkedlist * opp;
    //cout << opp->cosine(lists[0], lists[4])<< endl;


    //KNN recomendacion
    Linkedlist * user = lists[0];
    //cout << opp->cosine(user, lists[2])<< endl;
    //cout << user->search(3) << endl;
    int knn=5;
    vector<double> list_red;
    vector<int> movie_id;

    for (size_t i = 0; i < lists.size(); i++) {
        if (user != lists[i]){
            double result_cosine = opp->cosine(user, lists[i]);
            if (result_cosine != -2 && result_cosine>0.5) // no sea indefinido
                list_red.push_back(result_cosine); 
                movie_id.push_back(lists[i]->getKey());
        }
    }
    sort(list_red.begin(), list_red.end(), greater<double>());
    for (auto i = 0; i < knn; i++){
        cout << list_red[i] << " ";
        cout << movie_id[i] << " " << endl;
    }
        
    
    cout << " size res " << list_red.size() << endl;


/*
def knn(user, k, metric, data):

    dict_new = {}
    if metric == 'cosine':
        for i in data.keys():
          if i != user:
            res = cosine(data[user],data[i])
            if res != "Nan":
              dict_new [i] = res

        sortedDict = sorted(dict_new.items(), key=lambda x: x[1], reverse=True)

        for x in list(sortedDict)[0:k]:
          print (x)
*/












    return 0;
}
