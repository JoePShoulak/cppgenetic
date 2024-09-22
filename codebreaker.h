#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <vector>
#include <iostream>

#include "genetic.h"

using namespace std;

vector<char> solution({'j', 'o', 'e'});

char randomLetter()
{
  return "abcdefghijklmnopqrstuvwxyz"[rand() % 26];
}

class Wordsearcher : public Lifeform<char>
{
public:
  Wordsearcher(const vector<char> &dna) : Lifeform<char>(dna) {};
  Wordsearcher() : Lifeform<char>({randomLetter(),
                                   randomLetter(),
                                   randomLetter()}) {};

  float fitness() override
  {
    float score = 0;

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

  Wordsearcher breed(const Wordsearcher &partner)
  {
    vector<char> newDna;

    for (int i = 0; i < dna.size(); i++)
      newDna.push_back((rand() % 2 == 0 ? dna : partner.dna)[i]);

    return Wordsearcher(newDna);
  }
};

#endif
