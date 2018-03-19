//This file will house the opn algorithm.
#pragma once
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <vector>
#include <omp.h>
#include <fstream>
#include "tree.hpp"
#include "expalg.hpp"
#include "tools.hpp"

using std::vector;
using NTL::ZZ;
using NTL::RR;
using NTL::pow;

struct Stats{

  Stats(ZZ updatefreq = ZZ(10007))// 100003
  { freq = updatefreq; }

  ZZ number_found;
  ZZ freq;
  ZZ product;

  vector<ZZ> max_primes;
  vector<ZZ> max_exps;
};

void modify(Stats& s, vector<ZZ>& primes, vector<vector<ZZ> >& exp_seqs);

bool cap_check(vector<ZZ>& primes, 
               vector<Tree>& factor_trees, 
               int& factors);

bool exp_find(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs,
              vector<vector<ZZ> >& leaves);

void record(Stats& s);
ZZ primes_between(ZZ& lower, ZZ& upper);

void expand(vector<ZZ>& primes, Stats& s);
void expand_sets(vector<vector<ZZ> >& leaves, Stats& s);

void OPAN(int d);

bool exp_find_noexp(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs, Stats& s);
