#include <omp.h>
#include "list.hpp"
#include "opnalg.hpp"
#include "enum_primes.hpp"
#define TEST;

int main(){
  
//  if isQuick(low_bound, prime_list);
//  if isQuick(index, prime_list);

//  ZZ prime = QuickNext(prime_list, index, lowbound);
//  ZZ primes_between = QuickPi(prime_list, index, lowbound) - QuickPi(   

//  Enum_Primes prime_list(ZZ(21), 1000000);
/*
  std::cout << "Primes below: " << prime_list.sum_primes_below() << '\n';

  std::cout << "100000000 is not indexable, correct? " 
            << ! isIndexed(prime_list, 1000000000) << '\n';

  ZZ lower(503);
  size_t ni = next_index(lower, prime_list);
  
  std::cout << "Index after 503: " << ni << '\n' << "Prime after 503: " 
            << prime_list[ni] << '\n';

  std::cout << "calculating primes between 500000 and 1000000\n";
  ZZ st(5000000), f(10000000);
  std::cout << "num Prime: " << 
    primes_between(st, f, prime_list) << '\n';
*/
//  if isQuick(low_bound, prime_list);
//  if isQuick(index, prime_list);

/* 
  for(auto p : prime_list.container){
    std::cout << *p << ' ';
  }
  std::cout << '\n';
*/
//  for (int i = 0; i < 10000000000; ++i){}

  OPAN(5);
//  test_list();
/*
  vector<ZZ> primes;
    primes.push_back(ZZ(3));
    primes.push_back(ZZ(5));
    primes.push_back(ZZ(17));
//    primes.push_back(ZZ(181));
//    primes.push_back(ZZ(181001));
//    primes.push_back(ZZ(32760999911));
//    primes.push_back(ZZ(11));
//    primes.push_back(ZZ(13));

  vector<vector<ZZ>> exp_seqs =  expAlg(primes);
  for (auto exp : exp_seqs){

    for (auto e : exp){
      std::cout << e << " ";
    }
    std::cout << '\n';
  }
*/



  return 0;

}
