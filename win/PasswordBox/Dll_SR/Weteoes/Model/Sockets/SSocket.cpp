#include <Weteoes/Loading.h>
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

	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //创建客户端套节字
	SOCKADDR_IN server = Socket_Initialization();

	// 绑定Socket Server到本地地址
	int result; //返回
	result = ::bind(sServer, (const struct sockaddr*) & server, sizeof(sockaddr_in));
	if (result == SOCKET_ERROR) { goto SocketStop; }

	// 监听
	result = listen(sServer, 1);
	if (result == SOCKET_ERROR) { goto SocketStop; }

	//循环等待
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
	// 释放连接和进行结束工作      
	closesocket(socket);
	socket = NULL;
}
void SSocketClass::Recv_Socket_While(SOCKET socket) {
	while (!SocketStopFlac) {
		std::vector<std::string> Recv_Cache;
		if (!Recv_Socket(socket, &Recv_Cache)) { break; } // 退出线程
		if (Recv_Cache.empty()) { continue; }
		for (std::string data : Recv_Cache) {
			Socket_RunShell(socket, data);
		}
	}
}
bool SSocketClass::Send_Socket(SOCKET socket, std::string data) {
	int result; //send result
	while (true) {
		if (w) { data = flac_Start + data + flac_End; } // 需要根据w规则
		result = send(socket, data.c_str(), (int)data.size(), 0); //发送数据
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) {
				Sleep(100);
				continue;
			}
			else { //发送失败
				return false;
			}
		}
		return true;
	}
}
bool SSocketClass::Recv_Socket(SOCKET socket, std::vector<std::string>* allResult) {
	/* Initialization */
	int result; //recv result
	int ConfigCache = socketCache; //配置的缓存大小
	char* result_byte = new char[ConfigCache]; //缓存数据byte
	std::string allData = ""; //已经接收数据
	ULONG MoreLen; //剩下的数据大小
	std::string recvTemp = recvTempList[socket];
	if (recvTemp.empty()) { recvTempList[socket] = ""; } // 没有数据就创建

	/* While Reve */
W_recv:
	while (true) {
		result = recv(socket, result_byte, ConfigCache - 1, 0); //接收数据(需要添加结束标记所以-1)
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) {
				continue;
			}
			else { //接收失败
				//SocketStop(socket);
				return false;
			}
		}
		// 是否有临时数据
		if (!recvTemp.empty()) { allData = recvTemp; recvTemp = ""; }
		/* Recv */
		result_byte[result] = 0x00; //添加结束标记
		allData += std::string(result_byte, result); //Cache >> AllResult
		memset(result_byte, 0, ConfigCache); //清空之前的数据
		ioctlsocket(socket, FIONREAD, &MoreLen); //检查剩下的数据
		if (MoreLen == 0 || allData.length() > 50000) { //接收完毕
			// 需要根据w规则
			if (w) {
				int findStart, findEnd;
				while ((findStart = (int)allData.find(flac_Start)) != -1 && findStart < allData.length() && (findEnd = (int)allData.find(flac_End, findStart)) != -1) {
					// 先放数据，再修改数据
					int subStart = findStart + (int)flac_Start.length();
					std::string onlyData = allData.substr(subStart, findEnd - subStart);
					if (onlyData.empty()) { continue; }
					while (true) { // 如果数据包错乱，丢掉前面一个包
						int findStart_ = (int)onlyData.find(flac_Start);
						if (findStart_ == -1) { break; }
						onlyData = onlyData.substr(findStart_ + (int)flac_Start.length());
					}
					allResult->push_back(onlyData);
					allData = allData.substr(findEnd + flac_End.length());
				}
				// 如果还有临时数据就存起来(没必要判断)
				recvTemp = allData;
				if (!allResult->empty()) { goto W_success; }
			}
			// 不需要根据w规则
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