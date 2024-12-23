## Introduction

this is a simple C++ logger library, support different levels of log printing.
`DEBUG`, `INFO`, `WARN`, `ERROR`, `FATAL`
It uses printf-like way to print formatted message.

## Usage
```c++
#include "logger.h"
debug("hello logger: %d", 1);
info("hello logger: %d", 2);
warn("hello logger: %d", 3);
error("hello logger: %d", 4);
fatal("hello logger: %d", 5);
```
printed log message as below if level configured : `WARN`
```sh
2024-12-23.10:38:41 [WARN][main.cc:12]hello logger: 3
2024-12-23.10:38:41 [ERROR][main.cc:13]hello logger: 4
2024-12-23.10:38:41 [FATAL][main.cc:14]hello logger: 5
```
