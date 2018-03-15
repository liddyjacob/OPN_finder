// The exponent algorithms.

#include <vector>
#include <NTL/ZZ.h>
#include <fill> // std::fill


#include "tools.hpp"

using std::vector; // vector<>
using NTL::ZZ; // ZZ

/*
  expAlg: Returns the exponents found when looking for all
primitive abundant numbers whose primes compose P(primes)
*/
vector<vector<ZZ> > expAlg(vector<ZZ>& primes);
void initiate(vector<ZZ>& primes, 
              vector<ZZ> expos, 
              vector<vector<ZZ> >& exp_seqs);
bool orderDel(vector<ZZ>& primes,
              vector<ZZ>& expos,
              vector<vector<ZZ> >& exp_seqs,
              vector<int>& G,
              int g = 0);
bool expIncAlg(vector<ZZ>& primes,
               vector<ZZ>& expos,
               vector<vector<ZZ> >& exp_seqs,
               vector<int>& G,
               int g = 0);

vector<vector<ZZ> > expAlg(vector<ZZ>& primes){

  int divisors = primes.size();
  vector&<ZZ> expos(divisors);
  std::fill (expos.begin(), expos.end(), ZZ(1));
  
  vector<vector<ZZ> > exp_seqs;

  if (b_inf(P) < ZZ(2)){ return exp_seqs; }

  expAbundant(primes, expos, exp_seq);
}
