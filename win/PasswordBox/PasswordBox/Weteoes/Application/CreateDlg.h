#pragma once
#ifndef CreateDlgClass_H
#define CreateDlgClass_H

class CreateDlgClass {
public:
	void browser(
		std::string url,
		std::string browserKey,
		bool reloadURL,
		std::string dlgTitle = "Browser",
		int dlgWidth = 0,
		int dlgHeight = 0, 
		bool minimize = false,
		int dlgBorderStyle = BorderStyle_None
	);

public:
	void init(bool reloadURL = true);
	void login(bool reloadURL = true);
	void login_sso(bool reloadURL = true);
	void changePassword(bool reloadURL = true);
	void main(bool reloadURL = true, bool minimize = false);

public:
	std::string init_BrowserKey = "init";
	std::string login_BrowserKey = "login";
	std::string login_sso_BrowserKey = "login_sso";
	std::string changePassword_BrowserKey = "changePassword";
	std::string main_BrowserKey = "main";

private:
	enum {
		BorderStyle_None = 0,
		BorderStyle_Dialog_Frame = 1,
		BorderStyle_Thin = 2,
		BorderStyle_Resizing = 3,
	};
};
#endif