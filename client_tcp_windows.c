//test1
//test2
//test3
//test4
//test5
//test6
#include <WINSOCK2.H>
#include <STDIO.H>

#pragma  comment(lib,"ws2_32.lib")


int main(int argc, char* argv[])
{
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA data; 
	SOCKET sclient;
	char * sendData = "你好，TCP服务端，我是客户端!\n";
	char recData[255];
	int ret;
	struct sockaddr_in serAddr;
    if(WSAStartup(sockVersion, &data) != 0)
    {
        return 0;
    }

    sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sclient == INVALID_SOCKET)
    {
        printf("invalid socket !");
        return 0;
    }

   // sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(1234);
    serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//这里是服务器IP 
    if (connect(sclient, (struct sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        printf("connect error !");
        closesocket(sclient);
        return 0;
    }
    //char * sendData = "你好，TCP服务端，我是客户端!\n";
    send(sclient, sendData, strlen(sendData), 0);

    //char recData[255];
    ret = recv(sclient, recData, 255, 0);
    if(ret > 0)
    {
        recData[ret] = 0x00;
        printf(recData);
    }
    closesocket(sclient);
    WSACleanup();
    return 0;
}
