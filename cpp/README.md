### C++ / Python Integration

## Build process

_side note_: This is not even close to an ideal building process.
There are some particular and inconsistent behaviors
throughout the process.

* You need to have [CMake](https://cmake.org/) installed
* You need to have some version of [Python](https://www.python.org/)
installed, preferably [Python 3](https://www.python.org/downloads/release/python-364/)

_another side note_:
Depending on your operating system, these steps can vary greatly.
Also, in the case of Linux, in different distributions.

_What is [CMake](CMakeLists.txt) doing?_

Based on the directory where you run the build, it will download a
[Boost](https://www.boost.org/) distribution and generate some
environment variables on top of that. During this process, it will
also detect the version of Python that you are using.

Supposedly, you would not have to have a version of Boost installed on
your operating system, since the build process handles that part for you.
Supposedly.

That said, we also have to install a version of Boost with Python
configured, and depending on your Linux distribution, Numpy has to be
configured together.

``` bash
$ apt-cache search libboost-python-dev
$ apt-cache search libboost-numpy-dev
$ apt install *whatever you find*
```

After that, it's a good idea to set a version of Python to be set as
the main version.

``` bash
$ update-alternatives --install /usr/bin/python python /usr/bin/python3 10
```

In this case, I chose to set Python3 as the primary.


Here are the settings that worked for me:

``` bash
$ sudo apt install python3
$ sudo apt install python3-pip
$ pip3 install numpy
$ sudo apt install libboost-python1.65.1
$ sudo apt install libboost-numpy1.65.1
$ update-alternatives --install /usr/bin/python python /usr/bin/python3 10
```

In another situation:

``` bash
$ sudo apt install python3
$ sudo apt install python3-pip
$ pip3 install numpy
$ sudo apt install libboost-python-dev
$ update-alternatives --install /usr/bin/python python /usr/bin/python3 10
```

Assuming everything is installed properly, just run the build commands

``` bash
$ mkdir build
$ cd build
$ cmake ..
$ make sqrtlib
```