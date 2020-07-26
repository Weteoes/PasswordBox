#pragma once
#ifndef AppCookieVisitor_
#define AppCookieVisitor_
class AppCookieVisitor : public CefCookieVisitor {
public:
    AppCookieVisitor() {};
    ~AppCookieVisitor() {};

    bool Visit(const CefCookie& cookie, int count, int total,
        bool& deleteCookie);

private:
    char* UnicodeToAnsi(const wchar_t* szStr);

    IMPLEMENT_REFCOUNTING(AppCookieVisitor);
};
#endif