#include "pch.h"
#include "AppCookieVisitor.h"

bool AppCookieVisitor::Visit(const CefCookie& cookie, int count, int total, bool& deleteCookie) {
    if (count == total) {
        return false;
    }
    std::wstring domain = cookie.domain.str;
    if (cookie.name.str && cookie.value.str) {
        std::string strName = UnicodeToAnsi(cookie.name.str);
        std::string strValue = UnicodeToAnsi(cookie.value.str);
        if (domain == L"passwordbox.weteoes.cn") {
            // Èç¹ûÊÇSSOµÇÂ¼
            VariableClass::loginSSOClass.Cookie(strName, strValue);
            return true;
        }
    }
    return true;
}

char* AppCookieVisitor::UnicodeToAnsi(const wchar_t* szStr) {
    int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
    if (nLen == 0) {
        return NULL;
    }
    char* pResult = new char[nLen];
    WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
    return pResult;
}