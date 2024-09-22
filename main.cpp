#include <iostream>

#include "genetic.h"
#include "codebreaker.h"

using namespace std;

int main(int argc, char **argv)
{
  srand(time(0));

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

  return 0;
}
