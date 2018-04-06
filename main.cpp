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

  Enum_Primes prime_list(ZZ(2), 1000);

  std::cout << "100000000 is not indexable, correct? " 
            << ! isIndexed(prime_list, 1000000000) << '\n';
//  if isQuick(low_bound, prime_list);
//  if isQuick(index, prime_list);

 
  for(auto p : prime_list.container){
    std::cout << *p << ' ';
  }
  std::cout << '\n';
//  for (int i = 0; i < 10000000000; ++i){}

//  ZZ start(54653857), finish(110345023);
//  std::cout << primes_between(start, finish);


//  OPAN(6);
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
