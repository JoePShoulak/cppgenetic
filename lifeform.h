#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>

template <typename T>
class Lifeform
{
public:
  std::vector<T> dna;

  Lifeform<T>(const std::vector<T> &dna) : dna(dna){};

  virtual float evaluate()
  {
    // score the lifeform
    return 0;
  }

  virtual Lifeform breed(const Lifeform &partner)
  {
    // combine the DNA in some way
    return Lifeform(dna);
  }

  virtual void mutate()
  {
    // do something to DNA
  }
};

#endif
