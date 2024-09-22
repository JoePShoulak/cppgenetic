#include "../genetic.h"

// ===== SETTINGS AND PRE-DEFINITIONS =====
#define POPULATION 1000
#define MUTATION_RATE 1.0 / POPULATION
#define BIAS 1

std::string genePool = "abcdefghijklmnopqrstuvwxyz"; // All possible genes
std::string solution = "zach";                       // The word we're searching for
int genomeLength = solution.size();                  // Genome length must be solution length

// ====== MINOR HELPER FUNCTIONS ======
// A method for getting one random gene from the gene pool
char randomGene()
{
  return genePool[rand() % genePool.length()];
}

// A method for constructing an entire random set of genes
std::vector<char> randomGenome()
{
  std::vector<char> genome;

  while (genome.size() < genomeLength)
    genome.push_back(randomGene());

  return genome;
}

// ====== LIFEFORM SUBCLASS DEFINITION ======
class Wordsearcher : public Lifeform<char>
{
public:
  // Default constructor for the initial population will be random genome
  Wordsearcher() : Lifeform<char>({randomGenome()}) {};
  // We must be able to create a new Wordsearcher by giving it a specific genome
  Wordsearcher(const std::vector<char> &genome) : Lifeform<char>(genome) {};

  // We calculate the fitness by counting the correct letters in correct positions
  float fitness() override
  {
    float score = 0;

    for (int i = 0; i < genome.size(); i++)
      if (genome[i] == solution[i])
        score++;

    return score / genome.size();
  }

  // Upon mutation, one gene gets replaced with a random gene
  void mutate() override
  {
    genome[rand() % genome.size()] = randomGene();
  }

  // Breeding will randomly choose between which parent to take from for each gene
  Wordsearcher *breed(const Lifeform &partner) const override
  {
    std::vector<char> newgenome;

    for (int i = 0; i < genome.size(); i++)
      newgenome.push_back((rand() % 2 == 0 ? genome : partner.genome)[i]);

    return new Wordsearcher(newgenome);
  }
};

// ====== MAIN FUNCTION ======
int main(int argc, char **argv)
{
  std::cout << std::endl; // Throw a newline to be nice
  srand(time(0));         // Seed our RNG

  // Make our genetic class given our custom Lifeform specifications and
  Genetic<Wordsearcher> genetic(POPULATION, MUTATION_RATE, BIAS);

  genetic.begin(true);           // Initialize the first generation, true for verbose
  genetic.iterateUntil(1, true); // Run until we reach out fitness goal, true for verbose

  int guesses = POPULATION * genetic.getGenCount();
  double bruteExpectation = pow(genePool.length(), genomeLength);
  float percent = guesses / bruteExpectation * 100;

  // Summarize our results
  std::cout << "Completed in " << guesses << " guesses, "
            << "compared to the brute force expected " << bruteExpectation << " guesses "
            << "(" << percent << "% of the expected guesses)."
            << std::endl
            << std::endl;

  return 0;
}
