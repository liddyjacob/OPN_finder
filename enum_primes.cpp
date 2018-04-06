//primevect: Keeping track of all primes.
#include "enum_primes.hpp"
//#include <cstddef>
//#include <vector>
//#include <NTL/ZZ.h>
#include <cassert>

using NTL::ZZ;
using NTL::NextPrime;
using std::size_t;

//const size_t MAX_CONTAINER = 10000000;
Enum_Primes::Enum_Primes(ZZ lower, size_t size) {
  sum_below = ZZ(0);

  ZZ* ptr_prime = new ZZ(NextPrime(lower));
  container.push_back(ptr_prime);
  find_next_prime(size);
}

ZZ Enum_Primes::operator[](std::size_t index){
  assert (index < MAX_CONTAINER);
  assert(index >= 0);
  if (index >= container.size()){ find_next_prime(index); }
  return *container[index]; 
} 

void
Enum_Primes::set_sum_below(){
  ZZ prime(2);

  for (ZZ prime(2); prime < *container.front(); 
       prime = NextPrime(prime + ZZ(1))){
    sum_below+=ZZ(1);
  }
}


void
Enum_Primes::find_next_prime(std::size_t index){

  size_t end = container.size() - 1;  
  size_t diff = index - end;
  
  ZZ endprime = *container.back();
  for(diff; diff > 0; --diff){
    endprime = NextPrime(endprime + ZZ(2));
    ZZ* prime_ptr = new ZZ(endprime);
    container.push_back(prime_ptr);
  }

  return;
}

//Get index of next prime
std::size_t next_index(ZZ& lower, Enum_Primes& primes){

  //return index_helper(0, primes.size() - 1);
  size_t start = 0;
  size_t end = primes.size() - 1;

  if (primes.back() <= lower){return primes.size() - 1;}
  if (primes.front() >= lower){return 0;}

  while (start <= end){
    size_t mid = start + (end - start) / 2;

    if (primes[mid] == lower) return mid; 
    if (primes[mid] < lower){ 

      if (lower < primes[mid + 1]) { return mid + 1; }

      if (lower > primes[mid + 1]) { start = mid + 1; }
    } else {
      end = mid - 1;
    }
  }
//    if (primes[mid]
}

/*
std::size_t index_helper(std::size_t start, std::size_t end, primes){

  return 0;
}
*/

bool isInRange(Enum_Primes plist, ZZ low_bound){

  return (  ( low_bound > plist.front() ) 
         && (low_bound < plist.back()));

}

bool isIndexed(Enum_Primes plist, size_t startat){

  return  (startat < MAX_CONTAINER);
  return true;

}
