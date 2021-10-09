#include "coord.hpp"
#include "series.hpp"
#include <iostream>

using namespace std;

int main()
{
  Coord r1{3,4};   cout<< "r1:" << r1 << endl;
  Polar p1{r1};    cout<< "p1:" << p1 << endl;
  Coord r2{p1};    cout<< "r2:" << r2 << endl;
  r2 = Coord{10,-3}; cout<< "r2:" << r2 << endl;
  Coord dist = r2 - r1;
  Coord delta = dist / 4;
  Series<Coord> line1{r1, r2, delta};
  for( auto i: line1 ) {
    cout << line1.count() << ": " << i << endl;
    if( line1.count() > 10 ) break;
  }
  return 0;
}
