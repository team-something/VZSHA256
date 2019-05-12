# VZSHA256

A C++ implementation of SHA 256 Algorithm. Made to use in the VZCoin Project.

Repo referred: https://github.com/Data-ptr/SHA256-le Thanks @Data-ptr !

## Output Files
Two output files are generated:
1. bin/test :- Generated to test if algorithm works
2. libs/sha256.a :- A static library that can be used to run this algo in any other code

## Instructions
```bash
  # Clone the repo
  $ git clone https://github.com/vazzup/VZSHA256.git

  # Go to the folder
  $ cd VZSHA256

  # Generate Makefiles using CMake
  $ cmake .

  # Compile using Makefile
  $ make

  # Test the program 
  $ ./bin/test < "Hello this is Vatsal kanakiya"

  # Output will be :- 9BD93B80BA05389EB487D7FD35FB4EA31872937D7DA268FD895D5856CC78CAEC
```
