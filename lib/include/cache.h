#ifndef LIB_CACHE_H
#define LIB_CACHE_H

#include <map>

template <class State> class Cache {
  private:
    // Private member variables.
    std::map<State, double> memory_;

  public:
    // Public member functions.
    void add_to_cache(const State &, double);
    std::pair<bool, double> retrieve_from_cache(const State &) const;
};

#include "lib/src/cache.inc"

#endif // LIB_CACHE_H
