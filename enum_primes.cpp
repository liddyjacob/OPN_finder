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
std::size_t next_index(ZZ lower, Enum_Primes primes){

  return 0;
}

std::size_t index_helper(std::size_t start, std::size_t end){
  return 0;
}


bool isInRange(Enum_Primes plist, ZZ low_bound){

  return (  ( low_bound > plist.front() ) 
         && (low_bound < plist.back()));

}
bool isIndexed(Enum_Primes plist, size_t startat){

  return  (startat < MAX_CONTAINER);

 return true;
}
