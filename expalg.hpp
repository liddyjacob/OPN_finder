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
              int g = -1);
bool expIncAlg(vector<ZZ>& primes,
               vector<ZZ>& expos,
               vector<vector<ZZ> >& exp_seqs,
               List& G,
               int g = -1);

vector<vector<ZZ> > expAlg(vector<ZZ>& primes){

  int divisors = primes.size();
  vector<ZZ> expos(divisors);
  std::fill (expos.begin(), expos.end(), ZZ(1));
  
  vector<vector<ZZ> > exp_seqs;

  if (b_inf(primes) < ZZ(2)){ return exp_seqs; }

  initiate(primes, expos, exp_seqs);

  return exp_seqs;
}

void initiate(vector<ZZ>& primes, 
              vector<ZZ>& expos, 
              vector<vector<ZZ> >& exp_seqs){

  if (b(primes, expos) >= ZZ(2)){
    if (primitive(primes, expos)){
      exp_seqs.push_back(expos);
    }
    return;
  }

  
  List G(primes); // Initialize a doubly linked list as 0, 1, ..., p.

  orderDel(primes, expos, exp_seqs, G);

  return;
}
