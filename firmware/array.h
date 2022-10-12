#pragma once

template<class T, unsigned int N>
class Array {

  T arr[N];

public:

  T& at(unsigned int index) {
    assert(index < N);
    return arr[index];
  }

  const T& at(unsigned int index) const {
    assert(index < N);
    return arr[index];
  }
};