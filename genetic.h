#ifndef GENETIC_H
#define GENETIC_H

#include <vector>
#include <cmath>
#include <iostream>

// TODO: @todos aren't showing up in the TODO tree extension

/**
 * @interface Lifeform
 * @brief Template class for use as members of the Genetic Class
 * @note One must make a child class of this with definitions for the methods so it can function.
 */
template <typename T>
class Lifeform
{
public:
  /// @brief The genome to be refined into the solution for the algorithm.
  std::vector<T> genome;

  /**
   * @brief Default Lifeform constructor.
   */
  Lifeform(const std::vector<T> &genome) : genome(genome) {};

  /**
   * @todo possibly validate: fitness cannot be negative.
   * @brief Null default method for evaluating fitness
   * @note Must be overridden in child class
   * @return A number representing fitness, where greater means more fit.
   */
  virtual float fitness() = 0;

  /**
   * @brief Null default method for combining genomes into new Lifeforms
   * @param partner The partner to breed with.
   * @note Must be overridden in child class
   * @return A new Lifeform with a genome derived from its parents' genomes
   */
  virtual Lifeform *breed(const Lifeform &partner) const = 0;

  /**
   * @brief Null default method for introducting variation in a genome
   * @note Must be overridden in child class
   */
  virtual void mutate() = 0;
};

/**
 * @todo Restrict to Lifeforms only.
 * @todo Make max an enum?
 * @brief A class for managing the Genetic Algorithm and Populations of Lifeforms
 */
template <typename T>
class Genetic
{
  T bestMember;
  float totalFitness = 0;
  int genCount = 1;
  bool max;

  int popLimit;       // popLimit must be 2+
  float mutationRate; // mutationRate should be >0 (0 means no mutation)

  /**
   * Cannot be negative
   * 0 means no bias (everyone chosen evenly)
   * 1 results in a basic weighted sum
   * (0, 1) results in a smaller bias (for fitnesses >1, inverted otherwise)
   * (1, inf) results in a larger bias (for fitnesses >1, inverted otherwise)
   */
  float bias = 1;

  std::vector<T> population;

  /**
   * @brief Select a member with bias for fitness from the population
   * @return A member of the population, chosen with bias for fitness
   */
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

  /**
   * @todo Not sure how this works with negatives or mins
   * @brief Returns fitness but with a selection bias
   * @param member The lifeform to get the biased fitness of.
   * @return The biased fitness of a given member
   */
  float biasedFitness(T member)
  {
    int sign = 1;
    float f = member.fitness();

    if (f < 0)
    {
      f *= -1;
      sign *= -1;
    }

    float r = sign * pow(f, bias);

    return max ? r : 1 / r; // If we're minning we need to invert r to pick the best ones
  }

public:
  /**
   * @todo validate some of these numbers? They should all be either positive or non-neg
   * @todo max=false doesn't really work
   * @brief Constructor for the Genetic class
   * @param popLimit The population limit.
   * @param mutationRate The rate of mutation.
   * @param bias The mutation bias.
   * @param max If true, select for max fitness. Otherwise select for min fitness.
   */
  Genetic(int popLimit,
          float mutationRate,
          float bias = 1,
          bool max = true) : popLimit(popLimit),
                             mutationRate(mutationRate),
                             bias(bias),
                             max(max) {};

  /**
   * @brief Accessor for genCount
   * @return The current generation index of the simulation
   */
  int getGenCount()
  {
    return genCount;
  }

  /**
   * @brief Initialize the population, verbose flag for output
   * @param verbose If true, print verbose information.
   * @return The current generation index of the simulation
   */
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

  /**
   * @brief Create the next generation by progenation and mutation
   * @param verbose If true, print verbose information.
   */
  void iterate(bool verbose = false)
  {
    // Progenate
    std::vector<T> newPopulation = {};

    while (newPopulation.size() < popLimit)
    {
      auto parentA = selectMember();
      auto parentB = selectMember();
      auto child = parentA.breed(parentB);

      newPopulation.push_back(*child);

      delete child;
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
      else if (max && population[i].fitness() > bestMember.fitness())
        bestMember = population[i];
      else if (!max && population[i].fitness() < bestMember.fitness())
        bestMember = population[i];
    }

    // Cleanup
    genCount++;

    if (verbose)
      display();
  }

  /**
   * @brief Call iterate() until our bestMember has a fitness at or above our goal
   * @param fitnessGoal The goal to reach.
   * @param verbose If true, print verbose information.
   */
  void iterateUntil(float fitnessGoal, bool verbose = false)
  {
    while (max ? bestMember.fitness() < fitnessGoal : bestMember.fitness() > fitnessGoal)
      iterate(verbose);
  }

  /**
   * @brief Display a summary of the current generation
   */
  std::string display()
  {
    // TODO: Should this return a string instead of output,
    // and leave the obligation of displaying to the user?

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
