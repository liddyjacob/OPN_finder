#include <omp.h>
#include "list.hpp"
#include "opnalg.hpp"

#define TEST;

int main(){
  #pragma omp paralell
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
