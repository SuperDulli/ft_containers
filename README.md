# ft_containers
C++ containers

## Content

my implementation of some STL containers and utilities (C++98):

- vector
- map
- stack
- set

- iterator_traits
- reverse_iterator
- enable_if
- is_integral
- equal and lexicographical_compare
- pair
- make_pair

## Notes

Both map and set are using a Red-Black tree.

My Containers can be used with ft::\<container\>.

[Reference](https://cppreference.com/)

## Usage

`make all` - build 4 executables: tests with my containers, the STL containers and with and without debug messages.

`make compare` - builds, runs and compare the tests between mine and the standard.

`make test_rb_tree && ./test_rb_tree` - test the Red-Black tree implementation on its own.

`make test_intra` - downloads and builds the test from the project page
