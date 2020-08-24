#include <pch.h>
#include <Weteoes/Application/Log.h>

bool ready() {
	if (!WeteoesDll::Ready()) { return false; }
	return true;
}

extern "C" _declspec(dllexport) bool Write(const char* msg) {
	if (!ready()) { return false; }
	VariableClass::logMutex.lock();
	bool result = LogClass::Write(msg);
	VariableClass::logMutex.unlock();
	return result;
}

extern "C" _declspec(dllexport) bool Info(const char* msg) {
	if (!ready()) { return false; }
	VariableClass::logMutex.lock();
	bool result = LogClass::Info(msg);
	VariableClass::logMutex.unlock();
	return result;
}