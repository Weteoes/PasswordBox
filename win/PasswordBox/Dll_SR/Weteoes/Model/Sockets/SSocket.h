#ifndef SSocketClass_H
#define SSocketClass_H
//#include <winsock2.h> ������Ԥ����h��Ҫ��windows.hǰ
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <vector>
#include <map>
#include <thread>
#include <string>

class SSocketClass
{
public:
	int Entrance();

private:
	virtual void Loading() = 0; // ��ʼ��
	virtual SOCKADDR_IN Socket_Initialization() = 0; // Initialization Socket
	virtual void Socket_RunShell(SOCKET, std::string) = 0; // ��������
	virtual void Send_Socket_While(SOCKET) = 0; // ѭ������Socket

private:
	void SocketStart(); // ��Socket
	bool Recv_Socket(SOCKET socket, std::vector<std::string>* allResult);// ����Socket
	void Recv_Socket_While(SOCKET); // ѭ������Socket
public:
	bool Send_Socket(SOCKET, std::string); //����Socket
	void SocketStop(SOCKET); // �ر�Socket

public:
	bool SocketStopFlac = false; // �Ƿ�ֹͣSocket
	SOCKET sServer = NULL; // Socket

public:
	std::vector<SOCKET> clientList; // �ͻ����б�
	std::map<SOCKET, std::string> recvTempList; // ����Recv��ʱ����
	std::string flac_Start = "|start|"; // ��ʼflac
	std::string flac_End = "|end|"; // ����flac
	int socketCache = 5000; // ��������С
	bool w = true; // ���պͷ���ʱ�Ƿ����w����

};
#endif