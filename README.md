<h1 align="center"> Control-Core C++ Implementation </h1>

<div align="center" text-align="center">
  
![version](https://img.shields.io/badge/version-1.0.0-blue.svg) ![license](https://img.shields.io/badge/license-BSD%20--%20Clause%203-brightgreen)
  
</div>
  
## About
Control Core is a platform for control systems to treat conditions affecting internal organs. This repository is the C++ translation of Control Core framework which is initially written in Python. C++ inherently being faster than Python offers a much higher speed of code execution.

## Table of Contents
- [Quick Start :boom:](#quick-start)
- [Installation 🐣](#installation)
- [Starting the app](#starting-the-app)
- [Supoorted OS ✒](#supported-operating-systems)
- [Repository Structure](#repository-structure-guidelines)

## Quick Start
This is the offical repository of C++ Implemention of Control Core Framework.


## Installation

Follow these steps to install this project directory:

```
# clone the repo
$ git clone https://github.com/NISYSLAB/concore-cpp.git

# go into app's directory:
$ cd concore-cpp
```

## Starting the app

Follow these steps to run the app on your local machine:

```
# go into app's directory:
$ cd concore-cpp

# in a terminal, create a sub project in the format
$ python mkconcore.py <graphml-file> <source-directory> <subproject-name> <operating-system>
  
# example for windows
$ python mkconcore.py testZ.graphml testsou t2 windows

```

## Supported Operating Systems
1. Windows
2. Linux/Ubuntu
3. MacOS

### Repository structure guidelines
1. The repo contains the original python files (`pmpymat.py`, `cpymat.py` and `powermeter.py`) as well as their c++ translations (`pmpymat.cpp`, `cpymat.cpp` and `powermeter.cpp`) in testsou directory. `concore.py` and `concore.hpp` are present in the root directory.
2. The source directory has files involving the neuromodultation which is outside the current scope.
3. The graphml files which have a 'C' in their name work with C++ translated files. Others work with the python files. <br />
   Some highlights - <br />
    `testZ.graphml` - Basic Python functionality. `testZC.graphml` - Basic C++ functionality. <br />
    `test3.graphml` - Python with multiple port functionality `test3C.graphml` - C++ with multiple port functionality<br />
    
    <br /> To view these graphml files, yEd can be used.


