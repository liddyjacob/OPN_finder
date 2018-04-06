//primevect: Keeping track of all primes.
#pragma once
#include <cstddef>
#include <vector>
#include <NTL/ZZ.h>

using NTL::ZZ;
using NTL::NextPrime;
using std::vector;
using std::size_t;

const std::size_t MAX_CONTAINER = 10000000;

class Enum_Primes{
public:

  Enum_Primes(ZZ lower = ZZ(0), std::size_t size = MAX_CONTAINER);
  ZZ operator[](std::size_t index);

  ZZ front(){return *container.front();}
  ZZ back(){return *container.back();}

  size_t size(){return container.size();}
  ZZ sum_primes_below(){return sum_below;}


//private:

  void set_sum_below();
  void find_next_prime(std::size_t index);
  vector<ZZ*> container;
  ZZ sum_below;
};

//Get index of next prime
std::size_t next_index(ZZ& lower, Enum_Primes& primes);
//std::size_t index_helper(std::size_t start, std::size_t end);

bool isInRange(ZZ& low_bound, Enum_Primes& plist);
bool isIndexed(Enum_Primes plist, size_t startat);

ZZ primes_between(ZZ& low, ZZ& high, Enum_Primes& primes);
