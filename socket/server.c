#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int server_fd,client_fd;
    int server_len,client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    char back[] = {"I’m server"};
    /*创建服务器使用的socket*/
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    /*服务器Socket指定IP地址和端口，为便于本机测试指定服务器的IP地址是192.168.1.1而端口则为9266*/
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.1.1");
    server_address.sin_port = htons(9266);
    server_len = sizeof(server_address);
    /*接着将“电话号码”设定给“电话”，也就是将地址结构与Socket挂起钩来，指针赋值可以理解为钩子的挂入本书所称的“钩子函数”实际就是指针函数*/
    bind(server_fd,(struct sockaddr*)&server_address,server_len);
    /*创建一个Socket的监听队列（允许接收10个连接），监听客户端Socket的连接请求*/
    listen(server_fd,10);
    while(1) {
        char recv[20];
        printf("server is waiting\n");
        /*程序运行到此处时，说明客户端的连接请求已经到来，接受它的连接请求，克隆出一个Socket与客户端建立连接，并将客户端的“电话号码”记录在client_address中，函数返回建立连接的ID号*/
        client_len = sizeof(client_address);
        client_fd = accept(server_fd,(struct sockaddr*)&client_address,&client_len);
        /*使用read和write函数接收客户端字符然后发回客户端*/
        read(client_fd,recv,20);
        write(client_fd,back,20);
        printf("received from client= %s\n",recv);
        close(client_fd);
    }
    close(server_fd);
    exit(0);
}
