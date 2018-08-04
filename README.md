# jregex

**A C++ Regular Expression Library**

Authur: Huang Jiahua


## Features

- Judge whether a string (from c++ STL) matches the given regular expression.
- Judge whether a string contains sub-string that matches the given regular expression.
- Find the first sub-string in a string that matches the given regular expression.
- Find all the sub-string in a string that matches the given regular expression.

## Documentation

[The documentation file](docs/index.md) is in this repository.

## Building

This project supports [CMake](https://cmake.org) out of the box.

Quick start:

``` bash
mkdir build
cd build
cmake..
```

Please see the 'CMakeList.txt'.

## Repository Contents

See [docs/index.md](docs/index.md) for more.

The public interface is in include/*.h. Callers should not include or rely on the details of any other header files in this package. 

Header File:

- include/jregex/jregex.h




