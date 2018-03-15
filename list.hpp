//To house the list structure

#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <vector>
#include <iostream>

#include "tools.hpp"

using std::vector;
using NTL::RR;
using NTL::ZZ;

class ListIter;

struct Node{

  Node(Node* prev, Node* next, int p_index, RR delta)
    : prev(prev), next(next), p_index(p_index), delta(delta)
  { }

  Node(){
    prev = NULL;
    next = NULL;
  }

  Node* prev;
  Node* next;
  int p_index;
  RR delta;
};

//A doubly linked list:
struct List{
  // Initialize the list to:
  // 0 <-> 1 <-> 2 <-> ... <-> size - 1 
  List(vector<ZZ>& primes){
    if (primes.size() == 0) {
      std::cerr << "Initialization of list with empty prime sequence!\n";
      return;
    }

    head = new Node;
      head->p_index = 0;
      head->delta = Delta(primes[0], ZZ(1));

    Node* current = head;

    for (int i = 1; i < primes.size(); ++i){
        Node* next = new Node;
          next->p_index = i;
          next->delta = Delta(primes[i], ZZ(1));

        // Link the nodes: 
        current->next = next;
        next->prev = current; 

        // Move on to next node
        current = next;
    }
    // Finally, save the tail:
    tail = current; // NULL is default next
  }

  Node* head;
  Node* tail;
};

class ListIter{
public:

  ListIter(List& l){
    position = l.head;
  };

  ListIter(Node* n)
    : position(n)
  { }

  int& operator*() {return position->p_index;}
  //Prefix iterator
  ListIter& operator++() {position = position->next; return *this;}

private:

  Node* position;
};

ListIter begin(List l) { return ListIter(l.head); }
ListIter end(List l)   { return ListIter(l.tail);}


#ifdef TEST
void display(List l);

void test_list(){

  vector<ZZ> primes;
    primes.push_back(ZZ(3));
    primes.push_back(ZZ(7));
    primes.push_back(ZZ(11));
    primes.push_back(ZZ(13));
    primes.push_back(ZZ(19));
  
  List l(primes);
  display(l);
}

void display(List l){

  ListIter iter(l);
//  while
}



#endif //TEST
