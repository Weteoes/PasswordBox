#pragma once
#ifndef VariableClass_
#define VariableClass_
#include <pch.h>

class VariableClass {
public:
	static std::mutex logMutex; // 日志事务锁
	static std::string logFile; // 日志保存位置+文件
};
#endif