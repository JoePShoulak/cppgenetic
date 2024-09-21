#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <vector>
#include <iostream>

#include "lifeform.h"

class Codebreaker : public Lifeform<char>
{
public:
  Codebreaker(const std::vector<char> &dna) : Lifeform<char>(dna) {};

  float evaluate() override
  {
    float score = 0;

    for (int i = 0; i < dna.size() - 1; i++)
    {
      if (int(dna[i]) < int(dna[i + 1]))
        score++;
    }

    return score / (dna.size() - 1);
  }

  void mutate() override
  {
    char swap = dna[0];

    for (int i = 0; i < dna.size() - 1; i++)
      dna[i] = dna[i + 1];

    dna[dna.size() - 1] = swap;
  }

  Codebreaker breed(const Codebreaker &partner)
  {
    std::vector<char> newDna;
    srand(time(0));

    for (int i = 0; i < dna.size(); i++)
      newDna.push_back((rand() % 2 == 0 ? dna : partner.dna)[i]);

    return Codebreaker(newDna);
  }

  void summarize(std::string name)
  {
    std::cout << "Codebreaker " << name << std::endl;
    std::cout << "  DNA: ";

    for (int i = 0; i < dna.size(); i++)
    {
      std::cout << dna[i];

      if (i != dna.size() - 1)
        std::cout << ", ";
    }

    std::cout << std::endl;

    std::cout << "  SCORE: " << evaluate() << std::endl
              << std::endl;
  }
};

#endif
