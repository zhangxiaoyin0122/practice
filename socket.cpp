//��������:
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
	//���������׽���
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("����socket�ɹ�\n");
	//ipv4�Ľṹ��
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("192.168.193.128", &addr.sin_addr);
	//��
	int r = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if (r == -1) perror("bind"), exit(1);
	printf("�󶨳ɹ�\n");

	//����Ϊ����������
	if ((r = listen(lfd, SOMAXCONN)) == -1)  //accept���е����ֵ
		perror("listen"), exit(1);
	printf("����Ϊ���������ֳɹ�\n");

	//�ȴ��ͻ�������
	int newlfd = accept(lfd, NULL, NULL);
	printf("�пͻ��˲���������\n");
	//��д�շ���Ϣ�Ĺ���
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


//�ͻ���:
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
			printf("�������ر���\n");
			close(lfd);
			break;
		}
		printf("buf=>%s\n", buf);
		memset(buf, 0x00, sizeof(buf));
	}
}
