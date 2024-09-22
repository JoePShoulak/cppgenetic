#include <iostream>

#include "genetic.h"
#include "codebreaker.h"

using namespace std;

int main(int argc, char **argv)
{
  cout << endl;
  srand(time(0));

  Genetic<Codebreaker> genetic(100, 0.1);

  genetic.begin(true);

  while (genetic.bestMember().fitness() < 1)
    genetic.iterate(true);

  cout << "Best DNA: ";
  for (auto c : genetic.bestMember().dna)
    cout << c;

  cout << endl
       << endl;

  return 0;
}
