#ifndef SKIPLIST_H
#define SKIPLIST_H

#define SKIPLIST_MAX_LEVEL 16
#define P 0.5                            
/*
    -- A Node -- 
    key: containts the value
    level: containts the (higher) level of the node
    nextNodes[i]: containts the pointer to the next Node at level i, if this is the last node at level i it's nullptr
*/
typedef struct Node{
    int key;
    int level;
    Node** nextNodes;
}Node;
/*
    --  SkipList class -- 
    head containts the pointer to the sentinel node which is, by costruction, the lowest node in the list 
    and, of course, at the highest level 
*/
class SkipList{
    private:
        Node* head;
        int size;
    public:
        /* -- Constructor -- */  
        SkipList();
        /* --             --*/

        bool insert(int key);
        
        Node* search(int key);
        
        bool remove(int key);

        void print();

        int getSize(){
            return size;
        }

        int getLevel(){
            return head->level;
        }
        
        Node* getHead(){
            return head;
        }
        Node* getHigherLevelNode(){
            return head->nextNodes[head->level];
        }
        Node* first(){
            return head->nextNodes[0];
        }

        ~SkipList();
        
    private:
        int getRandomLevel();

        Node* createNode(int key, int level);
};

#endif
