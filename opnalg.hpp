//This file will house the opn algorithm.
#pragma once
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <vector>
#include <omp.h>
#include <fstream>
#include "tools.hpp"
#include "enum_primes.hpp"
#include "tree.hpp"
#include "expalg.hpp"
using std::vector;
using NTL::ZZ;
using NTL::RR;
using NTL::pow;

struct Stats{

  Stats(ZZ updatefreq = ZZ(10007))// 100003
  { freq = updatefreq; number_found = 0;}

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
              vector<vector<ZZ> >& exp_seqs);

void record_branch(vector<ZZ>& primes, ZZ& num_found);
void record(Stats& s, bool endflag = false);
ZZ primes_between(ZZ& lower, ZZ& upper);

void expand(vector<ZZ>& primes, ZZ& nums, Enum_Primes& list);
void expand_sets(vector<Node*>& leaves, Stats& s);
void OPAN(int d);


