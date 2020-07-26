#pragma once
#ifndef CreateDlgClass_H
#define CreateDlgClass_H

class CreateDlgClass {
public:
	void browser(
		std::string url,
		std::string browserKey,
		std::string dlgTitle = "Browser",
		int dlgWidth = 0,
		int dlgHeight = 0, 
		bool minimize = false,
		int dlgBorderStyle = BorderStyle_None
	);
	void init();
	void login();
	void login_sso();
	void changePassword();
	void main(bool minimize = false);

private:
	enum {
		BorderStyle_None = 0,
		BorderStyle_Dialog_Frame = 1,
		BorderStyle_Thin = 2,
		BorderStyle_Resizing = 3,
	};
};
#endif