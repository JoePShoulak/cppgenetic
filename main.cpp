#include <iostream>

#include "codebreaker.h"
#include "genetic.h"

using namespace std;

void testWithoutGenetics()
{
  Codebreaker alice;
  Codebreaker bob;

  alice.summarize("alice");
  bob.summarize("bob");

  cout << "Breeding!\n"
       << endl;

  auto charlie = alice.breed(bob);

  charlie.summarize("charlie");

  cout << "Mutating!\n"
       << endl;

  charlie.mutate();

  charlie.summarize("charlie");
}

void testWithGenetics()
{
  Genetic<Codebreaker> genetic(10, 0.1);

  genetic.begin();
  genetic.display();

  while (genetic.bestMember().fitness() < 1)
  {
    genetic.iterate();
    genetic.display();
  }

  cout << "\nBest result: " << endl;
  for (auto c : genetic.bestMember().dna)
    cout << c << " ";

  cout << "\n"
       << endl;
}

int main(int argc, char **argv)
{
  srand(time(0));

  // testWithoutGenetics();
  testWithGenetics();

  return 0;
}
