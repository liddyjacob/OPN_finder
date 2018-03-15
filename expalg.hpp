// The exponent algorithms.

#include <vector>
#include <NTL/ZZ.h>
#include <algorithm> // std::fill


#include "tools.hpp"
#include "list.hpp" // Doubly linked list, sorted, of integers.
using std::vector; // vector<>
using NTL::ZZ; // ZZ

/*
  expAlg: Returns the exponents found when looking for all
primitive abundant numbers whose primes compose P(primes)
*/
vector<vector<ZZ> > expAlg(vector<ZZ>& primes);
void initiate(vector<ZZ>& primes, 
              vector<ZZ>& expos, 
              vector<vector<ZZ> >& exp_seqs);
bool orderDel(vector<ZZ>& primes,
              vector<ZZ>& expos,
              vector<vector<ZZ> >& exp_seqs,
              List& G,
              ListIter iter);
bool expIncAlg(vector<ZZ>& primes,
               vector<ZZ>& expos,
               vector<vector<ZZ> >& exp_seqs,
               List& G,
               ListIter iter);

vector<vector<ZZ> > expAlg(vector<ZZ>& primes){

  int divisors = primes.size();
  vector<ZZ> expos(divisors);
  std::fill (expos.begin(), expos.end(), ZZ(1));
  
  vector<vector<ZZ> > exp_seqs;

  if (b_inf(primes) < RR(2)){ return exp_seqs; }

  initiate(primes, expos, exp_seqs);

  return exp_seqs;
}

void initiate(vector<ZZ>& primes, 
              vector<ZZ>& expos, 
              vector<vector<ZZ> >& exp_seqs){

  if (b(primes, expos) >= RR(2)){
    if (b(primes, expos) / b(primes.back()) < RR(2)){
      exp_seqs.push_back(expos);
    }
    return;
  }

  
  List G(primes); // Initialize a doubly linked list as 0, 1, ..., p.
  ListIter iter(G);

  orderDel(primes, expos, exp_seqs, G, iter);

  return;
}

bool orderDel(vector<ZZ>& primes,
              vector<ZZ>& expos,
              vector<vector<ZZ> >& exp_seqs,
              List& G,
              ListIter iter){

  bool found = false;
  int i = 0;
  RR precalc_b = b(primes, expos);

  while (iter != end(G)){

    if (precalc_b * delta(iter) >= RR(2)){
      //Set new exponents:
      vector<ZZ> expos_new = expos;
        expos_new[index(iter)] += ZZ(1);

      if (primitive(primes, expos_new, G)){
        exp_seqs.push_back(expos_new);
        found = true;
      }

      ++iter;
    } else {
      break;
    }
  }

  if (iter != end(G)){
    if (expIncAlg(primes, expos, exp_seqs, G, iter)){ 
      return true;
    }
  }

  return found;
}
      

bool expIncAlg(vector<ZZ>& primes,
               vector<ZZ>& expos,
               vector<vector<ZZ> >& exp_seqs,
               List& G,
               ListIter iter){

  bool found = false;

  while (iter != end(G)){
    if (mb(primes, expos, iter) > RR(2)){

      vector<ZZ> expos_new = expos;
        expos_new[index(iter)] += ZZ(1);

      List& Gnew(G);

      //Does NOT modify iter - modifies contents of G.
      resort(iter, Gnew, primes[index(iter)], expos_new[index(iter)]);

      if (orderDel(primes, expos_new, exp_seqs, G, iter)){found = true;}
      ++iter;
    } else { break; }
  }

  return found;
}
