#ifndef WebSocketClass_H
#define WebSocketClass_H
#include <pch.h>
#include <Weteoes/Model/Sockets/SSocket.h>

class WebSocketClass : public SSocketClass
{
public:
	WebSocketClass(std::string webPath);

private:
	virtual void Loading(); // 初始化
	virtual SOCKADDR_IN Socket_Initialization(); // Initialization Socket
	virtual void Socket_RunShell(SOCKET, std::string); // 运行命令
	virtual void Send_Socket_While(SOCKET); // 循环发送Socket

private:
	std::string OtherSend();
	std::string GetHeader(std::string);
	bool fileByte(std::string); // 是否需要通过Byte传输的格式

private:
	std::string webPath = "";
};
#endif

#ifndef WebSocketClass_CPP
#define WebSocketClass_CPP
#define WEBHEADER "\
HTTP/1.1 200 OK\r\n\
Content-Type: text/html; charset=UTF-8\r\n\
Server: ZYhttp_v1.0.1\r\n\
Content-Length: %ld\r\n\r\n"

#include <Weteoes/Dll/WeteoesDll.h>
#include <fstream>

inline WebSocketClass::WebSocketClass(std::string webPath) {
	this->webPath = webPath;
}

void WebSocketClass::Loading() {
	w = false; // 不根据w规则
}
SOCKADDR_IN WebSocketClass::Socket_Initialization() {
	SOCKADDR_IN server;
	memset(&server, 0, sizeof(SOCKADDR_IN)); //初始化(先将保存地址的server置为全0)
	int Socket_Port = 23340; // 默认监听端口
	string Software_UI_Port = ManagementDll::Get((char*)"Software_UI_Port");
	if (!Software_UI_Port.empty()) { 
		// 不为空,替换
		Socket_Port = atoi(Software_UI_Port.c_str());
	}
	server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式
	server.sin_port = htons(Socket_Port); //指明连接服务器的端口号
	server.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // Server服务端Socket
	return server;
}

void WebSocketClass::Socket_RunShell(SOCKET client, std::string data) { //执行动作
	std::string result = "";
	if (data.find("GET") != 0) { result = OtherSend(); goto f_result; }
	else {
		std::string file = data.substr(4);
		file = file.substr(0, file.find(" "));
		if (file == "/") { file = "/index.html"; }
		// operating
		if (VariableClass::webOperatingClass.Entrance(file, result)) {
			result = GetHeader("") + result;
			goto f_result;
		}
		if (file.find(".") == -1) { file = "/index.html"; } // VUE 转发
		std::string pathFile = this->webPath + file;
		if(WeteoesDll::IO_Exists((char*)pathFile.c_str())) {
			//fileByte.
			std::string urlType = pathFile.substr(pathFile.find_last_of(".") + 1);
			if (fileByte(urlType)) {
				std::fstream filea(pathFile.c_str(), std::ios::binary | std::ios::in);
				filea.seekg(0, std::ios::end); //文件指针指向结尾
				int length = (int)filea.tellg(); //获取文件长度
				filea.seekg(0, std::ios::beg); //文件指针从新指向开头
				char* buffer = (char*)calloc(length, sizeof(char));           //存储读取字符串
				filea.read(buffer, length);
				result = GetHeader(pathFile);
				Send_Socket(client, result);
				result = "";
				send(client, buffer, length, 0);
			}
			else {
				char* pathFile_c;
				int pathFile_c_len = WeteoesDll::IO_ReadFile((char*)pathFile.c_str(), pathFile_c);
				result = GetHeader(pathFile) + string(pathFile_c, pathFile_c_len);
			}
		}
		else { result = OtherSend(); }
	}
f_result:
	if (!result.empty()) { Send_Socket(client, result); }
	SocketStop(client);
}

void WebSocketClass::Send_Socket_While(SOCKET) {
	return;
}

std::string WebSocketClass::OtherSend() {
	return GetHeader("") + "404";
}
inline std::string WebSocketClass::GetHeader(std::string file) {
	std::string result = "HTTP/1.1 200 OK\r\ncharset=UTF-8\r\nServer: Weteoes\r\n";
	if (VariableClass::DEBUG) {
		result += "Access-Control-Allow-Origin:*\r\n";
	}
	if (!file.empty()) { 
		std::string urlType = file.substr(file.find_last_of(".") + 1);
		if (urlType == "woff") { result += "Content-Type: application/font-woff\r\n"; }
		else if (urlType == "ttf") { result += "Content-Type: font/ttf\r\n"; }
		else if (fileByte(urlType)) { result += "Accept-Ranges: bytes\r\nDate: Weteoes\r\n\r\n"; }
	}
	result += "\r\n";
	return result;
}
bool WebSocketClass::fileByte(std::string urlType) {
	if (
		urlType == "jpg" ||
		urlType == "jpeg" ||
		urlType == "png" ||
		urlType == "ico" ||
		urlType == "icon" ||
		urlType == "woff" ||
		urlType == "ttf"
		) {
		return true;
	}
	return false;
}
#endif