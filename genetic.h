#ifndef GENETIC_H
#define GENETIC_H

#include <vector>

using namespace std;

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

#endif