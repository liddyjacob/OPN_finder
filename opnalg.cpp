//This file will house the opn algorithm.
//#include "tree.hpp"
//#include "expalg.hpp"
//#include "tools.hpp"


#include "opnalg.hpp"


void OPAN(int d){

  std::vector<Tree> factor_trees;
  Stats s;

  for (int factors = 3; factors <= d; ++factors){

    factor_trees.push_back(Tree());
    Tree& tree = factor_trees.back();
      grow(tree, RR(3));

    vector<vector<ZZ> > leaves;
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


      if (exp_find(primes, exp_seqs, leaves)){

        success(tree);
        fail(tree);

      } else {

        //cap check - see if primes is at its cap!
        if (!cap_check(primes, factor_trees, factors)){ 
          growing = fail(tree);
        }
      }
    }
    expand_sets(leaves, s);
  }
  return;
}


bool exp_find(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs,
              vector<vector<ZZ> >& leaves){

  if (!exp_seqs.empty()){
    int i = 0;
     
    for (auto exps : exp_seqs){
      if (b(primes, exps) < RR(2)){ break; }            
      if (!primitive(primes, exps)) { break; }
      ++i;
    }
    if (i != exp_seqs.size()) {

      exp_seqs = expAlg(primes);
      if (!exp_seqs.empty()){
        leaves.push_back(primes);
        return true;
      }

      return false;
    }
    leaves.push_back(primes);
    return true;
  }

  exp_seqs = expAlg(primes);

  if (!exp_seqs.empty()){
    leaves.push_back(primes);
    return true;
  }

  return false;
}


bool exp_find_noexp(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs, Stats& s){
  if (!exp_seqs.empty()){
    int i = 0;

    for (int i = 0; i < exp_seqs.size(); ++i){
      vector<ZZ>& exps = exp_seqs[i];
      if (b(primes, exps) < RR(2)){ break; }            
      if (!primitive(primes, exps)) { break; }
      ++i;
    }
    if (i != exp_seqs.size()) {

      exp_seqs = expAlg(primes);
      if (!exp_seqs.empty()){
       modify(s, primes, exp_seqs);
       return true;
      }

      return false;
    } else {
      modify(s, primes, exp_seqs);
      return true;
    }
  }

  exp_seqs = expAlg(primes);

  if (!exp_seqs.empty()){
    modify(s, primes, exp_seqs);
    return true;
  }
  return false;
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

void expand(vector<ZZ>& primes, Stats& s){

    vector<vector<ZZ> > exp_seqs;
    
    while (exp_find_noexp(primes, exp_seqs, s)){

      record(s);
      ZZ prev = primes[primes.size() - 1];
      primes.pop_back();
      primes.push_back(NextPrime(prev + ZZ(1)));

    }
  }


void expand_sets(vector<vector <ZZ>>& sets, Stats& s){

  
  #pragma omp parallel for 
  for (int i = 0; i < sets.size(); ++i){
    vector<ZZ> primes = sets[i];
    vector<vector<ZZ> > exp_seqs; 
    expand(primes, s);
  } 
}

void record(Stats& s){

  if (s.number_found % s.freq == ZZ(0)){
  std::ofstream file;
  file.open("stats.txt", std::ios::app);

  file << "Number Found = " << s.number_found << '\n';
  file << "Max product: ";
    for (int i = 0; i < s.max_primes.size(); ++i){
      file << s.max_primes[i] << '^' << s.max_exps[i] << ' ';
    }

  file << "\n\n";
  

  file.close();
  }
  return;
}

ZZ product(vector<ZZ>& primes, vector<ZZ>& exps){

  ZZ product(1);

  for (int i= 0; i < primes.size(); ++i){
    product *= NTL::power(primes[i], NTL::conv<long>(exps[i]));
  }

  return product;
}

void modify(Stats& s, vector<ZZ>& primes, vector<vector<ZZ> >& exp_seqs){

  s.number_found += exp_seqs.size();
  
  for (auto& exps : exp_seqs){

    if (product(primes, exps) > s.product){
      s.max_primes = primes;
      s.max_exps = exps;
      s.product = product(primes, exps);
    }

  }

}
