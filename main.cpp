#include <iostream>

#include "codebreaker.h"

using namespace std;

int main(int argc, char **argv)
{
  Codebreaker alice({'c', 'b', 'a'});
  Codebreaker bob({'f', 'e', 'd'});

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

  return 0;
}
