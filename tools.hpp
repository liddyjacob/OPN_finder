//Tools.
#pragma once

#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <iostream>
#include <vector>
#include "list.hpp"

using NTL::RR;
using NTL::ZZ;
using std::vector;

using NTL::conv;
using NTL::NextPrime;
//#define DEBUG

#ifdef DEBUG
template<typename T>
void printvect(vector<T> vect);
#endif


RR Delta(ZZ& p, ZZ& e);
RR Delta(ZZ& p);

RR Delta(ZZ& p, ZZ& e);

RR Delta(ZZ& p);
RR del_neg(ZZ& p, ZZ& e);
RR b_inf(ZZ& p); 
RR b_inf(vector<ZZ>& primes);
RR b(ZZ& p, ZZ& e);
RR b_1(ZZ& p);
RR b_1(vector<ZZ>& prime);
RR b(ZZ& p);
RR b(vector<ZZ>& primes, vector<ZZ>& expos);
bool primitive(vector<ZZ>& primes, vector<ZZ>& expos, List& l);
//REQUIRES AT LEAST TWO PRIMES.
bool primitive(vector<ZZ>& primes, vector<ZZ>& expos);
RR mb(vector<ZZ>& primes,vector<ZZ>& expos, List& l);
ZZ def_prime(vector<ZZ>& primes);

