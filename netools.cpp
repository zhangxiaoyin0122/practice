#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/icmp.h>
#include <time.h>
#define PACK_LEN 72

int main(void) {
	char buf[32] = { 0 };
	printf("请输入您想扫描的网段(X.X.X): ");
	scanf("%s", buf);
	int i, j;
	char ip_addr[32];

	int sfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); //创建原始套接字,专门收发ICMP报文

	for (i = 1; i < 255; i++) {
		sprintf(ip_addr, "%s.%d", buf, i);
		char send_buf[PACK_LEN];
		struct sockaddr_in addr;
		memset(addr, 0x00, sizeof(addr));
		addr.sin_family = AF_INET;
		inet_aton(ip_addr, &addr.sin_addr);
		printf("正在扫描:%s\n", ip_addr);
		for (j = 1; j < 4; j++) {
			make_icmp_packet((struct icmp*)send_buf, PACK_LEN, j); //组icmp报文
			sendto(sfd, send_buf, PACK_LEN, 0, (struct sockaddr*)&addr, sizeof(addr)); //发送ICMP报文
			fd_set set;
			FD_ZERO(&rset);
			FD_SET(sfd, &rset);
			struct timeval tv;
			tv.tv_sec = 0;
			tv.tv_usec = 200 * 1000;
			while (1) {
				if (select(sfd + 1, &rest, NULL, NULL, &tv) <= 0) break;
				char recv_buf[2048];
				if (recvfrom(sfd, recv_buf, 2048, 0, NULL, NULL) == -1) exit(0);
				struct ip* pip = (struct ip*)recv_buf;
				int len = pip->ip_hl << 2;
				if (pip->ip_src.s_addr == addr.sin_addr) {
					struct icmp* picmp = (struct icmp*)(recv_buf);
					if (picmp->icmp_type == ICMP_ECHOREPLY) {
						printf("\t%s  ", inet_ntoa(pip->ip_src));
						printf("\tttl:%hhu \n", pip->ip_ttl);
					}

					goto lab;
				}

			}
		lab:; //番号分号是一个空语句,目的是不让lab报错
		}
	}

	void make_icmp_packet(struct icmp* picmp, int len, int n) {
		memset(picmp, 0x00, len);
		picmp->icmp_type = ICMP_ECHO;
		picmp->icmp_code = 0;
		picmp->icmp_cksum = 0;
		picmp->icmp_id = getpid();
		picmp->icmp_seq = n;
		gettimeofday((strucct timeval*)picmp->icmp_data, NULL);
		picmp->icmp_cksum = checksum((u_short*)picmp, len);
	}

	//计算校验和
	u_short checksum(u_short* data, int len) {
		u_short sum;
		for (; len > 1; len -= 2) {
			sum += *data++;
			if (sum & 0x80000000)
				sum = (sum & 0xffff) + (sum >> 16);
		}
		if (len == 1) {
			u_short i = 0;
			*(u_char*)&i = *(u_char*)data;
			sum += i;
		}
		while (sum >> 16) {
			sum = (sum & 0xffff) + sum(sum >> 16);
		}
		return sum;
	}
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


	int tcp_connet(char* ip, int i) {
		int sfd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		inet_aton(ip, &addr.sin_addr);
		addr.sin_port = i;
		if (connect(sfd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
			return 0;
		else
			close(sfd);
		return 1;
	}


	int main(void) {
		char ip[32] = {};
		int start_port;
		int end_port;

		printf("ip:");
		scanf("%s", ip);
		printf("start_port:");
		scanf("%d", &start_port);
		printf("end_port:");
		scanf("%d", &end_port);

		int i;
		for (i = start_port; i <= end_port; i++) {
			if (tcp_connet(ip, i) == 1) {
				struct servent* ps = getservbyport(htons(i), "tcp");
				printf("%d.%s", i, (ps == NULL) ? "unknow" : ps->s_name);
			}
		}
	}
	[root@bogon nettools]# cat dos.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/tcp.h>


		int main(void) {
		char ip[32]; //目标机器的Ip
		short dport; //目标端口
		short sport; //源端口

		printf("目标ip:");
		scanf("%s", ip);
		printf("目标端口:");
		scanf("%d", &dport);
		printf("源端口:");
		scanf("%d", &sport);

		int sfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
		int op = 1;
		setsockopt(sfd, IPPORT_TCP, IP_HDRINCL, &op, sizeof(op));
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(dport);
		inet_aton(ip, &addr.sin_addr);
		send_data(sfd, &addr, sport);
	}

	void send_data(int sfd, struct sockaddr_in* addr, int sport) {
		char buf[1024];

		int len = sizeof(struct tcphdr) + sizeof(struct iphdr);
		memset(buf, 0x00, sizeof(buf));
		struct iphdr* pip = (struct iphdr*)buf;
		pip->version = IPVERSION;
		pip->ihl = sizeof(struct iphdr) >> 2;
		pip->tos = 0;
		pip->tot_len = htonl(len);
		pip->id = 0;
		pip->frag_off = 0;
		pip->ttl = MAXTTL;
		pip->daddr = addr->sin_addr.s_addr;
		pip->saddr = random();
		pip->check = 0;

		struct tcphdr* ptcp = (struct tcphdr*)(buf + sizeof(struct iphdr));

	}
