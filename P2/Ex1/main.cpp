/*
 * Main per tal de comprovar el correcte funcionament del TAD ArrayDeque.
 */

/* 
 * File:   main.cpp
 * Author: Martí Pedemonte i Gabriel Marín
 *
 * Created on 6 de marzo de 2018, 8:59
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

#include "ArrayDeque.h"

using namespace std;

int menu(vector<string> a){
    int i;
    for(i = 0; i<a.size(); i++){
        cout << i+1 << ".\t "<< a[i] << endl;
    }
    cin >> i;
    i--;
    if(i<0 || i >= a.size()){
        cout<<"Opció incorrecte."<<endl;
        return menu(a);
    }
    return i;
}

void insertFront(ArrayDeque &array){
    try{
        int element;
        cout << "Introdueix l'element a inserir: ";
        cin >> element;
        array.insertFront(element);
        cout << "Element " << element << " agregat pel davant." << endl;
    }catch(invalid_argument& e){
        cout<<e.what()<<endl;
    }
}

void insertRear(ArrayDeque &array){
    try{
        int element;
        cout << "Introdueix l'element a inserir: ";
        cin >> element;
        array.insertRear(element);
        cout << "Element " << element << " agregat pel darrera." << endl;
    }catch(invalid_argument& e){
        cout<<e.what()<<endl;
    }
}

void deleteFront(ArrayDeque &array){
    try{
        int element = array.getFront();
        array.deleteFront();
        cout << "Element " << element << " eliminat pel davant." << endl;
    }catch(invalid_argument& e){
        cout<<e.what()<<endl;
    }
}

void deleteRear(ArrayDeque &array){
    try{
        int element = array.getRear();
        array.deleteRear();
        cout << "Element " << element << " eliminat pel darrera." << endl;
    }catch(invalid_argument& e){
        cout<<e.what()<<endl;
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    vector<string> vec_options(6);
    int option, max;
    ArrayDeque *array;
    
    vec_options[0]="Inserir element pel davant";
    vec_options[1]="Inserir element pel final";
    vec_options[2]="Eliminar element pel davant";
    vec_options[3]="Eliminar element pel final";
    vec_options[4]="Imprimir contingut de l’ArrayDEQUE";
    vec_options[5]="Sortir";
    
    cout<<"Introdueix la mida de l'ArrayDEQUE: ";
    cin>>max;
    try{
        array=new ArrayDeque(max);
        do{
            cout<<"Que vols fer?"<<endl;
            option=menu(vec_options);
            switch(option){
                case 0:
                    insertFront(*array);
                    break;
                case 1:
                    insertRear(*array);
                    break;
                case 2:
                    deleteFront(*array);
                    break;
                case 3:
                    deleteRear(*array);
                    break;
                case 4:
                    array->print();
                    break;
                case 5:cout<<"Adéu!"<<endl;;
            }
        }while(option!=5);
        delete array;
    }
    catch(invalid_argument& e){
        cout<<e.what()<<endl;
    }
    
    vec_options.clear();
    vector<string>().swap(vec_options);
    delete &vec_options;
    return 0;
}

