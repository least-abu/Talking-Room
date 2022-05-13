#include <WinSock2.h>
#include <string.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main()
{
    //初始化
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
    {
        printf("初始化失败\n");
        return 0;
    }
    printf("初始化成功\n");

    //创建socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
    {
        printf("创建socket失败\n");
        return 0;
    }
    printf("创建socket成功\n");

    //绑定
    sockaddr_in addr;
    int len = sizeof(sockaddr_in);
    addr.sin_family = AF_INET;//协议
    printf("请输入连接的ip地址：");
    char ip1[128];
    gets_s(ip1, 128);
    addr.sin_addr.S_un.S_addr = inet_addr(ip1);//接受任意ip地址
    addr.sin_port = htons(11111);

    //主动连接服务器
    int i = connect(s, (sockaddr*)&addr, len);
    if (i == SOCKET_ERROR)
    {
        printf("连接失败\n");
        return 0;
    }
    printf("连接成功\n");

    //接收数据
    while (1)
    {
        char url[256];
        int ret = recv(s, url, 256, 0);
        if (ret <= 0)
        {
            printf("已断开连接\n");
            break;
        }
        else
        {
            printf("%s\n",url);
        }
    }

    //关闭
    closesocket(s);
    WSACleanup();
    return 0;
}