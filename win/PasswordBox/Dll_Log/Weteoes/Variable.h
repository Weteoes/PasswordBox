#pragma once
#ifndef VariableClass_
#define VariableClass_
#include <pch.h>

class VariableClass {
public:
	static std::mutex logMutex; // ��־������
	static std::string logFile; // ��־����λ��+�ļ�
};
#endif