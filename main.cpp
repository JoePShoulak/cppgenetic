#include <iostream>

#include "lifeform.h"

class Codebreaker : public Lifeform<char>
{
public:
  Codebreaker(const std::vector<char> &dna) : Lifeform<char>(dna) {};

  float evaluate() override
  {
    return 1;
  }
};

int main(int argc, char **argv)
{
  Codebreaker alice({'a', 'b', 'c'});
  Lifeform<char> bob({'a', 'b', 'c'});

  std::cout << std::endl;
  std::cout << "DNA: " << std::endl;

  for (auto c : alice.dna)
    std::cout << "  " << c << std::endl;

  std::cout << std::endl;
  std::cout << "Evaluation: " << alice.evaluate() << std::endl;

  return 0;
}
