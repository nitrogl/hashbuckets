/*
 * Class uses SHA-X, extending HashAlgorithm
 * 
 * Copyright (C) 2015  Roberto Metere, Glasgow <roberto.metere@strath.ac.uk>
 */

#ifndef HASHALGORITHM_SHA_TEMPLATE
#define HASHALGORITHM_SHA_TEMPLATE
//-----------------------------------------------------------------------------

#include <iostream>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include "hashalgorithm.hpp"
#include "hashflavour.h"
//-----------------------------------------------------------------------------

/**
 * SHA hash algorithm of a generic type.
 * It relies on the correctness of the library CryptoPP.
 */
template <class T> class SHA: public HashAlgorithm<T>
{
private:
  size_t size;                       ///< The hash size in bytes.
  
protected:
  HashFlavour flavour;               ///< The flavour of the hash (it can be SHA1, etc..)
  byte *lastHash;                    ///< Cache the last hash
  CryptoPP::HashTransformation* sha; ///< The hash transformation, in accordance with the flavour
  
  /**
   * Set the flavour of the hash algorithm.
   * @warning This function is meant to be used only once-per-instance.
   * 
   * @param flavour The SHA flavour to set (SHA1, SHA-256, and so forth).
   */
  void setFlavour(HashFlavour flavour) {
    this->flavour = flavour;
    
    switch (this->flavour) {
      case SHA256_FLAVOUR:
        this->sha = new CryptoPP::SHA256();
        this->size = CryptoPP::SHA256::DIGESTSIZE; // bytes
        break;
      
      default:
        std::cerr << "setFlavour(). The given flavour either is not a SHA-compatbile one or is not (yet) implemented." << std::endl;
      case SHA1_FLAVOUR:
        this->sha = new CryptoPP::SHA1();
        this->size = CryptoPP::SHA1::DIGESTSIZE; // bytes
        break;
    }
    
    lastHash = new byte[this->size];
  }
  
public:
  SHA(HashFlavour flavour = SHA1_FLAVOUR) : HashAlgorithm<T>() {
    this->setFlavour(flavour);
  }
  
  /**
   * Get the hash size in bytes.
   * @warning This is the digest size, not the size of its string representation.
   * For example, SHA1 use a size of 20 bytes, but its common string representation makes use of 40 bytes, because the digest uses only 4 bits for the alphanumeric characters.
   */
  size_t hashSize() const {
    return this->size;
  }
};
//-----------------------------------------------------------------------------

#endif // HASHALGORITHM_SHA_TEMPLATE
