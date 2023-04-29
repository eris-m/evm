# EVM

EVM is a stack-based virtual machine. 
It is a WIP Hobby project right now

EVM is written in C++20, and provides both the interpreter and other components as a library.
The interpreter is, as of now, non-existent, but will be implememted in the future.

Currently, work is being done on `evm_common`, 
which contains classes and functions common to all EVM components.
It also contains loading/saving logic for some types.

# Contributing

Contributing would be a great help.
If you spot a bug or want a feature, 
don't hesitate to open an issue.
If you contribute to EVM
please note that generally the code base follows the [GNU Coding Conventions](https://gcc.gnu.org/codingconventions.html).

# Building
Currently, 
the only requirement to building EVM is cmake.
To build evm, run `cmake -B <build_dir>`, 
which will build all targets.

If you don't want tests included, define `EVM_TESTS` to `OFF`,
eg. `cmake -B <build_dir> -DEVM_TESTS=OFF`.
