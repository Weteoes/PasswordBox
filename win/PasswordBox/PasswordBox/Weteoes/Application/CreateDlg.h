#pragma once
#ifndef CreateDlgClass_H
#define CreateDlgClass_H
class CreateDlgClass {
public:
	void browser(string url, bool minimize = false);
	void init();
	void login();
	void changePassword();
	void main(bool minimize = false);
};
#endif