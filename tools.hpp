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

//#define DEBUG

#ifdef DEBUG
template<typename T>
void printvect(vector<T> vect){
  for (auto v : vect){
    std::cout << v << ", ";
  }
}
#endif


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

  #ifdef DEBUG
    std::cout << "In b with: ";
    printvect(primes);
    std::cout << "\nAnd exponents: ";
    printvect(expos);
    std::cout << std::endl;
  #endif

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

  #ifdef DEBUG
    std::cout << "In Primitive with: ";
    printvect(primes);
    std::cout << "\nAnd exponents: ";
    printvect(expos);
    display(l);
  #endif

  for (int i = l.size() - 1; i > 0; --i){
    ZZ p = primes[l[i]];
    ZZ e = expos[l[i]];
 
    if (b(primes, expos) * del_neg(p, e) >= RR(2))
      return false;
  }

  #ifdef DEBUG
    std::cout << "Primitive Succeeded\n";
  #endif

  return true;
}

RR mb(vector <ZZ> primes,vector<ZZ> expos, List& l){
  #ifdef DEBUG
    std::cout << "In mb with: ";
    printvect(primes);
    std::cout << "\nAnd exponents: ";
    printvect(expos);
    std::cout << std::endl;
  #endif

  RR product(1);

  for (int i = 0; i < l.at(); ++i){
    product *= b(primes[l[i]], expos[l[i]]);
  }
  
  #ifdef DEBUG
    std::cout << "Finite Product: " << product << std::endl;
  #endif

  for (int i = l.at(); i < l.size(); ++i){
    product *= b_inf(primes[l[i]]);
  }

  #ifdef DEBUG
    std::cout << "Total Product: " << product << std::endl;
  #endif
 
  return product;
}
