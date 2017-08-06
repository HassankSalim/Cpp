#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
  int ans, input;
  string clue = "";
  ans = rand() % 100;
  while(1)
  {
    cout << "Guess the number \n";
    cin >> input;
    if(ans == input)
      {
        cout << "Congrats \n";
        break;
      }
    clue = input > ans ? "Guess too high" : "Guess too low";
    cout << clue << '\n';
  }
  return 0;
}
