#include <stdio.h>
#include <iostream>
#include <climits>

using namespace std;

/*

Sample Input :
4
-1 10 -2 3 4

Sample Output :
Sum :15
From index 1 to 4

*/

struct custom
{
  int i, j, sum;
};

int main() {
  int arr[100], n, temp_sum, temp;
  custom max_cur, max;
  max_cur.i = 0;
  max_cur.j = 0;
  max.i = 0;
  max.j = 0;
  max_cur.sum = -100;
  max.sum = -100;
  cin >> n;
  for(int i = 0; i < n; i++)
    cin >> arr[i];
  for(int i = 0; i < n; i++)
  {
    temp = arr[i];
    temp_sum = max_cur.sum + temp;
    if(temp > temp_sum)
    {
      max_cur.sum = temp;
      max_cur.i = i;
      max_cur.j = i;
    }
    else
    {
      max_cur.sum = temp_sum;
      max_cur.j = i;
    }
    if(max_cur.sum > max.sum)
    {
      max.sum = max_cur.sum;
      max.i = max_cur.i;
      max.j = max_cur.j;
    }
  }
  cout << "Sum :" << max.sum << " \nFrom index " << max.i << " to "<< max.j << "\n";
  return 0;
}
