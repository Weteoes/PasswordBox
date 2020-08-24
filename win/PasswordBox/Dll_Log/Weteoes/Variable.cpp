#include "pch.h"
#include "Variable.h"

std::mutex VariableClass::logMutex;
std::string VariableClass::logFile = "log\\debug.log";