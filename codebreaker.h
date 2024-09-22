#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <vector>
#include <iostream>

#include "lifeform.h"

using namespace std;

class Codebreaker : public Lifeform<char>
{
public:
  Codebreaker(const vector<char> &dna) : Lifeform<char>(dna) {};
  Codebreaker() : Lifeform<char>({"abcdefghijklmnopqrstuvwxyz"[rand() % 26],
                                  "abcdefghijklmnopqrstuvwxyz"[rand() % 26],
                                  "abcdefghijklmnopqrstuvwxyz"[rand() % 26],
                                  "abcdefghijklmnopqrstuvwxyz"[rand() % 26],
                                  "abcdefghijklmnopqrstuvwxyz"[rand() % 26]}) {};

  float fitness() override
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
    vector<char> newDna;

    for (int i = 0; i < dna.size(); i++)
      newDna.push_back((rand() % 2 == 0 ? dna : partner.dna)[i]);

    return Codebreaker(newDna);
  }

  void summarize(string name)
  {
    cout << "Codebreaker " << name << endl;
    cout << "  DNA: ";

    for (int i = 0; i < dna.size(); i++)
    {
      cout << dna[i];

      if (i != dna.size() - 1)
        cout << ", ";
    }

    cout << endl;

    cout << "  SCORE: " << fitness() << endl
         << endl;
  }
};

#endif
