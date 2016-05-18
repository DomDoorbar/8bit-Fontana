# 8Bit Fontana #

This is an example C++ application using the SDL library.
It tries to be as nicely C++11 as possible but do keep in
mind that SDL is written in C and, at some stage, you have
to interface with it.

## Story ##
The evil b’Kuhn has transported you and your crew into the 8bit world where many viruses and bugs are coming to consume you and your ship. puzzle through this 8bit universe and destory the evil b'kuhn before he turns you in dump memory. **8Bit Fontana**.

## Installation ##
You will have to have the SDL development libraries installed on
your system.  The easiest way to compile is to use a command-line

```bash
$ g++ -c -std=c++11 src/*.cpp
$ g++ -o starship *.o -lSDL2 -lSDL2_image
```

which will produce an executable file called "8bit" in the
top-level directory.  To execute this file do the following

`$ ./8bit`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Credits ##
The sprites in this game were created by me through the use of a program called
https://www.Piskel.com for the creation tool
