#include "pch.h"
#include "HttpOperating.h"
#include "Wininet.h"
#include <atlfile.h>

DWORD HttpOperatingClass::defaultHttpFlac = {
    INTERNET_FLAG_KEEP_CONNECTION |
    INTERNET_FLAG_NO_AUTO_REDIRECT | //���Զ�����HTTP�����ض���ֻ
    INTERNET_FLAG_NO_COOKIES | //�����Զ����Cookie��ͷ������Ҳ�����Զ���ӷ��ص�Cookie��HTTP�����Cookie���ݿ�
    INTERNET_FLAG_NO_AUTH | //������HTTP�����Զ������֤
    // INTERNET_FLAG_CACHE_IF_NET_FAIL | //�������ʧ�ܣ��򷵻ػ����ļ�
    INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | //����sslģʽ�µ�https->http��ת
    INTERNET_FLAG_IGNORE_CERT_CN_INVALID | //����sslģʽ�µ�֤�����ƴ���
    INTERNET_FLAG_NO_UI | //����cookie�ĶԻ���
    //INTERNET_FLAG_SECURE |//����sslģʽ
    0
};


std::string HttpOperatingClass::HttpRequest(std::string ip, int port, std::string url, std::string file, std::string type, bool isSSL, std::map<std::string, std::string> cookies) {
    return HttpRequestUpdateFile(ip, port, url, file, type, isSSL, cookies);
}

std::string HttpOperatingClass::HttpRequestUpdateFile(std::string ip, int port, std::string url, std::string file, std::string snedType, bool isSSL, std::map<std::string, std::string> cookies) {
    // Local variables
    //std::string file = "1.txt";         //Filename to be loaded
    const char* type = "image/jpg";
    char boundary[] = "pippo";              //Header boundary
    char nameForm[] = "file";               //Input form name

    char hdrs[255];                         //Headers
    char* buffer = (char*)calloc(1, sizeof(char));                           //Buffer containing file + headers
    std::string strResponse = "";           // recv

    DWORD httpFlac = defaultHttpFlac;
    if (isSSL) {
        httpFlac = httpFlac | INTERNET_FLAG_SECURE;
    }

    // obtain file size:
    if (!file.empty()) {
        char* fileData;
        int fileDataLen = WeteoesDll::IO_ReadFile((char*)file.c_str(), fileData);
        if (fileDataLen == 0) { return ""; }
        std::string fileDataStr = std::string(fileData, (size_t)fileDataLen);

        //allocate memory to contain the whole file + HEADER
        int bufferSize = sizeof(char) * fileDataLen + 2048;
        buffer = (char*)malloc(bufferSize);
        //print header5
        sprintf_s(hdrs, "Content-Type: multipart/form-data; boundary=%s", boundary);
        sprintf_s(buffer, bufferSize, "--%s\r\nContent-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\n", boundary, nameForm, file.c_str());
        sprintf_s(buffer, bufferSize, "%sContent-Type: %s\r\n\r\n", buffer, type);
        sprintf_s(buffer, bufferSize, "%s%s\r\n", buffer, fileDataStr.c_str());
        sprintf_s(buffer, bufferSize, "%s--%s--\r\n", buffer, boundary);
    }

    //Open internet connection
    HINTERNET hSession = InternetOpen("WinSock", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (hSession == NULL) return "";

    HINTERNET hConnect = InternetConnect(hSession, ip.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
    if (hConnect == NULL) return "";
    
    HINTERNET hRequest = HttpOpenRequest(hConnect, snedType.c_str(), url.c_str(), NULL, NULL, NULL, httpFlac, 1);
    if (hRequest == NULL) return "";

    std::string cookiesStr = getCookieStr(cookies);
    if (!cookiesStr.empty()) {
        HttpAddRequestHeaders(hRequest, cookiesStr.c_str(), (DWORD)cookiesStr.length(), HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE);
    }

    BOOL sent;
    if (!file.empty()) {
        // ������ļ�
        sent = HttpSendRequest(hRequest, hdrs, (DWORD)strlen(hdrs), buffer, (DWORD)strlen(buffer));
    }
    else {
        // ���û���ļ�
        sent = HttpSendRequest(hRequest, NULL, 0, buffer, (DWORD)strlen(buffer));
    }
    if (!sent) { 
        int error = GetLastError();
        switch (error) {
        case ERROR_INTERNET_CANNOT_CONNECT:
            //MessageBox(NULL, _T("���������������"),_T(""), MB_OK);
            break;
        }
        return ""; 
    }
    while (TRUE) {
        char cReadBuffer[4096];
        unsigned long lNumberOfBytesRead;
        bool bRet = InternetReadFile(hRequest, cReadBuffer, sizeof(cReadBuffer) - 1, &lNumberOfBytesRead);
        if (!bRet || !lNumberOfBytesRead) { break; }
        cReadBuffer[lNumberOfBytesRead] = 0;
        strResponse += cReadBuffer;
    }
    //close any valid internet-handles
    InternetCloseHandle(hSession);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hRequest);

    return strResponse;
}

std::string HttpOperatingClass::getCookieStr(std::map<std::string, std::string> cookies) {
    std::string result = "";
    if (cookies.size() == 0) {
        return result;
    }
    result += "Cookie: ";
    std::map<std::string, std::string>::iterator i;
    for (i = cookies.begin(); i != cookies.end(); i++) {
        std::string key = i->first;
        std::string value = i->second;
        result += key + "=" + value + ";";
    }
    //"Cookie: JSESSIONID=46FBBCE3C9011DAF2F39CE2D7A538EE0\r\n";
    return result;
}
