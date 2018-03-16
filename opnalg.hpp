//This file will house the opn algorithm.

#include "tree.hpp"
#include "expalg.hpp"
#include "tools.hpp"

using std::vector;
using NTL::ZZ;
using NTL::RR;

bool cap_check(vector<ZZ>& primes, 
               vector<Tree>& factor_trees, 
               int& factors);

bool exp_find(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs);

void record(vector<ZZ>& primes,
            vector<vector<ZZ >>& exp_seqs);


void OPAN(int d){

  std::vector<Tree> factor_trees;

  for (int factors = 3; factors <= d; ++factors){

    factor_trees.push_back(Tree());

    Tree tree = factor_trees.back();
      grow(tree, RR(3));

    vector<vector<ZZ> > exp_seqs;
    bool growing = true;

    while (growing){

      grow(tree, RR(3));
      std::vector<ZZ> primes = strip_primes(tree);

      //See if the tree still needs to grow;
      if (primes.size() != factors) {
        exp_seqs.clear();        
        if (b_1(primes) >= RR(2)){
        
          primes.pop_back();
          ZZ replacement = def_prime(primes);
          replace(tree, replacement);

        }
        
        continue;

      }

      if (b_inf(primes) <= RR(2)){
        growing = fail(tree); 
        continue;
      }


      if (exp_find(primes, exp_seqs)){

        record(primes, exp_seqs);
        success(tree);

      } else {

        //cap check - see if primes is at its cap!
        if (!cap_check(primes, factor_trees, factors)){ 
          growing = fail(tree);
        }
      }


    }

  }

  return;
}


bool exp_find(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs){
/*
  if (!exp_seqs.empty()){
    int i = 0;
    for (auto exps : exp_seqs){
      if (b(primes, exps) < RR(2)){ break; }            
      if (!primitive(primes, exps)) { break; }
      ++i;
    }
    if (i != exp_seqs.size()) {

      exp_seqs = expAlg(primes);
      return (!exp_seqs.empty());

    } else {
      return true;
    }
  }
*/
  exp_seqs = expAlg(primes);
  return (!exp_seqs.empty());
}

bool cap_check(vector<ZZ>& primes, 
               vector<Tree>& factor_trees, 
               int& factors){
/*
  ZZ truncp = backup(factor_tree);
  primes = strip_primes(factor_tree);

  if (primes.size() >= factors - 1){
    return false;
  }

  ZZ cap = findmax(factor_trees, factors);

  if (truncp <= cap) { 
    grow(tree, conv<RR>(truncp + 1));
    return true;
  }
*/
  return false;
}

void record(vector<ZZ>& primes, vector<vector<ZZ> >& expos){

  return;
}
