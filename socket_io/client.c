#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int client_fd;
    int server_len;
    struct sockaddr_in server_address;
    int result;
    char temp[] = {"I'm client"},recv[20];

/*象服务器一样，首先要创建客户端的socket，然后使用这个socket向服务器通信*/

    client_fd= socket(AF_INET,SOCK_STREAM,0);

/*还要设定服务器的“电话号码”，准备连接使用*/
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.1.1");
    server_address.sin_port = htons(9266);
    server_len= sizeof(server_address);

/*向服务器端发出连接请求，请求服务器同意接收*/
    result = connect(client_fd,(struct sockaddr *)&server_address,server_len);

    if(result == -1) {
        perror("error: connect failed");
        exit(1);
    }

/*连接成功，开始向服务器发送字符并接收返回内容打印到控制台*/

    write(client_fd,temp,20);
    read(client_fd,recv,20);
    printf("sent from server = %s\n",recv);
    close(client_fd);
    exit(0);
}
