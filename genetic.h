#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <limits>
#include <cmath>
#include <iostream>

// ===== LIFEFORM TEMPLATE CLASS =====
// One must make a child class of this with definitions for the methods so it can function.
template <typename T>
class Lifeform
{
public:
  std::vector<T> dna;

  Lifeform<T>(const std::vector<T> &dna) : dna(dna){};

  // score the lifeform
  virtual float fitness()
  {
    return -std::numeric_limits<float>::max();
  }

  // combine the DNA in some way
  virtual Lifeform breed(const Lifeform &partner)
  {
    return Lifeform(dna);
  }

  // do something to DNA
  virtual void mutate() {}
};

// ===== GENETIC CLASS =====
// TODO: Restrict to Lifeforms only
template <typename T>
class Genetic
{
  T bestMember;
  int popLimit;
  float mutationRate;
  int genCount = 1;
  float bias = 1; // 0 means no bias (everyone chosen evenly)
                  // 1 results in a basic weighted sum
                  // (0, 1) results in a smaller bias (for fitnesses >1, inverted otherwise)
                  // (1, inf) results in a larger bias (for fitnesses >1, inverted otherwise)

  std::vector<T> population;

  // Select a member with bias for fitness from the population
  T selectMember()
  {
    float totalFitness;

    for (T m : population)
      totalFitness += pow(m.fitness(), bias);

    int i = 0;
    // totalFitness could be 0, so we have to max with 1 to avoid % 0
    // randomNum % N>0 could be 0, which would return an invalid member, so max with 1 again
    int randomNum = std::max(rand() % std::max(int(totalFitness), 1), 1);

    while (randomNum > 0)
      randomNum -= population[i++].fitness();

    return population[i - 1];
  }

public:
  // TODO: validate some of these numbers? They should all be either positive or non-neg
  Genetic(int popLimit, float mutationRate, float bias = 1) : popLimit(popLimit),
                                                              mutationRate(mutationRate),
                                                              bias(bias) {};

  // Accessor because this should technically be private
  int getGenCount()
  {
    return genCount;
  }

  // Initialize the population, verbose flag for output
  void begin(bool verbose = false)
  {
    while (population.size() < popLimit)
      population.push_back(T());

    if (verbose)
      display();
  }

  // Create the next generation by progenation and mutation
  void iterate(bool verbose = false)
  {
    // Progenate
    std::vector<T> newPopulation = {};

    while (newPopulation.size() < popLimit)
    {
      auto parentA = selectMember();
      auto parentB = selectMember();
      auto child = parentA.breed(parentB);

      newPopulation.push_back(child);
    }

    population = newPopulation;

    for (int i = 0; i < population.size(); i++)
    {
      // Mutate
      if (rand() % 100 / 100 < mutationRate)
        population[i].mutate();

      // Find the best member while we're looping over everything
      if (i == 0)
        bestMember = population[i];
      else if (population[i].fitness() > bestMember.fitness())
        bestMember = population[i];
    }

    // Cleanup
    genCount++;

    if (verbose)
      display();
  }

  // Call iterate() until our bestMember has a fitness at or above our goal
  void iterateUntil(float fitnessGoal, bool verbose = false)
  {
    while (bestMember.fitness() < fitnessGoal)
      iterate(verbose);
  }

  // Display a summary of the current generation
  void display()
  {
    std::cout << "Gen count: " << genCount << std::endl;
    std::cout << "Pop size: " << population.size() << std::endl;
    std::cout << "Best fitness: " << bestMember.fitness() << std::endl;
    std::cout << "Best DNA: ";
    for (auto k : bestMember.dna)
      std::cout << k;

    std::cout << std::endl
              << std::endl;
  }
};

#endif
