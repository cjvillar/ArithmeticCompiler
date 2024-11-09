#pragma once

// standard headers
#include <cctype>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> //used for system()
#include <unistd.h>  //sleep on mac & linux main.cpp

#include <stdexcept> //CodeGen exeption handling

// includes
#include "Token.h"
#include "Lexer.h"
#include "AST.h"
#include "CodeGen.h"
// #include "Irgenerator.h"
#include "Parser.h"