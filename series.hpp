#ifndef SERIES_HPP
#define SERIES_HPP

#if __cplusplus < 201103L
#  error Requires C++11
#endif

#include <cstddef>
#include <string>
#include <type_traits>

// Series<type>(first,last,increment) is a dummy container
// Requires: T(), T(const T&), T::operator=(const T&, T::operator-(), T::operator+=(const T&), T::operator<(const T&)
template<typename T = int>
struct Series {
  // Constructors
  explicit Series( T count, const std::string& name="" )
  : Series( (count == T())?T():(count<T())?incr(count):T(),(count == T())?T():(count<T())?T():decr(count),T(),name ) {}
  Series( const T& first, const T& last, const T& incr=T(), std::string name="" )
  :   m_first( first )
  ,   m_last( last )
  ,   m_incr( incr )
  ,   m_iter( first )
  ,   m_name( std::move(name) )
  {
    static_assert( std::is_constructible<T>::value, "" );
    static_assert( std::is_copy_assignable<T>::value, "" );
    // Is the increment equal to the default constructor of the type
    if ( not (m_incr < T() or T() < m_incr ) ) {
      ++m_incr;
    }
    // Are we increasing or decreasing?
    if ( ( m_first < m_last  && m_incr < T() ) || ( m_last  < m_first && T() < m_incr ) )  {
      m_incr = -m_incr;
    }
    m_last += m_incr;
    }
    Series( const Series& rhs )
    : m_first( rhs.m_first )
    ,   m_last( rhs.m_last )
    ,   m_incr( rhs.m_incr )
    ,   m_iter( rhs.m_iter )
    ,   m_cntr( rhs.m_cntr )
    ,   m_name( rhs.m_name )
    {
    }

    // Iterable functions
    const Series& begin() const { return *this; }
    const Series& end() const { return *this; }

    // Iterator functions
    bool operator!=( const Series& ) const
    { return ( T() < m_incr ) ? ( m_iter < m_last ) : ( m_last < m_iter ); }
    bool operator==( const Series& rhs ) const { return ( *this == rhs ); }
    T operator++() { ++m_cntr; m_iter += m_incr; return m_iter; }
    T operator++( int ) { ++m_cntr; T t(m_iter); ++(*this); return t; }
    T operator* () const { return m_iter; }
    T operator()() const { return m_iter; }
    std::string name() const { return m_name; }

    void reset() { m_cntr = 0; m_iter = m_first; }

    // Info
    size_t size() const { int sz{0}; for( int i{m_first}; i < m_last; ++sz,i+=m_incr ){} return sz; }
    size_t count() const { return m_cntr; }
private:
  T      const m_first;
  T      m_last;
  T      m_incr;
  T      m_iter;
  size_t m_cntr{0};
  const std::string m_name;
  static T incr(T v) { return ++v; }
  static T decr(T v) { return --v; }
};

// Convenience construction wrappers
template<typename T>
auto series( T n ) -> decltype(Series<>(n)) { return Series<>(n); }

template<typename T>
auto series( const T& f, const decltype(f)& t ) -> decltype(Series<>(f,t)) { return Series<>(f,t); }

template<typename T>
auto series( const T& f, const decltype(f)& t, const decltype(f)& i ) -> decltype(Series<>(f,t,i)) { return Series<>(f,t,i); }

#endif /*SERIES_HPP*/
