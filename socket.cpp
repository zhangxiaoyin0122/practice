//服务器端:
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void parse(char* buf) {
	int i, len;
	len = strlen(buf);
	for (i = 0; i < len; i++) {
		if (buf[i] >= 'a' && buf[i] <= 'z') {
			buf[i] -= 32;
		}
	}
}

int main(void) {
	//创建监听套接字
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("创建socket成功\n");
	//ipv4的结构体
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("192.168.193.128", &addr.sin_addr);
	//绑定
	int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if (r == -1) perror("bind"), exit(1);
	printf("绑定成功\n");

	//设置为被动监听字
	if ((r = listen(lfd, SOMAXCONN)) == -1)  //accept队列的最大值
		perror("listen"), exit(1);
	printf("设置为被动监听字成功\n");

	//等待客户端连接
	int newlfd = accept(lfd, NULL, NULL);
	printf("有客户端不连接上来\n");
	//读写收发信息的过程
	while (1) {
		char buf[1024] = {};
		r = read(newlfd, buf, 1024);
		if (r == 0)
			break;
		printf("%s\n", buf);
		parse(buf);
		write(newlfd, buf, r);
	}
	close(newlfd);
	close(lfd);
}


//客户端:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(void) {
	//
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	//
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("192.168.193.128", &addr.sin_addr);
	//
	int r = connect(lfd, (struct sockaddr*)&addr, sizeof(addr));

	char buf[1024] = {};
	while (fgets(buf, 1024, stdin) != NULL) {
		write(lfd, buf, strlen(buf));
		memset(buf, 0x00, sizeof(buf));
		r = read(lfd, buf, 1024);
		if (r <= 0) {
			printf("服务器关闭了\n");
			close(lfd);
			break;
		}
		printf("buf=>%s\n", buf);
		memset(buf, 0x00, sizeof(buf));
	}
}
