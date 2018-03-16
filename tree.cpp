//Tree.hpp

#include "tree.hpp"

#include <vector>
#include <algorithm>

#include <NTL/ZZ.h>
#include <NTL/RR.h>

using std::vector;
using std::max;

using NTL::ZZ;
using NTL::RR;
using NTL::NextPrime;
using NTL::conv;


void grow(Tree& t, RR bound){

  bound = max(bound, conv<RR>(t.curr->p + ZZ(1)));

  // If there are any children: Need to worry about them.
  if (!t.curr->children.empty()){

    RR maxchild = conv<RR>(t.curr->children.back()->p);
    bound = max(maxchild + RR(1), bound); 
  }

  ZZ nextprime = NextPrime(NTL::CeilToZZ(bound));

  Node* extend = new Node(nextprime, t.curr);
  
  t.curr = extend;
}

void strip_helper(Node* n, vector<ZZ>& primes){
  if (n->p == 1) { return; }
  strip_helper(n->parent, primes);
  primes.push_back(n->p);
}

vector<ZZ> strip_primes(Tree& t){
  vector<ZZ> primes;
  strip_helper(t.curr, primes);
  return primes;
}

void replace(Tree& t, ZZ rep){
  t.curr->p = rep;
}

bool fail(Tree& t){

  while (!t.curr->success){

    Node* failed = t.curr;
    t.curr = t.curr->parent;
    delete failed;
    t.curr->children.pop_back();

    if (t.curr->p == ZZ(1) && (!t.curr->success))
      return false;
  }

  t.curr->tried = true;

  while (t.curr->tried){
    t.curr = t.curr->parent;
  }

  return true;
}

void success(Tree& t){
  Node* node = t.curr;
  node = node->parent;

  if (node->children.size() == 2){
    delete node->children[0];
    node->children.erase(node->children.begin());
  }

  while (node->p != ZZ(1)){
    node->success = true;
    node = node->parent;
    
    // A shortcut:
    if (node->success == true) {break;}
  }

  t.curr = t.curr->parent;
}



