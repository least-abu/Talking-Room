#include <WinSock2.h>
#include <string.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

int main()
{
    //��ʼ��
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
    {
        printf("��ʼ��ʧ��\n");
        return 0;
    }
    printf("��ʼ���ɹ�\n");

    //����socket
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
    {
        printf("����socketʧ��\n");
        return 0;
    }
    printf("����socket�ɹ�\n");

    //��
    sockaddr_in addr;
    int len = sizeof(sockaddr_in);
    addr.sin_family = AF_INET;//Э��
    printf("���������ӵ�ip��ַ��");
    char ip1[128];
    gets_s(ip1, 128);
    addr.sin_addr.S_un.S_addr = inet_addr(ip1);//��������ip��ַ
    addr.sin_port = htons(11111);

    //�������ӷ�����
    int i = connect(s, (sockaddr*)&addr, len);
    if (i == SOCKET_ERROR)
    {
        printf("����ʧ��\n");
        return 0;
    }
    printf("���ӳɹ�\n");

    //��������
    while (1)
    {
        char url[256];
        int ret = recv(s, url, 256, 0);
        if (ret <= 0)
        {
            printf("�ѶϿ�����\n");
            break;
        }
        else
        {
            printf("%s\n",url);
        }
    }

    //�ر�
    closesocket(s);
    WSACleanup();
    return 0;
}