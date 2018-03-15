//Tools.
#pragma once

#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <iostream>

#include <vector>

using NTL::RR;
using NTL::ZZ;
using std::vector;
using NTL::conv;

RR Delta(ZZ& p, ZZ& e);
RR Delta(ZZ& p);

RR Delta(ZZ& p, ZZ& e){

  RR pr = conv<RR>(p); // convPrec(p, 53)
  RR er = conv<RR>(e);

  return (pow(pr, er + RR(2)) - RR(1)) /
/*      -----------------------------------       */
         (pr * (pow(pr, er + RR(1)) - RR(1)));
}

RR Delta(ZZ& p){
  ZZ e(1);
  return Delta(p, e);
}

RR del_neg(ZZ& p, ZZ& e){

  RR pr = conv<RR>(p);
  RR er = conv<RR>(e);

  return (pr * (pow(pr, er) - RR(1))) /
/*       --------------------------      */
         (pow(pr, er + RR(1)) - RR(1));
}

#include "list.hpp"

RR b_inf(ZZ& p) {
  RR pr = conv<RR>(p);
  return (pr)/(pr - RR(1));
}

RR b_inf(vector<ZZ>& primes){

  RR product(1);

  for (prime : primes){ product *= b_inf(prime); }

  return product;
}

RR b(ZZ& p, ZZ& e){
  RR pr = conv<RR>(p);
  RR er = conv<RR>(e);
  return (pow(pr, er + RR(1)) - RR(1)) /
/*       ----------------------------    */
         ((pr - RR(1)) * pow(pr, er));

}

RR b(ZZ& p){
  ZZ e(1);
  return b(p, e);
}

RR b(vector<ZZ>& primes, vector<ZZ>& expos){

  if (primes.size() != expos.size()){
    std::cerr << "from b(P, E): Exponent and prime sequence sizes are not the same!\n";
    return RR(-1);
  }

  RR product(1);

  for (int i = 0; i < primes.size(); ++i){ product *= b(primes[i], expos[i]); }

  return product;
}

//REQUIRES AT LEAST TWO PRIMES.
bool primitive(vector<ZZ>& primes, vector<ZZ>& expos, List& l){

  ListIter iter(l);
  iter.position = l.tail->prev;

  for (iter; iter != begin(l); --iter){
    ZZ p = primes[index(iter)];
    ZZ e = primes[index(iter)];
    if (b(primes, expos) * del_neg(p, e) >= RR(2))
      return false;
  }

  return true;
}


//delta(iter) got smaller, move to the right.
void resort(ListIter iter, List G,  ZZ& p, ZZ& e){

  delta(iter) = Delta(p, e); 
  ListIter curr = iter;

  while (curr != end(G)){
    if (delta(curr) > delta(iter)){
      ++curr;
    } else { 
      place_before(iter, curr, G);
      return;
    }
  }

  if (delta(curr) > delta(iter)){
    place_after(iter, curr, G);
  } else {
    place_before(iter, curr, G);
  } 
}

RR mb(vector <ZZ> primes,vector<ZZ> expos, ListIter iter){

  ListIter after = iter; // To infinite exponent
  ListIter before = iter; // to regular exponent
    --before;

  RR product(1);

  while (before.position != NULL){
    product *= b(primes[index(before)], expos[index(before)]);
    --before;
  }

  while (after.position != NULL){
    product *= b_inf(primes[index(after)]);
    ++after;
  }

  return product;
}






