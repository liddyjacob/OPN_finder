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

#ifndef MAX
void expand(vector<ZZ>& primes, ZZ& num, Enum_Primes& list){

    vector<vector<ZZ> > exp_seqs;
    ZZ prev(0);
    vector<vector<ZZ> > last_exps;
    vector<ZZ> new_primes;
    ZZ increment(2);
    ZZ start_prime(0);
    //size_t pindex(0);
    //bool inrange = isInRange(primes.back(), list);
    //if (inrange) {pindex = next_index(primes.back(), list);}

    while (exp_find(primes, exp_seqs)){

      bool twomode = false;
      if (last_exps == exp_seqs){ 
        new_primes = primes; 
        start_prime = primes[primes.size() - 1];
        twomode = true;
      }

      while (last_exps == exp_seqs){
  
        primes = new_primes; 

        prev = new_primes[primes.size() - 1];
        ZZ next = NextPrime(prev + increment);
        new_primes.pop_back();
        new_primes.push_back(next);

        increment*= ZZ(2);
        last_exps = exp_seqs;
        exp_find(new_primes, exp_seqs);

      }

      if (twomode){
        
        num += last_exps.size() 
          * primes_between(start_prime, primes[primes.size() - 1], list);
        num += last_exps.size();
        twomode = false;
        //if (isInRange(primes.back(), list)){
        //  pindex = next_index(primes[primes.size() - 1], list);
        //}
        //modify(s, primes, last_exps);
      } else {
        num += exp_seqs.size();
        //modify(s, primes, exp_seqs); // < Should be last_exps
      }

      //record(s); 

      increment = ZZ(2); 

      prev = primes[primes.size() - 1];
      ZZ next = NextPrime(prev + ZZ(1));

      primes.pop_back();
      primes.push_back(next);
 
      last_exps = exp_seqs;
    }
    primes.pop_back();
    primes.push_back(prev);
}
#endif
ZZ product(vector<ZZ>& primes, vector<ZZ>& exps){
  //assert(primes.size() == exps.size());
  ZZ product(1);
  for (int i= 0; i < primes.size(); ++i){
    product *= NTL::power(primes[i], NTL::conv<long>(exps[i]));
  }
  return product;
}

#ifdef MAX
void expand_max(vector<ZZ>& primes, vector<ZZ>& maxprimes, vector<ZZ>& maxexps){

    vector<vector<ZZ> > exp_seqs;
    ZZ prev(0), next(0), bad(0); // previous next prime
    vector<vector<ZZ> > last_exps;
    vector<ZZ> new_primes;
    ZZ increment(2);
    //ZZ start_prime(0);
    ZZ maxproduct(0);

    while (exp_find(primes, exp_seqs)){

      bool twomode = false;
      if (last_exps == exp_seqs){ 
        new_primes = primes; 
        //start_prime = primes[primes.size() - 1];
        twomode = true;

        while (increment >= ZZ(2)){//(last_exps == exp_seqs){        
          new_primes = primes;
          last_exps = exp_seqs;

          prev = primes[primes.size() - 1];
          next = NextPrime(prev + increment);
          new_primes.pop_back();
          new_primes.push_back(next);
        
          exp_find(new_primes, exp_seqs);

          if (bad == next){
              break;
          }

          if (last_exps == exp_seqs){
            //std::cout << "THE SAME---------------!\n";
            increment *= ZZ(2);
            primes = new_primes; // Move on to new primes
            exp_seqs;
          } else {
            //std::cout << "Not the same\n"; 
            increment /= ZZ(4);
            bad = next;
            exp_seqs = last_exps;
          }
        
        }
      }

      increment = ZZ(2); 

      for (auto& exps : exp_seqs){ 
        if (maxproduct < product(primes, exps)){
          maxproduct = product(primes, exps);
          maxprimes = primes;
          maxexps = exps;
        }
      }

      prev = primes[primes.size() - 1];
      next = NextPrime(prev + ZZ(1));

      primes.pop_back();
      primes.push_back(next);
 
      last_exps = exp_seqs;
    }

    primes.pop_back();
    primes.push_back(prev);
}

