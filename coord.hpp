/**
 * @file   coord.hpp
 * @brief  Rectangular and Polar 3-dimensional coordinates using floating point
 */
#ifndef COORD_HPP
#define COORD_HPP

#include <cmath>

//------------------------------------------------------------------------------
class Polar;

class Coord {
public:
  explicit Coord(double x=0.0, double y=0.0, double z=0.0): m_x(x), m_y(y), m_z(z) {}
  Coord(const Coord& rhs) = default;
  explicit Coord(const Polar& rhs);
  ~Coord() = default;
  Coord& operator=(const Coord& rhs) = default;
  Coord& operator++();
  Coord& operator+=(const Coord& rhs) {
    m_x += rhs.m_x;
    m_y += rhs.m_y;
    m_z += rhs.m_z;
    return *this;
  }
  Coord& operator-=(const Coord& rhs) {
    m_x -= rhs.m_x;
    m_y -= rhs.m_y;
    m_z -= rhs.m_z;
    return *this;
  }
  Coord operator+(Coord rhs) const {
    return rhs += *this;
  }
  Coord operator-(Coord rhs) const {
    return -(rhs -= *this);
  }
  Coord  operator-() const { return Coord{-m_x,-m_y,-m_z}; }
  bool operator==(const Coord& rhs) const {
    return m_x == rhs.m_x && m_y == rhs.m_y && m_z == rhs.m_z ;
  }
  Coord& operator*=(double rhs) {
    m_x *= rhs;
    m_y *= rhs;
    m_z *= rhs;
    return *this;
  }
  Coord& operator/=(double rhs) {
    m_x /= rhs;
    m_y /= rhs;
    m_z /= rhs;
    return *this;
  }
  Coord operator*(double rhs) {
    Coord result{*this};
    return result *= rhs;
  }
  Coord operator/(double rhs) {
    Coord result{*this};
    return result /= rhs;
  }
  bool operator<(const Coord& rhs) const;
  double mag() const { return ( sqrt( m_x * m_x + m_y * m_y + m_z * m_z ) ); }
  double x() const { return m_x; }
  double y() const { return m_y; }
  double z() const { return m_z; }
private:
  friend class Polar;
  double m_x{0.0}, m_y{0.0}, m_z{0.0};
};

//------------------------------------------------------------------------------
class Polar {
public:
  explicit Polar(double r=0.0, double t=0.0, double p=0.0): m_r(r), m_t(t), m_p(p) {}
  explicit Polar(const Coord& rhs)
  : m_r(sqrt( rhs.m_x * rhs.m_x + rhs.m_y * rhs.m_y + rhs.m_z * rhs.m_z ))
  , m_t((m_r == 0.0) ? 0.0 : acos(rhs.m_z / m_r))
  , m_p((rhs.m_x == 0.0) ? 0.0 : atan2(rhs.m_y,rhs.m_x))
  {}
  Polar(const Polar& rhs) = default;
  ~Polar() = default;
  Polar& operator=(const Polar& rhs) = default;
  Polar& operator++() {
    m_r += 1.0;
    return *this;
  }
  Polar& operator+=(const Polar& rhs) {
    Coord lhs(*this);
    lhs += Coord(rhs);
    *this = Polar(lhs);
    return *this;
  }
  Polar operator-() { return Polar(-Coord{*this}); }
  bool operator==(const Polar& rhs) const {
    return m_r == rhs.m_r && m_t == rhs.m_t && m_p == rhs.m_p ;
  }
  bool operator<(const Polar& rhs) const {
    return ( m_r < rhs.m_r ) || ( m_t < rhs.m_t ) || ( m_p < rhs.m_p );
  }
  double r() const { return m_r; }
  double t() const { return m_t; }
  double p() const { return m_p; }
private:
  friend class Coord;
  double m_r{0.0}, m_t{0.0}, m_p{0.0};
};

//------------------------------------------------------------------------------
Coord::Coord(const Polar& rhs)
: m_x(rhs.r()*sin(rhs.t())*cos(rhs.p())), m_y(rhs.r()*sin(rhs.t())*sin(rhs.p())), m_z(rhs.r()*cos(rhs.t()))
{
}
Coord& Coord::operator++() {
  Polar polar{*this};
  ++polar;
  *this = Coord(polar);
  return *this;
}
bool Coord::operator<(const Coord& rhs) const {
  return Polar(*this) < Polar(rhs);
}
Coord operator*(double lhs, Coord rhs) {
  return rhs *= lhs;
}
Coord operator/(double lhs, Coord rhs) {
  return rhs /= lhs;
}

//------------------------------------------------------------------------------
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Coord& rhs) {
  os << "(" << rhs.x() << "," << rhs.y() << "," << rhs.z() << ")";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Polar& rhs) {
  os << "(" << rhs.r() << "@" << rhs.t() << "@" << rhs.p() << ")";
  return os;
}

#endif /*COORD_HPP*/
