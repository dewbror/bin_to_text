bin_to_text 1.0.0
===============
Welcome to bin_to_text v1.0.0

bin_to_text is a simple CLI program for converting text written as binary to human readable text assuming the text is ascii encoded.

This program assumes each character is encoded as 8 bits.

Options:

  -f="path/to/file"    Read in binary from a text file and print it as text to stdout.
  
  -b="binary-code"     Read in binary from argument and print it as text to stdout.

How to Build
------------
Whith cmake:
```
cmake -S . -B ./build
cmake --build ./build
```
or just use your compiler directly
```
gcc bin_to_text.c -o ./build/bin_to_text
```

Example
-------
Display program information:
```
./build/bin_to_text
```
Read binary from file:
```
./build/bin_to_text -f="binary.txt"
```
--- end of README ---
