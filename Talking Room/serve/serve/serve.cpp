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
    addr.sin_addr.S_un.S_addr = inet_addr("0.0.0.0");//��������ip��ַ
    addr.sin_port = htons(11111);
    int i = bind(s, (sockaddr*)&addr, len);

    //����
    printf("���ڵȴ��ͻ������ӡ���\n");
    listen(s, 5);//˲��������ͻ�

    //�ȴ���������
    //��ȡ�ͻ���ip��ַ
    sockaddr_in  caddr;
    caddr.sin_family = AF_INET;//Э��
    int caddrlen = sizeof(sockaddr_in);

    //���²���һ��socket
    SOCKET sclient = accept(s, (sockaddr*)&caddr, &caddrlen);
    if (sclient == INVALID_SOCKET)
    {
        printf("�ͻ�������ʧ��\n");
        return 0;
    }
    printf("�ͻ������ӳɹ�\n");
    printf("�Է�ip��ַΪ:%s\n", inet_ntoa(caddr.sin_addr));

    while (1)
    {
        char url[256];
        gets_s(url, 256);
        int ret = send(sclient, url, sizeof(url), 0);
        if (ret <= 0)
        {
            printf("�ͻ����ѶϿ�����\n");
            break;
        }
    }

    //�ر�
    closesocket(sclient);
    WSACleanup();
    return 0;
}