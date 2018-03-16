//This file will house the opn algorithm.
#pragma once
#include <NTL/RR.h>
#include <NTL/ZZ.h>
#include <vector>
#include <omp.h>
#include <fstream>
//#include "tree.hpp"
//#include "expalg.hpp"
//#include "tools.hpp"

using std::vector;
using NTL::ZZ;
using NTL::RR;

bool cap_check(vector<ZZ>& primes, 
               vector<Tree>& factor_trees, 
               int& factors);

bool exp_find(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs,
              vector<vector<ZZ> >& leaves);

void record(vector<ZZ>& primes,
            vector<vector<ZZ >>& exp_seqs);

void expand(vector<ZZ>& primes);
void expand_sets(vector<vector<ZZ> >& leaves);

void OPAN(int d);

bool exp_find_noexp(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs);

