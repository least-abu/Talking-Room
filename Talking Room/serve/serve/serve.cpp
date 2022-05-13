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
    addr.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");//接受任意ip地址
    addr.sin_port = htons(11111);
    int i = bind(s, (sockaddr*)&addr, len);

    //监听
    printf("正在等待客户端连接……\n");
    listen(s, 5);//瞬间来五个客户

    //等待别人连接
    //获取客户端ip地址
    sockaddr_in  caddr;
    caddr.sin_family = AF_INET;//协议
    int caddrlen = sizeof(sockaddr_in);

    //重新产生一个socket
    SOCKET sclient = accept(s, (sockaddr*)&caddr, &caddrlen);
    if (sclient == INVALID_SOCKET)
    {
        printf("客户端连接失败\n");
        return 0;
    }
    printf("客户端连接成功\n");
    printf("对方ip地址为:%s\n", inet_ntoa(caddr.sin_addr));

    while (1)
    {
        char url[256];
        gets_s(url, 256);
        int ret = send(sclient, url, sizeof(url), 0);
        if (ret <= 0)
        {
            printf("客户端已断开连接\n");
            break;
        }
    }

    //关闭
    closesocket(sclient);
    WSACleanup();
    return 0;
}