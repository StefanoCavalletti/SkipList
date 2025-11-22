#include <iostream>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <chrono>

#include "skip_list.h"

SkipList::SkipList(){
    srand(time(NULL));
    head=createNode(-1,SKIPLIST_MAX_LEVEL-1);
    size = 0;
}

bool SkipList::insert(int key){
    int lev = getRandomLevel();
    //std::cout<<"Inserisco nodo " << key << " livello " << lev <<".\n";
    Node* newNode = createNode(key,lev);
    Node* node = head;
    Node* toUpdate[SKIPLIST_MAX_LEVEL];
    for(int i = head->level; i >= 0 ; i--){
        while(node->nextNodes[i] && node->nextNodes[i]->key < key){
            node = node->nextNodes[i];
        }
        toUpdate[i] = node;
    }
    node = node->nextNodes[0];
    if(!node || newNode->key != node->key){
        if(lev > head->level){
            for (int i = head->level+1; i <= lev; i++){
                toUpdate[i] = head;
            }
            head->level = lev;
        }
        for (int i = 0; i <= lev; i++) { // < o <= ???????????
            newNode->nextNodes[i] = toUpdate[i]->nextNodes[i];
            toUpdate[i]->nextNodes[i] = newNode;
        }
        //std::cout<<"Inserito nodo " << newNode -> key << " livello " << newNode->level <<".\n";
        size++;
        return true;
    } else {
        return false;
    }
}

Node* SkipList::search(int key){
    Node* node = head;
    for(int i = head->level; i >= 0 ; i--){
        while(node->nextNodes[i] && node->nextNodes[i]->key < key){
            node = node->nextNodes[i];
        }
    }
    node = node->nextNodes[0];
    if(node && node->key == key){
        return node;
    }
    return nullptr;
}


/* --- Removes a node --- 
return:
true: node found and removed correctly
false: node not found, it was not in the skiplist
*/
bool SkipList::remove(int key){
    Node* node = head;
    Node* toUpdate[SKIPLIST_MAX_LEVEL];
    for(int i=0; i<SKIPLIST_MAX_LEVEL;i++){toUpdate[i] = nullptr;}
    for(int i = head->level; i >= 0; i--){
        while(node->nextNodes[i] && node->nextNodes[i]->key < key){
            node = node -> nextNodes[i];
        }
        toUpdate[i] = node;
    }
    node = node->nextNodes[0];
    if(node && node->key == key){
        for(int i = 0; i<=head->level; i++){
            if(toUpdate[i]->nextNodes[i] != node)
                break; //continue;
            toUpdate[i]->nextNodes[i] = node->nextNodes[i];
        }
        delete[] node->nextNodes;
        delete node;
        while (head->level > 1 && head->nextNodes[head->level - 1] == NULL)
            head->level--;
        size--;
        return true;
    }
    return false;
}

void SkipList::print(){
    std::cout << "\n---- Skip List ----\n";
    for (int i = head->level; i >= 0; i--) {
        Node* node = head->nextNodes[i];
        std::cout << "Livello " << i << ": ";
        while (node) {
            std::cout << node->key << " ";
            node = node->nextNodes[i];
        }
        std::cout << "\n";
    }
    std::cout << "-------------------\n";
}

int SkipList::getRandomLevel(){
    int lev = 0;
    while( ((double)rand()/RAND_MAX) < P  && lev < SKIPLIST_MAX_LEVEL-1){
        lev++;
    }
    return lev;
}

Node* SkipList::createNode(int key, int level){
    Node* node = new Node;
    node->key = key;
    node->level = level;
    node->nextNodes = new Node*[SKIPLIST_MAX_LEVEL];
    for(int i = 0; i < SKIPLIST_MAX_LEVEL; i++){
        node->nextNodes[i] = nullptr;
    }
    return node;
}




void printNode(Node* node){
    std::cout<<"---- Nodo " << node->key << " livello " << node->level <<".\n";
    for(int i = 0; i< node->level+1; i++){
        if(node->nextNodes[i]!= nullptr)
            std::cout<< "Puntatore livello " << i << " ----> " << node->nextNodes[i]->key << ".\n";
    }
}

SkipList::~SkipList() {
    Node* current = head->nextNodes[0];
    while (current != nullptr) {
        Node* temp = current;
        current = current->nextNodes[0];

        // Prima dealloca l'array di puntatori
        delete[] temp->nextNodes;
        // Poi dealloca il nodo
        delete temp;
    }
    
    delete[] head->nextNodes;
    delete head;
}
