#include <vector>
#include <iostream>

#include "../genetic.h"

using namespace std;

string solution = "genetic";
int dnaLength = solution.size();

char randomLetter()
{
  return "abcdefghijklmnopqrstuvwxyz"[rand() % 26];
}

vector<char> randomDNA()
{
  vector<char> dna;

  while (dna.size() < dnaLength)
    dna.push_back(randomLetter());

  return dna;
}

class Wordsearcher : public Lifeform<char>
{
public:
  Wordsearcher(const vector<char> &dna) : Lifeform<char>(dna) {};
  Wordsearcher() : Lifeform<char>({randomDNA()}) {};

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

int main(int argc, char **argv)
{
  cout << endl;
  srand(time(0));

  Genetic<Wordsearcher> genetic(100, 0.01);

  genetic.begin(true);

  while (genetic.bestMember().fitness() < 1)
    genetic.iterate(true);

  cout << "Best DNA: ";
  for (auto c : genetic.bestMember().dna)
    cout << c;

  cout << endl
       << endl;

  return 0;
}