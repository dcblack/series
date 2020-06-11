// Example
#include "series.hpp"
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------------------------------
class MyT {
public:
  MyT(float value=0.0): m_value(value) {}
  MyT(const MyT& rhs) = default;
  ~MyT(void) = default;
  MyT& operator=(const MyT& rhs) = default;
  MyT& operator++(void) { m_value += 1.0; return *this; }
  MyT& operator+=(const MyT& rhs) { m_value += rhs.m_value; return *this; }
  MyT  operator-(void) { return MyT{-m_value}; }
  bool operator<(const MyT& rhs) const { return m_value < rhs.m_value; }
  float value(void) const { return m_value; }
private:
  float m_value{0.0};
};

std::ostream& operator<<(std::ostream& os, const MyT& rhs) {
  os << rhs.value();
  return os;
}

#define Do_Series(...) do {\
    std::cout << "Series<>(" << #__VA_ARGS__ << ")" << std::endl;\
    for (auto i: Series<>{__VA_ARGS__}) {\
      std::cout << i << std::endl;\
    }\
  } while(0)
#define Do_SeriesT(T,...) do {\
    std::cout << "Series<"<<#T<<">(" << #__VA_ARGS__ << ")" << std::endl;\
    Series<T> r{__VA_ARGS__};\
    for (auto i: r) {\
      std::cout << i << std::endl;\
    }\
    std::cout << "Count: " << r.count() << std::endl;\
  } while(0)
#define Do_series(...) do {\
    std::cout << "series(" << #__VA_ARGS__ << ")" << std::endl;\
    for (auto i: series(__VA_ARGS__)) {\
      std::cout << i << std::endl;\
    }\
  } while(0)

int main(void) {

  std::cout << "*** Basic use case " << std::string(40,'*') << std::endl;
  Do_Series(3);
  Do_Series(1,3);
  Do_Series(1,3,2);
  Do_Series(10,14,2);
  Do_Series(1);
  Do_Series(2);
  Do_Series(1,1);
  Do_Series(10,14,-2); // Corrects to +2
  Do_Series(14,10,2);
  Do_Series(14,10,-2);
  Do_Series(0,-2);
  Do_SeriesT(double,7.1,7.3,0.1);
  Do_SeriesT(MyT,3.75,3.70,-0.02);

  std::cout << "*** Advanced tests " << std::string(40,'*') << std::endl;

  std::cout << "Series<> series_var { 5 };" << std::endl;
  Series<> series_var { 5 };
  std::cout << "series_var.size() => " << series_var.size() << std::endl;
  std::cout << "*rint => " << *series_var << std::endl;
  std::cout << "rint++ => " << series_var++ << std::endl;
  std::cout << "*rint => " << *series_var << std::endl;
  std::cout << "++rint => " << ++series_var << std::endl;
  std::cout << "*rint => " << *series_var << std::endl;
  std::cout << "rint() => " << series_var() << std::endl;
  series_var.reset();
  std::cout << "*rint => " << *series_var << std::endl;
  Series<> rsprint { 30, 25 };
  std::cout << "rsprint.size() = " << rsprint.size() << std::endl;

  std::cout << "*** Conveniences " << std::string(40,'*') << std::endl;
  Do_series(3);
  Do_series(1,3);
  Do_series(1,3,2);
  Do_series(-3);
  Do_series(0);
  Do_series(1);
  Do_series(0,0);
  Do_series(1,1);

  std::cout << "*** Done " << std::string(40,'*') << std::endl;

  return 0;
}
