#include <stdio.h>
#include <iostream>

using namespace std;

int main() {
	int t, n;
	cin >> t;
	for(int i = 0; i < t; i++)
	{
	    cin >> n;
      if(__builtin_popcount(n) == 1)
        cout << "YES";
      else
          cout << "NO";

	}
	return 0;
}
