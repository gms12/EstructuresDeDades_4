/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BalancedBST.h
 * Author: Gabriel
 *
 * Created on 1 de mayo de 2018, 20:49
 */

#ifndef BALANCEDBST_H
#define BALANCEDBST_H

#include <iostream>
#include <math.h>
#include "NodeTree.h"
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

    template <class Type> class BalancedBST{
        public:
        //Constructors
        BalancedBST();//TEST: 
        BalancedBST(const BalancedBST& orig);//TEST: 
        //Destructor
        virtual ~BalancedBST();//TEST: 
        //Consultors
        int size() const;//TEST: 
        bool isEmpty() const;//TEST: 
        NodeTree<Type>* root() const;//TEST: 
        NodeTree<Type>* search(int key);//TEST: 
        void printInorder();//TEST: 
        void printPreorder() const;//TEST: 
        void printPostorder() const;//TEST: 
        int getHeight();//TEST: 
        int getCounter() const;//TEST:
        //Modificadors
        void insert(const Type& element, int key);//TEST: 
        void setCounter(int c);
        //Mirall
        BalancedBST<Type>* mirror();//TEST: 
    private:
        //Mètodes privats interns
        void postDelete(NodeTree<Type>* p);
        int size(NodeTree<Type>* p) const;
        void printPreorder(NodeTree<Type>* p) const;
        void printPostorder(NodeTree<Type>* p) const;
        void printInorder(NodeTree<Type>* p);
        int getHeight(NodeTree<Type>* p);
        void insert(NodeTree<Type>* p, const Type& element, int key);
        NodeTree<Type>* search(NodeTree<Type>* p, int key);
        NodeTree<Type>* constructor_copia(NodeTree<Type>* from);
        NodeTree<Type>* constructor_mirall(NodeTree<Type>* from);
        NodeTree<Type>* rightRotation(NodeTree<Type>* p);//nou metode
        NodeTree<Type>* leftRotation(NodeTree<Type>* p);//nou metode
        int getBalance(NodeTree<Type>* p) const;//nou metode
        //Atributs
        NodeTree<Type>* pRoot;
        int counter;
    };

//Constructor per defecte. Punter arrel a null.
template <class Type> BalancedBST<Type>::BalancedBST(){
    this->pRoot = nullptr;
    this->counter = 0;
    cout << "Arbre creat" << endl;
}
//Constructor còpia.
template <class Type> BalancedBST<Type>::BalancedBST(const BalancedBST& orig){
    this->pRoot = constructor_copia(orig.root());
    this->counter = orig.getCounter();
    cout << "Arbre creat" << endl;
}
//Metode auxuliar per al constructor. Recorrem en preordre i anem copiant node a node
template <class Type> NodeTree<Type>* BalancedBST<Type>::constructor_copia(NodeTree<Type>* from){
    if(from==nullptr)return nullptr;//si l'arbre donat és null fem el nostre null
    else{
        NodeTree<Type>* newNode = new NodeTree<Type>(*from);//copiem el node
        newNode->setLeft(constructor_copia(from->getLeft()));//cridem per copiar el node de l'esq
        newNode->setRight(constructor_copia(from->getRight()));//cridem per copiar el node de la dreta    
        return newNode;//retornem el node
    }
}
//Destructor.
template <class Type> BalancedBST<Type>::~BalancedBST(){
    this->postDelete(this->pRoot);
    cout << "Arbre eliminat" << endl;
}

//Destrueix un subarbre donada la seva arrel. Metode auxiliar per al destructor
template <class Type> void BalancedBST<Type>::postDelete(NodeTree<Type>* p){
    if(p!=nullptr){    
        //primer eliminem el subarbre de l'esquerra
        if(p->hasLeft()) this->postDelete(p->getLeft());
        //despres eliminem al subarbre de la dreta
        if(p->hasRight()) this->postDelete(p->getRight());
        //per ultim eliminem el node en questio
        delete p;
    }
}

//Retorna el nombre de NodeTrees que hi ha a l'arbre.
template <class Type> int BalancedBST<Type>::size() const{
    return this->size(this->pRoot);
}

