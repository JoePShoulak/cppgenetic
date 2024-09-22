#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <limits>
#include <cmath>

using namespace std;

// Lifeform class, used as the members of the genetic class.
// One must make a child class off this with definitions for the methods so it can function.
template <typename T>
class Lifeform
{
public:
  vector<T> dna;

  Lifeform<T>(const vector<T> &dna) : dna(dna){};

  // score the lifeform
  virtual float fitness()
  {
    return -numeric_limits<float>::max(); // This is not the floating point error
  }

  // combine the DNA in some way
  virtual Lifeform breed(const Lifeform &partner)
  {
    return Lifeform(dna);
  }

  // do something to DNA
  virtual void mutate() {}
};

// Genetic class handles the lifeforms and is the iterator class
// TODO: Restrict to Lifeforms only
template <typename T>
// template <typename U, typename T, typename = std::enable_if_t<std::is_base_of<Lifeform<U>, T>::value>>
class Genetic
{
  int populationLimit;
  float mutationRate;
  int genCount = 1;
  float bias = 1; // 0 means no bias (everyone chosen evenly)
                  // 1 results in a basic weighted sum
                  // (0, 1) results in a smaller bias
                  // (1, inf) results in a larger bias

  vector<T> population;

  T selectMember()
  {
    float totalFitness;

    for (T m : population)
      totalFitness += pow(m.fitness(), bias);

    int i = 0;
    int randomNum = max(rand() % max(int(totalFitness), 1), 1);

    while (randomNum > 0)
      randomNum -= population[i++].fitness();

    return population[i - 1];
  }

public:
  Genetic(int populationLimit, float mutationRate, float bias = 1) : populationLimit(populationLimit), mutationRate(mutationRate), bias(bias) {};

  int getGenCount()
  {
    return genCount;
  }

  void begin(bool verbose = false)
  {
    while (population.size() < populationLimit)
    {
      T newMember;
      population.push_back(newMember);
    }

    if (verbose)
      display();
  }

  void iterate(bool verbose = false)
  {
    // Progenate
    cout << "Progenate called" << endl;
    vector<T> newPopulation = {};

    while (newPopulation.size() < populationLimit)
    {
      auto parentA = selectMember();
      auto parentB = selectMember();
      auto child = parentA.breed(parentB);

      newPopulation.push_back(child);
    }

    population = newPopulation;

    // Mutate
    cout << "Mutate called" << endl;
    for (T &m : population)
      if (rand() % 100 / 100 < mutationRate)
        m.mutate();

    // Cleanup
    genCount++;

    if (verbose)
      display();
  }

  T bestMember()
  {
    T best = population[0];

    for (int i = 1; i < populationLimit; i++)
      if (population[i].fitness() > best.fitness())
        best = population[i];

    return best;
  }

  void display()
  {
    cout << "Gen count: " << genCount << endl;
    cout << "Pop size: " << population.size() << endl;
    cout << "Best fitness: " << bestMember().fitness() << endl;
    cout << "Best DNA: ";
    for (auto k : bestMember().dna)
      cout << k;

    cout << "\n"
         << endl;
  }
};

#endif
