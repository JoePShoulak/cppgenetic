#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>
#include <limits>

using namespace std;

template <typename T>
class Lifeform
{
public:
  vector<T> dna;

  Lifeform<T>(const vector<T> &dna) : dna(dna){};

  // score the lifeform
  virtual float fitness()
  {
    return -numeric_limits<float>::max();
  }

  // combine the DNA in some way
  virtual Lifeform breed(const Lifeform &partner)
  {
    return Lifeform(dna);
  }

  // do something to DNA
  virtual void mutate() {}
};

#endif
