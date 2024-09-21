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

  void mutate() override
  {
    char swap = dna[0];

    for (int i = 0; i < dna.size() - 1; i++)
    {
      dna[i] = dna[i + 1];
    }

    dna[dna.size() - 1] = swap;
  }

  Codebreaker breed(const Codebreaker &partner)
  {
    std::vector<char> newDna;

    for (int i = 0; i < dna.size(); i++)
    {
      newDna.push_back((rand() % 2 == 0 ? dna : partner.dna)[i]);
    }

    return Codebreaker(newDna);
  }
};

int main(int argc, char **argv)
{
  Codebreaker alice({'a', 'b', 'c'});
  Codebreaker bob({'d', 'e', 'f'});

  std::cout << std::endl;
  std::cout << "DNA: " << std::endl;

  for (auto c : alice.dna)
    std::cout << "  " << c << std::endl;

  std::cout << std::endl;
  std::cout << "Evaluation: " << alice.evaluate() << std::endl;

  std::cout << "Breeding!" << std::endl;
  auto charlie = alice.breed(bob);

  std::cout << std::endl;
  std::cout << "DNA: " << std::endl;

  for (auto c : charlie.dna)
    std::cout << "  " << c << std::endl;

  return 0;
}
