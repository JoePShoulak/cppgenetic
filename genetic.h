#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <limits>

using namespace std;

// Genetic class handles the lifeforms and is the iterator class
template <typename T>
class Genetic
{
  int populationLimit;
  float mutationRate;
  int genCount = 0;

  vector<T> population;

public:
  Genetic(int populationLimit, float mutationRate) : populationLimit(populationLimit), mutationRate(mutationRate) {};

  void begin()
  {

    while (population.size() < populationLimit)
    {
      T newMember;
      population.push_back(newMember);
    }
  }

  T selectMember()
  {
    return population[rand() % populationLimit]; // Placeholder
  }

  void progenate()
  {
    vector<T> newPopulation;

    while (newPopulation.size() < populationLimit)
    {
      auto parentA = selectMember();
      auto parentB = selectMember();
      auto child = parentA.breed(parentB);

      newPopulation.push_back(child);
    }

    population = newPopulation;
  }

  void mutate()
  {
    for (T &m : population)
    {
      if (rand() % 100 / 100 < mutationRate)
        m.mutate();
    }
  }

  void iterate()
  {
    progenate();
    mutate();

    genCount++;
  }

  T bestMember()
  {
    T best = population[0];

    for (int i = 1; i < populationLimit; i++)
    {
      if (population[i].fitness() > best.fitness())
        best = population[i];
    }

    return best;
  }

  void display()
  {
    cout << "\nGen Cout: " << genCount << endl;
    cout << "Pop size: " << population.size() << endl;
    cout << "Best fitness: " << bestMember().fitness() << endl;
  }
};

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
    return -numeric_limits<float>::max();
  }

  // combine the DNA in some way
  virtual Lifeform breed(const Lifeform &partner)
  {
    return Lifeform(dna);
  }

  // do something to DNA
  virtual void mutate() {}
};

#endif
