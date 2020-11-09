#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

//打印链路层的源mac地址和目标mac地址
void print_mac(struct ethhdr* p) {
	printf("%02x:%02x:%02x:%02x:%02x:%02x <=> ", p->h_source[0], p->h_source[1],
		p->h_source[2], p->h_source[3], p->h_source[4], p->h_source[5]);
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", p->h_dest[0], p->h_dest[1],
		p->h_dest[2], p->h_dest[3], p->h_dest[4], p->h_dest[5]);
}
//解析IP协议
void parse_ip(char* buf) {
	struct iphdr* pt = (struct iphdr*)buf;
	struct in_addr ad;
	ad.s_addr = pt->saddr;
	printf("\t%s <=> ", inet_ntoa(ad));
	ad.s_addr = pt->daddr;
	printf("%s\n", inet_ntoa(ad));
}

void parse_arp(char* buf) {
	printf("111\n");
}
int main(void) {
	int sfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	char buf[2000] = { 0 };
	while (1) {
		memset(buf, 0x00, sizeof(buf)); //清空缓冲区
		int r = read(sfd, buf, 2000);
		if (r <= 0) break;
		struct ethhdr* peth = (struct ethhdr*) buf;
		print_mac(peth);
		//判断上层协议
		if (peth->h_proto == ETH_P_IP) {
			//上层协议为IP
			parse_ip(buf + sizeof(struct ethhdr));
		}
		else if (peth->h_proto == ETH_P_ARP) {
			//上层协议为ARP
			parse_arp(buf + sizeof(struct ethhdr));
		}
	}
}
 //test.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

struct iphdr {
	unsigned int ihl : 4; //4位首部长度
	unsigned int version : 4; //4位版本号

	u_int8_t tos; //8位服务类型
	u_int16_t tot_len; //16位总长度
	u_int16_t id; //16位标识号
	u_int16_t frag_off; //3位标志＋13位片偏移
	u_int8_t ttl; //8位生存时间
	u_int8_t protocol; //8位协议
	u_int16_t check; //16位首部检验和
	u_int32_t saddr; //32位源IP地址
	u_int32_t daddr; //32位目的IP地址
};

int main(void) {
	int sfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	int op = 1;
	setsockopt(sfd, IPPROTO_IP, IP_HDRINCL, &op, sizeof(op));
	char buf[1501];
	while (1) {
		memset(buf, 0x00, sizeof(buf));
		int r = read(sfd, buf, 1500);
		struct iphdr* p = (struct iphdr*) (buf);
		printf("version: %x\n", p->version);
		struct in_addr ad;
		ad.s_addr = p->saddr;
		printf("\t%s <=> ", inet_ntoa(ad));
		ad.s_addr = p->daddr;
		printf("%s\n", inet_ntoa(ad));
	}
}
