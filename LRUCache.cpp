/*LRU Cache Implementation
Written By : Lakha Rahman 
On : 17/04/2022
LRU Cache helps in fast acess of  frames by removing the least recently used frame when cache is full 
Double ended queue and hashmap used for optimizing the operation in O(1) time
*/

#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;
 
// Node to store data (Linked List) 
 class Node {
     public : 
     string key;
     int value;
     Node(string key,int value){
         this->key=key;
         this->value=value;
     }
 };
 //Creating LRU cache data structure 
class LRUCache {
public:   
    int maxsize;  //stores max capacity of cache
    
    list <Node> l;  //doubly linked list to store key value pair
    
    unordered_map<string, list<Node>::iterator> ma; // store references of key in cache
    
    
    LRUCache(int size){
        this->maxsize=size>1?size:1;
    }
    
    void insert(string key,int value){
        
        //there already exist the key
        if(ma.count(key)!=0){
            //replace old value with new 
            auto it =ma[key];
            it->value = value;
        }
        else {
            //check if cache is full or not 
            if(l.size()==maxsize){
                //remove least recently used item from cache
                Node last=l.back();
                ma.erase(last.key);   //remove from hashmap;
                l.pop_back(); //remove from list
            }
            Node n(key,value);
            l.push_front(n);
            ma[key]=l.begin();
        }
    }
    //to get value of a particular key
    int* getvalue(string key){
        
        //check if the key is there or not
        if(ma.count(key)!=0){
            auto it=ma[key];
            
            int value=it->value;
            //also inserting it in first of the list as it is most recently used
            l.push_front(*it);
            l.erase(it);
            ma[key]=l.begin();
            return &l.begin()->value;
            
        }
        return NULL;
    }
    
    // to get the most recent key 
    string mostrecentkey(){
        return l.front().key;
    }
    
    //display the linked list
    void display(){
        for (auto it = l.begin(); it != l.end(); it++)
               cout << it->key << " --> "  << it->value <<" | ";
 
              cout << endl;
    }
};
 
 
// Driver Code
int main()
{
    LRUCache ca(3);
    ca.insert("Web1",10);
    ca.insert("Web2",20);
    ca.insert("Web3",10);
    ca.display();
    cout<<"Most Recently used Web is : ";
    cout<<ca.mostrecentkey()<<endl;
    ca.insert("Web4",30);
    ca.display();
    cout<<"Most Recently used Web is : ";
    cout<<ca.mostrecentkey()<<endl;
    
    
 
    return 0;
}
