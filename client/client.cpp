#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/select.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // 创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    // 将 IP 地址转换为二进制形式
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 设置非阻塞模式
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    // 使用 select 进行多路复用
    fd_set read_fds;
    int max_fd = sockfd;

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        // 等待套接字或标准输入有数据可读
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("select error");
            break;
        }

        // 检查是否有来自服务器的数据
        if (FD_ISSET(sockfd, &read_fds)) {
            bytes_read = read(sockfd, buffer, BUFFER_SIZE);
            if (bytes_read > 0) {
                // 将读取的数据写入标准输出
                if (write(STDOUT_FILENO, buffer, bytes_read) < 0) {
                    perror("Write to stdout failed");
                    break;
                }
            } else if (bytes_read == 0) {
                // 服务器关闭连接
                printf("Server closed the connection\n");
                break;
            } else {
                perror("Read from server failed");
                break;
            }
        }

        // 检查是否有用户输入的数据
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0'; // 确保字符串以 null 结尾
                if (send(sockfd, buffer, bytes_read, 0) < 0) {
                    perror("Send to server failed");
                    break;
                }
            } else if (bytes_read < 0) {
                perror("Read from stdin failed");
                break;
            }
        }
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}

