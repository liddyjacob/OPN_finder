//To house the list structure
#pragma once

#define TEST

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
// LINK IN ORDER OF GREATEST TO LEAST!
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
      head->delta = Delta(primes[0]);

    Node* current = head;

    for (int i = 1; i < primes.size(); ++i){
        Node* next = new Node;
          next->p_index = i;
          next->delta = Delta(primes[i]);

        // Link the nodes: 
        current->next = next;
        next->prev = current; 

        // Move on to next node
        current = next;
    }
    // Finally, save the tail:
    tail = current; // NULL is default next
  }

  List(List& l);
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

  ListIter& operator++() {position = position->next; return *this;}
  ListIter& operator--() {position = position->prev; return *this;}

  Node* position;
};

RR & delta(ListIter& iter){return iter.position->delta;}
int& index(ListIter& iter){return iter.position->p_index;}

bool operator==(const ListIter& l1, const ListIter& l2){
  return l1.position == l2.position;
}

bool operator!=(const ListIter& l1, const ListIter& l2){
  return l1.position != l2.position;
}

List::List(List& l){

    ListIter iter(l);
    
    Node* current = NULL;

    while (iter.position != NULL){
      RR d = delta(iter);
      int i = index(iter);

      Node* next = new Node;
        next->delta = delta;
        next->p_index = i;

      Node* current = NULL;

      if (current != NULL){
        current->next = next;
        next->prev = current;
      } else { 
        head = next;
      }

      current = next;
      ++iter;
    }

    tail = current;

  }


void place_before(ListIter& l1, ListIter& l2, List& G){
// p1 <-> l2 <-> q1 <-> ... p2 <-> l1 <-> q2 ... 
// First, replace p2->next with q2 // p2 -> q2; l2 <- q2 
// IF Q2 IS NOT NULL:
//  Likewise, rep  q2->prev with p2 // p2 -> q2, p2 <- q2

// replace l2 -> prev with p1.
// replace l2 -> next with l1 // p1 <-> l1
// replace l1 -> prev with l2
// IF P1 IS NOT NULL:
//  replace P1->next with l2: // p1 -> l2; l2 

  Node* n1 = l1.position;
  Node* n2 = l2.position;

  Node* p2 = n1->prev;
  Node* q2 = n1->next;

  p2->next = q2;
  if (q2) { q2->prev = p2; }

  Node* p1 = n2->prev;
  n1->prev = p1;
  n1->next = n2;
  n2->prev = n1;
  if (p1) {p1->next = n2;}
  else {G.head = n1;}
}

void place_after(ListIter& l1, ListIter& l2, List& G){
  Node* n1 = l1.position;
  Node* n2 = l2.position;

  Node* p2 = n1->prev;
  Node* q2 = n1->next;

  p2->next = q2;
  if (q2) { q2->prev = p2; }

  Node* q1 = n2->next;
  n1->prev = n2;
  n1->next = q1;
  n2->next = n1;
  if (q1) {q1->prev = n2;}
  else {G.tail = n1;}
}
ListIter begin(List l) { return ListIter(l.head); }
ListIter end(List l)   { return ListIter(l.tail);}

#ifdef TEST
void display(List l);

void test_list(){

  vector<ZZ> primes;
    primes.push_back(ZZ(2));
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
  for(iter; iter != end(l); ++iter){
    std::cout << "Element Index: " << index(iter) << "; ";
    std::cout << "Delta: " << delta(iter) << std::endl;
  }

}



#endif //TEST
