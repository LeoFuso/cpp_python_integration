### C++ / Python Integration

## Build process

``` bash

mkdir build/bin -p
mkdir build/lib

g++ -O0 -fPIC -c SquareRoot.cpp -o build/bin/sqrt.o
g++ -O0 -fPIC -I/usr/include/python2.7 -c sqrtlib.cpp -o build/bin/sqrtlib.o
g++ -shared -O0 build/bin/sqrt.o build/bin/sqrtlib.o -o build/lib/SquareRoot.so 

```
