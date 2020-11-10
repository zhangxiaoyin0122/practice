//IP头部:
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

//TCP头部
struct tcphdr {
	u_int16_t source;  //16位源端口号
	u_int16_t dest;  //16位目的端口号
	u_int32_t seq; //32位序号
	u_int32_t ack_seq; //32位确认序号
	u_int16_t resl : 4; //4位首部长度
	u_int16_t doff : 4; //标志(保留4位)
	u_int16_t fin : 1; //发端完成发送任务
	u_int16_t syn : 1; //同步序号用来发起一个连接
	u_int16_t rst : 1; //重建连接
	u_int16_t psh : 1; //接收方应该尽快将这个报文段交给应用层
	u_int16_t ack : 1; //确认号有效
	u_int16_t urg : 1; //紧急指针有效
	u_int16_t res : 2;
	u_int16_t window;  //16位窗口大小  
	u_int16_t check; //16位检验和
	u_int16_t urg_ptr; //16位紧急指针

};

//UDP头部
struct udphdr {
	u_int16_t source; //
	u_int16_t dest; //
	u_int16_t len; //
	u_int16_t check; //
};

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

//解析TCP报文
void parse_tcp(char* buf) {
	struct tcphdr* p = (struct tcphdr*)buf;
	printf("%hu : %hd seq: %u,", ntohs(p->source), ntohs(p->dest), ntohs(p->seq));
	if (p->ack) {
		printf("ack_seq: %u", ntohs(p->ack_seq));
	}
	if (p->fin) {
		printf(" fin");
	}
	if (p->syn) {
		printf(" syn");
	}
	if (p->ack) {
		printf(" ack");
	}
	printf("\n");
}

//解析UDP报文
void parse_udp(char* buf) {
	struct udphdr* p = (struct udphdr*)buf;
	printf("%hu : %hu", ntohs(p->source), ntohs(p->dest));
	printf("\n\n");
}

//解析ICMP报文
void parse_icmp(char* buf) {
	struct icmphdr* p = (struct icmphdr*)buf;
	printf("icmp\n");
}

//解析IP协议
void parse_ip(char* buf) {
	struct iphdr* pt = (struct iphdr*)buf;
	//printf("version: %x",pt->version); //输出版本号
	struct in_addr ad;
	ad.s_addr = pt->saddr;
	printf("\t%s <=> ", inet_ntoa(ad)); //输出源IP地址   inet_ntoa:将ad结构体的参数(ad.s_addr)转换为字符串
	ad.s_addr = pt->daddr;
	printf("%s,protocol: %hhd,ttl:%hhu,tot_len:%hu\n", inet_ntoa(ad), pt->protocol, pt->ttl, pt->tot_len); //输出目的IP地址,
	if (pt->protocol == IPPROTO_TCP) {
		printf("\n\t\t");
		parse_tcp(buf + sizeof(struct iphdr));
	}
	else if (pt->protocol == IPPROTO_UDP) {
		printf("\n\t\t");
		parse_udp(buf + sizeof(struct iphdr));
	}
	else if (pt->protocol == IPPROTO_ICMP) {
		printf("\n\t\t");
		parse_icmp(buf + sizeof(struct iphdr));
	}
}

void parse_arp(char* buf) {
	printf("arp\n");
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