#endif


void expand_sets(vector<Node*>& sets, Stats& s){

  ZZ lower(2);
  std::size_t size = 10000;
  if (sets.size() >= 10000){size == MAX_CONTAINER;}
  Enum_Primes list(lower, size);

  #ifndef MAX
  vector<ZZ> nums(sets.size());
  std::fill(nums.begin(), nums.end(), ZZ(0));  
  #endif
  #ifdef MAX
  vector<ZZ> dummyprimes;
  strip_helper(sets[0], dummyprimes);
  size_t primesize = dummyprimes.size();  
  vector<ZZ> dvector(primesize);
    std::fill(dvector.begin(), dvector.end(), ZZ(0));
  vector<vector<ZZ>> max_primes(sets.size());
  std::fill(max_primes.begin(), max_primes.end(), dvector);
  vector<vector<ZZ>> max_exps(sets.size());
  std::fill(max_exps.begin(), max_exps.end(), dvector); 
  #endif


  #pragma omp parallel for 
  for (int i = 0; i < sets.size(); ++i){
    vector<ZZ> primes;
    strip_helper(sets[i], primes);// = sets[i];
    vector<vector<ZZ> > exp_seqs; 
    #ifndef MAX
    expand(primes, nums[i], list);
    record_branch(primes, nums[i]);
    #endif
    #ifdef MAX
    expand_max(primes, max_primes[i], max_exps[i]);
    record_max(max_primes[i], max_exps[i]);
    #endif
    set_max(sets[i], primes.back());
  }
  std::cout << "finished loop\n";

  #ifndef MAX
  for(auto& n : nums){
    s.number_found+= n;
  }

  #endif
  #ifdef MAX
  ZZ maxproduct(0);
  size_t maxindex = -1;
  for (size_t i = 0; i < max_primes.size(); ++i){
    if (product(max_primes[i], max_exps[i]) > maxproduct){
      maxproduct = product(max_primes[i], max_exps[i]);
      maxindex = i;
    }
  }
  s.max_primes = max_primes[maxindex];
  s.max_exps = max_exps[maxindex];
  #endif
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

void record_max(vector<ZZ>& primes, vector<ZZ>& exps){
  std::ofstream file;
  file.open("maxes.txt", std::ios::app);

  file << "\tMax: ";
  for (int i = 0; i < primes.size(); ++i){
      file << primes[i] << '^' << exps[i] << ' ';
  }
  file << '\n';
  file.close();
}



void record(Stats& s, bool endflag){

  #pragma omp flush(s)
  if (s.number_found % s.freq == ZZ(0) || endflag){
  std::ofstream file;
  #ifndef MAX
  file.open("stats.txt", std::ios::app);
  #endif
  #ifdef MAX
  file.open("maxes.txt", std::ios::app);
  #endif

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
  if (upper - lower > ZZ(1000)){

  ZZ prime = lower;//NextPrime(lower + ZZ(1));
  ZZ num(0);

  while (prime < upper){
    ++num;
    prime = NextPrime(prime + (ZZ(2)));
  }

  return num;

  } else {
    //Approximate
    RR pbeforeu = conv<RR>(upper) / NTL::log(conv<RR>(upper));
    RR pbeforel = conv<RR>(lower) / NTL::log(conv<RR>(lower));
    RR diff = pbeforeu - pbeforel;
    return conv<ZZ>(diff);
  
  }
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
  
//  #pragma omp flush(s)
  s.number_found += exp_seqs.size();
  
  for (auto& exps : exp_seqs){

    if (product(primes, exps) > s.product){
      s.max_primes = primes;
      s.max_exps = exps;
      s.product = product(primes, exps);
    }

  }

}
