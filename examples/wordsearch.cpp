#include <vector>
#include <iostream>
#include <cmath>

#include "../genetic.h"

using namespace std;

// FIXME: Floating point exception (core dumped), for low population
#define POPULATION 1000
#define MUTATION_RATE 0.001
#define BIAS 1

string genePool = "abcdefghijklmnopqrstuvwxyz";
string solution = "genetic";
int dnaLength = solution.size();

char randomGene()
{
  return genePool[rand() % genePool.length()];
}

vector<char> randomDNA()
{
  vector<char> dna;

  while (dna.size() < dnaLength)
    dna.push_back(randomGene());

  return dna;
}

class Wordsearcher : public Lifeform<char>
{
public:
  Wordsearcher() : Lifeform<char>({randomDNA()}) {};
  Wordsearcher(const vector<char> &dna) : Lifeform<char>(dna) {};

  float fitness() override
  {
    float score = 0;

    for (int i = 0; i < dna.size(); i++)
      if (dna[i] == solution[i])
        score++;

    return score / dna.size();
  }

  void mutate() override
  {
    dna[rand() % dna.size()] = randomGene();
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

  Genetic<Wordsearcher> genetic(POPULATION, MUTATION_RATE, BIAS);

  genetic.begin(true);

  while (genetic.bestMember().fitness() < 1)
    genetic.iterate(true);

  int guesses = POPULATION * genetic.getGenCount();
  double bruteExpectation = pow(26, dnaLength);

  cout << "Completed in " << guesses << " guesses, compared to the brute force expected " << bruteExpectation << endl
       << endl;

  return 0;
}
