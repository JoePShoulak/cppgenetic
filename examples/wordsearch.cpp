#include "../genetic.h"

// ===== SETTINGS AND PRE-DEFINITIONS =====
#define POPULATION 1000
#define MUTATION_RATE 1.0 / POPULATION
#define BIAS 1

std::string genePool = "abcdefghijklmnopqrstuvwxyz"; // All possible genes
std::string solution = "genetic";                    // The word we're searching for
int dnaLength = solution.size();                     // DNA length must be solution length

// ====== MINOR HELPER FUNCTIONS ======
// A method for getting one random member of the gene pool
char randomGene()
{
  return genePool[rand() % genePool.length()];
}

// A method for constructing an entire random set of genes
std::vector<char> randomDNA()
{
  std::vector<char> dna;

  while (dna.size() < dnaLength)
    dna.push_back(randomGene());

  return dna;
}

// ====== LIFEFORM SUBCLASS DEFINITION ======
class Wordsearcher : public Lifeform<char>
{
public:
  // Default constructor for the initial population will be random DNA
  Wordsearcher() : Lifeform<char>({randomDNA()}) {};
  // We must be able to create a new Wordsearcher by giving it a specific DNA
  Wordsearcher(const std::vector<char> &dna) : Lifeform<char>(dna) {};

  // We calculate the fitness by counting the correct letters in correct positions
  float fitness() override
  {
    float score = 0;

    for (int i = 0; i < dna.size(); i++)
      if (dna[i] == solution[i])
        score++;

    return score / dna.size();
  }

  // Upon mutation, one gene gets replaced with a random gene
  void mutate() override
  {
    dna[rand() % dna.size()] = randomGene();
  }

  // Breeding will randomly choose between which parent to take from for each gene
  Wordsearcher breed(const Wordsearcher &partner)
  {
    std::vector<char> newDna;

    for (int i = 0; i < dna.size(); i++)
      newDna.push_back((rand() % 2 == 0 ? dna : partner.dna)[i]);

    return Wordsearcher(newDna);
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
  double bruteExpectation = pow(26, dnaLength);
  float percent = guesses / bruteExpectation * 100;

  // Summarize our results
  std::cout << "Completed in " << guesses << " guesses, "
            << "compared to the brute force expected " << bruteExpectation << " guesses "
            << "(" << percent << "% of the expected guesses)."
            << std::endl
            << std::endl;

  return 0;
}
