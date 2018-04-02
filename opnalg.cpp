//This file will house the opn algorithm.
//#include "tree.hpp"
//#include "expalg.hpp"
//#include "tools.hpp"
#include "opnalg.hpp"

#include <algorithm>//std::fill

void OPAN(int d){

  std::vector<Tree> factor_trees;
  Stats s(ZZ(1009));

  for (int factors = 3; factors <= d; ++factors){

    s.number_found = ZZ(0);
    factor_trees.push_back(Tree());
    Tree& tree = factor_trees.back();
      grow(tree, RR(3));

    vector<Node*> leaves;
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
        leaves.push_back(tree.curr);
        success(tree);
        fail(tree);
  
        //std::cout << "Primes size is checked...\n";
      } else {
        //cap check - see if primes is at its cap!
        if (!cap_check(primes, factor_trees, factors)){ 

          growing = fail(tree);
        }
      }
    }
    expand_sets(leaves, s);
  }

//  for (auto& tree : factor_trees){
//    display(tree);
//  }

  return;
}


bool exp_find(vector<ZZ>& primes, 
              vector<vector<ZZ> >& exp_seqs){
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
      return (!exp_seqs.empty());

    } else {

      return true;

    }
  }

  exp_seqs = expAlg(primes);
  return (!exp_seqs.empty());
}


bool cap_check(vector<ZZ>& primes, 
               vector<Tree>& factor_trees, 
               int& factors){

  ZZ truncp = backup(factor_trees.back());
  primes = strip_primes(factor_trees.back());

  if (primes.size() == factors - 1){
    return false;
  }
  ZZ cap = findmax(primes, factor_trees);
  if (truncp <= cap) { 
    grow(factor_trees.back(), conv<RR>(truncp + 1));
    return true;
  }

  return false;
}

void expand(vector<ZZ>& primes, ZZ& num){

    vector<vector<ZZ> > exp_seqs;
    ZZ prev(0);

    vector<vector<ZZ> > last_exps;
    vector<ZZ> good_primes;

    ZZ increment(2);
    ZZ start_prime(0);


    while (exp_find(primes, exp_seqs)){

      bool twomode = false;
      if (last_exps == exp_seqs){ 
        good_primes = primes; 
        start_prime = primes[primes.size() - 1];
        twomode = true;
      }

      while (last_exps == exp_seqs){
  
        primes = good_primes; 

        prev = good_primes[primes.size() - 1];
        ZZ next = NextPrime(prev + increment);
        good_primes.pop_back();
        good_primes.push_back(next);

        increment*= ZZ(2);
        last_exps = exp_seqs;
        exp_find(good_primes, exp_seqs);
      }

      if (twomode){
        
        num += last_exps.size() 
          * primes_between(start_prime, primes[primes.size() - 1]);
        num += last_exps.size();
        twomode = false;
        //modify(s, primes, last_exps);
      } else {
        num += exp_seqs.size();
        //modify(s, primes, exp_seqs); // < Should be last_exps
      }

      increment = ZZ(2);
      //record(s); 
 
      prev = primes[primes.size() - 1];
      ZZ next = NextPrime(prev + ZZ(1));
      primes.pop_back();
      primes.push_back(next);

      last_exps = exp_seqs;
    }

    primes.pop_back();
    primes.push_back(prev);

}


void expand_sets(vector<Node*>& sets, Stats& s){


  vector<ZZ> nums(sets.size());
  std::fill(nums.begin(), nums.end(), ZZ(0));  
  
  #pragma omp parallel for 
  for (int i = 0; i < sets.size(); ++i){
    vector<ZZ> primes;
    strip_helper(sets[i], primes);// = sets[i];
    vector<vector<ZZ> > exp_seqs; 
    expand(primes, nums[i]);
    record_branch(primes, nums[i]);
    set_max(sets[i], primes.back());
  }

  for(auto& n : nums){
    s.number_found+= n;
  }

  record(s, true);
}


void record_branch(vector<ZZ>& primes, ZZ& num_found){
  std::ofstream file;
  file.open("stats.txt", std::ios::app);

  file << "\tPrimes: ";
  for (int i = 0; i < primes.size(); ++i){
      file << primes[i] << ',';
  }
  file << '\n' << "\tNumber Found: " << num_found << "\n\n";

  file.close();
}


void record(Stats& s, bool endflag){

  #pragma omp flush(s)
  if (s.number_found % s.freq == ZZ(0) || endflag){
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

ZZ primes_between(ZZ& lower, ZZ& upper){

  if (lower == ZZ(0)) { return ZZ(0); }

  ZZ prime = lower;//NextPrime(lower + ZZ(1));
  ZZ num(0);

  while (prime < upper){
    ++num;
    prime = NextPrime(prime + (ZZ(1)));
  }
  
  return num;
}

ZZ product(vector<ZZ>& primes, vector<ZZ>& exps){

  ZZ product(1);

  for (int i= 0; i < primes.size(); ++i){
    product *= NTL::power(primes[i], NTL::conv<long>(exps[i]));
  }

  return product;
}

void modify(Stats& s, vector<ZZ>& primes, vector<vector<ZZ> >& exp_seqs){
/*  std::cout << "OPNs:";

  for (auto exp : exp_seqs){
    std::cout << "\n\t";  

    for (int i = 0; i < exp.size(); ++i){
      std::cout << primes[i] << "^" << exp[i] << ' ';
    }
  }
  std::cout << '\n';
*/
  
  #pragma omp flush(s)
  s.number_found += exp_seqs.size();
  
  for (auto& exps : exp_seqs){

    if (product(primes, exps) > s.product){
      s.max_primes = primes;
      s.max_exps = exps;
      s.product = product(primes, exps);
    }

  }

}