//Retorna el nombre de NodeTrees que hi ha en un subarbre donada la seva arrel.
template <class Type> int BalancedBST<Type>::size(NodeTree<Type>* p) const{
    //si el Node p es nul, retornem 0
    if(p==nullptr) return 0;
    //altrament, sabem que n'hi ha un i mirem els seus fills
    else return 1 + size(p->getLeft()) + size(p->getRight());
}

//Retorna true si l'arbre està buit, false en cas contrari.
template <class Type> bool BalancedBST<Type>::isEmpty() const{
    return (this->pRoot == nullptr);
}

//Retorna l'adreça de l'arrel.
template <class Type> NodeTree<Type>* BalancedBST<Type>::root() const{
    return this->pRoot;
}

//Cerca un element. Retorna true si el troba, false en cas contrari.
template <class Type> NodeTree<Type>* BalancedBST<Type>::search(int key) {
    return this->search(pRoot,key);
}

//Cerca un element a partir d'un node. Quan el troba retorna el node.
template <class Type> NodeTree<Type>* BalancedBST<Type>::search(NodeTree<Type>* p, int key) {
    //si el node es null o el seu valor es el que busquem, el retornem
    if(p==nullptr || p->getKey()==key)return p;
    //si el seu valor es mes gran, busquem al fill de l'esquerra
    else if(p->getKey()>key && p->hasLeft()){
        return search(p->getLeft(),key);
    }
    //si no, com tindra un valor inferior, busquem al fill de la dreta
    else if(p->hasRight()){
        return search(p->getRight(),key);
    }
    return nullptr;//Si no ha estat agafat en un dels dos ifs vol dir que no existeix l'element
}

//Retorna un enter amb l'alçada d'un arbre, donada la seva arrel.
template <class Type> int BalancedBST<Type>::getHeight(NodeTree<Type>* p){
    //si el Node p es nul, retornem 0. L'alçada d'una fulla serà 1
    if(p==nullptr)return 0;
    //altrament, sabem que n'hi ha un i mirem els seus fills
    else return 1 + max(getHeight(p->getLeft()),getHeight(p->getRight()));
}
//Afegeix un nou NodeTree a l'arbre binari.
template <class Type> void BalancedBST<Type>::insert(const Type& element, int key){
    if(this->isEmpty()){//comprovem si l'arbre esta buit
        this->pRoot=new NodeTree<Type>(element, key);
    }
    else this->insert(pRoot,element, key);//si no esta buit cridem el metode auxiliar
    cout<<"S'insereix a l'arbre l'element "<<element.toString()<<endl;
}
//Metode auxiliar a insert. Se li passa també un node, per a poder ser recursiu
template <class Type> void BalancedBST<Type>::insert(NodeTree<Type>* p, const Type& element, int key){
    if(p->getKey()>key){//si el valor es inferior, anira a l'esq
        if(!p->hasLeft()){
            p->setLeft(new NodeTree<Type>(element, key));
        }//si no te fill esq, l'afegim. Si no, cridem el metode pel fill de lesq
        else this->insert(p->getLeft(),element, key);
    }
    else{//si es superior anira a la dreta
       if(!p->hasRight()){//Igual que abans pero per l'altre costat
            p->setRight(new NodeTree<Type>(element, key));
        }
       else this->insert(p->getRight(),element, key);    
    }
    //Ara hem de fer les comprovacions i balancejar l'arbre si s'escau
    int bal=getBalance(p);
    //Cas simple esq
    if(bal>1 && key<p->getLeft()->getKey()){}
    //Cas simple dret
    if(bal<-1 && key>p->getRight->getKey()){}
    //Cas complexe esq
    if(bal>1 && key>p->getLeft()->getKey()){}
    //Cas complexe dret
    if(bal<-1 && key>p->getRight->getKey()){}
}
//Metode per a fer una rotacio cap a la dreta
template <class Type> void BalancedBST<Type>::rightRotation(NodeTree<Type>* p){}
//Metode per a fer una rotacio cap a l'esquerra
template <class Type> void BalancedBST<Type>::leftRotation(NodeTree<Type>* p){}
//Metode per a calcular el balanceig d'un node
template <class Type> int BalancedBST<Type>::getBalance(NodeTree<Type>* p){
    if(p==nullptr)return 0;
    return getHeight(p->getLeft())-getHeight(p->getRight());
}
#ifdef __cplusplus
}
#endif

#endif /* BALANCEDBST_H */

