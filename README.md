# class Range<T>()

About this project
--------------------

This project defines simple header-only C++14 class to represent ranges and two convenience functions to enable using for-loops with following syntax:

```c++
for ( auto i: range(4) ) // equivalent to for( int i=0; i<4; ++i )
for ( auto i: range(1,4) ) // equivalent to for( int i=1; i<=4; ++i )
```

Note: There is one deviant case: `range(0)`, which is equivalent to `range(0,0)`.

Advanced ranges can be had using the class, thusly:

| Example                                                                 | Result                |
| :---------------------------------------------------------------------- | :-------------------- |
| `for( auto i:Range<>(3) )   cout << i << ",";`                          | 0,1,2,                |
| `for( auto i:Range<>(1,3) ) cout << i << ",";`                          | 1,2,3,                |
| `for( auto i:Range<>(1,3,2) ) cout << i << ",";`                        | 1,3,                  |
| `for( auto i:Range<>(10,14,2) ) cout << i << ",";`                      | 10,12,14,             |
| `for( auto i:Range<>(1) ) cout << i << ",";`                            | 0,                    |
| `for( auto i:Range<>(2) ) cout << i << ",";`                            | 0,1,                  |
| `for( auto i:Range<>(1,1) ) cout << i << ",";`                          | 1,                    |
| `for( auto i:Range<>(10,14,-2) ) cout << i << ",”; // sign corrected`   | 10,12,14,             |
| `for( auto i:Range<>(14,10,2) ) cout << i << ",";`                      | 14,12,10,             |
| `for( auto i:Range<>(14,10,-2) ) cout << i << ",”; // sign corrected`   | 14,12,10,             |
| `for( auto i:Range<>(0,-2)) cout << i << ",";`                          | 0,-1 -2,              |
| `for( auto i:Range<double>(7.1,7.3,0.1)) cout << i << ",";`             | 7.1,7.2,7.3,7.4,      |
| `for( auto i:Range<MyT>(3.75,3.70,-0.02)) cout << i << ",";`            | 3.75,3.73,3.71,3.69,  |
| `Range<> rint5{ 5 };`                                                   | Creates range object. |
| `cout << rint5.size();`                                                 | 5                     |
| `cout << *rint5;`                                                       | 0                     |
| `cout << rint5++;`                                                      | 0                     |
| `cout << *rint5;`                                                       | 1                     |
| `cout << ++rint5;`                                                      | 2                     |
| `cout << *rint5;`                                                       | 2                     |
| `cout << rint5();`                                                      | 2                     |
| `cout << *rint5;`                                                       | 0                     |
| `cout <<rint5.size();`                                                  | 0                     |
| `for( auto i:range(0) ) cout << i << “,”;`                              | 0,                    |
| `for( auto i:range(1) ) cout << i << “,”;`                              | 0,                    |
| `for( auto i:range(2) ) cout << i << “,”;`                              | 0,1,                  |
| `for( auto i:range(3) ) cout << i << “,”;`                              | 0,1,2,                |
| `for( auto i:range(1,3) ) cout << i << “,”;`                            | 1,2,3,                |
| `for( auto i:range(1,3,2) ) cout << i << “,”;`                          | 1,3,                  |
| `for( auto i:range(-3) ) cout << i << “,”;`                             | -2,-1,0,              |

Files
-----

```
- CMakeLists.txt
- README.md
- coord.h
- range.cpp -- testing
- range.hpp
```

## License

apache

Viewing
-------

This file uses [**GitHub flavored markdown**](https://github.github.com/gfm/). For measier viewing use one of:
1. Linux/OSX/Windows: [Typora.io](https://typora.io)
2. Online: [StackEdit](https://stackedit.io/editor)
3. General: [VIm](http://www.vim.org)

#### End
