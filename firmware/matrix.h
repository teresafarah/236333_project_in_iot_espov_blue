#pragma once

#include "array.h"

template<class T, unsigned int N, unsigned int M>
class Matrix {

  Array<Array<T, M>, N> mat;

public:

  // Matrix() = default;

  T& at(unsigned int index_i, unsigned int index_j) {
    return mat.at(index_i).at(index_j);
  }

  const T& at(unsigned int index_i, unsigned int index_j) const {
    return mat.at(index_i).at(index_j);
  }

  Array<T, M>& get_row(unsigned int index_i) {
    return mat.at(index_i);
  }

  const Array<T, M>& get_row(unsigned int index_i) const {
    return mat.at(index_i);
  }
};