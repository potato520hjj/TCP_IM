//local test1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = INADDR_ANY;  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);
    //接收客户端请求
    char revData[255];
char sendData[255]={0};
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock;
    int ret;
    int i ;
	printf("等待连接...\n");
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    	printf("接收到一个来至> %s <的连接\r\n", inet_ntoa(clnt_addr.sin_addr));
	 char str[] = "您已登陆成功!\n";
       write(clnt_sock, str, sizeof(str));
     while(1){
	//向客户端发送数据
     
     //接收数据
	ret = recv(clnt_sock, revData, 255, 0);
	if(ret > 0)
	{
		revData[ret] = 0x00;
		
		if(strcmp(revData,"exit") == 0)break;
		printf("->");
		printf(revData);
		for(i = 0; i < ret; i++)
			revData[i] = 0;
		printf("\n");
	} 
}  
 //关闭套接字
    close(clnt_sock);

    close(serv_sock);
    return 0;
}
