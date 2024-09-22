#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <cmath>
#include <iostream>

// ===== LIFEFORM TEMPLATE CLASS =====
// One must make a child class of this with definitions for the methods so it can function.
template <typename T>
class Lifeform
{
public:
  std::vector<T> genome;

  Lifeform<T>(const std::vector<T> &genome) : genome(genome){};

  // score the lifeform
  // TODO: possibly validate: fitness cannot be negative
  virtual float fitness()
  {
    return 0;
  }

  // combine the genome in some way
  virtual Lifeform breed(const Lifeform &partner)
  {
    return Lifeform(genome);
  }

  // do something to genome
  virtual void mutate() {}
};

// ===== GENETIC CLASS =====
// TODO: Restrict to Lifeforms only
template <typename T>
class Genetic
{
  T bestMember;
  float totalFitness = 0;
  int genCount = 1;
  int popLimit;       // popLimit must be 2+
  float mutationRate; // mutationRate should be >0 (0 means no mutation)
  float bias = 1;     /* BIAS
                        Cannot be negative
                        0 means no bias (everyone chosen evenly)
                        1 results in a basic weighted sum
                        (0, 1) results in a smaller bias (for fitnesses >1, inverted otherwise)
                        (1, inf) results in a larger bias (for fitnesses >1, inverted otherwise)
                      */

  std::vector<T> population;

  // Select a member with bias for fitness from the population
  T selectMember()
  {
    // totalFitness could be 0, so we have to max with 1 to avoid % 0
    // randomNum % N>0 could be 0, which would return an invalid member, so max with 1 again
    int randomNum = std::max(rand() % std::max(int(totalFitness), 1), 1);
    int i = 0;

    while (randomNum > 0)
      randomNum -= biasedFitness(population[i++]);

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

  // Returns fitness but with a selection bias
  float biasedFitness(T member)
  {
    return pow(member.fitness(), bias);
  }

  // Initialize the population, verbose flag for output
  void begin(bool verbose = false)
  {
    while (population.size() < popLimit)
    {
      T newMember;
      totalFitness += newMember.fitness();
      population.push_back(newMember);
    }

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
    totalFitness = 0;

    for (int i = 0; i < population.size(); i++)
    {
      // Mutate
      if (rand() % 100 / 100 < mutationRate)
        population[i].mutate();

      // Find the best member and total fitness while we're looping over everything
      totalFitness += biasedFitness(population[i]);

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
    std::cout << "Best genome: ";
    for (auto k : bestMember.genome)
      std::cout << k;

    std::cout << std::endl
              << std::endl;
  }
};

#endif
