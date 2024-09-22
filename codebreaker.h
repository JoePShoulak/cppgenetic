#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <vector>
#include <iostream>

#include "genetic.h"

using namespace std;

char randomLetter()
{
  return "abcdefghijklmnopqrstuvwxyz"[rand() % 26];
}

class Codebreaker : public Lifeform<char>
{
public:
  Codebreaker(const vector<char> &dna) : Lifeform<char>(dna) {};
  Codebreaker() : Lifeform<char>({randomLetter(),
                                  randomLetter(),
                                  randomLetter()}) {};

  float fitness() override
  {
    float score = 0;
    vector<char> solution({'j', 'o', 'e'});

    for (int i = 0; i < dna.size(); i++)
    {
      if (dna[i] == solution[i])
        score++;
    }

    return score / dna.size();
  }

  void mutate() override
  {
    dna[rand() % dna.size()] = randomLetter();
  }

  Codebreaker breed(const Codebreaker &partner)
  {
    vector<char> newDna;

    for (int i = 0; i < dna.size(); i++)
      newDna.push_back((rand() % 2 == 0 ? dna : partner.dna)[i]);

    return Codebreaker(newDna);
  }
};

#endif
