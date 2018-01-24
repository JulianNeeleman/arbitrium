// Copyright 2018 ReSnap b.v. All Rights Reserved.

#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <string>

class Serializable {
  public:
    virtual std::string serialize() const = 0;
};

#endif // SERIALIZABLE_HPP

