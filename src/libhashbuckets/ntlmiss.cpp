/*
 * Some useful functions using NTL.
 * 
 * Copyright (C) 2015  Roberto Metere, Glasgow <roberto.metere@strath.ac.uk>
 */

#include <sstream>
#include "ntlmiss.h"
//-----------------------------------------------------------------------------

namespace NTL {
  ZZ str2zz(const std::string s) {
    ZZ z;
    std::stringstream sstr;
    sstr << s;
    sstr >> z;
    return z;
  }
  //---------------------------------------------------------------------------

  unsigned long log2(const ZZ &z) {
    ZZ one, zl;
    unsigned long l2;
    
    one = str2zz("1");
    zl = z;
    l2 = 0L;
    while (zl > one) {
      zl = zl >> 1;
      l2++;
    }
    return l2;
  }
  //---------------------------------------------------------------------------

  unsigned long bits(const ZZ &z) {
    return log2(z) + 1L;
  }
  //---------------------------------------------------------------------------

  unsigned long bits(const ZZ_p &zp) {
    ZZ z;
    conv(z, zp);
    return log2(z) + 1L;
  }
  //---------------------------------------------------------------------------
  
  void vector2VecZZp(Vec<ZZ_p> &zp, const std::vector<ZZ_p> &v) {
    zp.kill();
    zp.SetLength(v.size());
    for (size_t i = 0; i < v.size(); i++) {
      zp.append(v[i]);
    }
  }
  //---------------------------------------------------------------------------
  
  Vec<ZZ_p> vector2VecZZp(const std::vector<ZZ_p> &v) {
    Vec<ZZ_p> res;
    
    res.SetLength(v.size());
    for (size_t i = 0; i < v.size(); i++) {
      res.append(v[i]);
    }
    
    return res;
  }
  //---------------------------------------------------------------------------

};
