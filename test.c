//IPͷ��:
struct iphdr {
	unsigned int ihl : 4; //4λ�ײ�����
	unsigned int version : 4; //4λ�汾��

	u_int8_t tos; //8λ��������
	u_int16_t tot_len; //16λ�ܳ���
	u_int16_t id; //16λ��ʶ��
	u_int16_t frag_off; //3λ��־��13λƬƫ��
	u_int8_t ttl; //8λ����ʱ��
	u_int8_t protocol; //8λЭ��
	u_int16_t check; //16λ�ײ������
	u_int32_t saddr; //32λԴIP��ַ
	u_int32_t daddr; //32λĿ��IP��ַ
};

//TCPͷ��
struct tcphdr {
	u_int16_t source;  //16λԴ�˿ں�
	u_int16_t dest;  //16λĿ�Ķ˿ں�
	u_int32_t seq; //32λ���
	u_int32_t ack_seq; //32λȷ�����
	u_int16_t resl : 4; //4λ�ײ�����
	u_int16_t doff : 4; //��־(����4λ)
	u_int16_t fin : 1; //������ɷ�������
	u_int16_t syn : 1; //ͬ�������������һ������
	u_int16_t rst : 1; //�ؽ�����
	u_int16_t psh : 1; //���շ�Ӧ�þ��콫������Ķν���Ӧ�ò�
	u_int16_t ack : 1; //ȷ�Ϻ���Ч
	u_int16_t urg : 1; //����ָ����Ч
	u_int16_t res : 2;
	u_int16_t window;  //16λ���ڴ�С  
	u_int16_t check; //16λ�����
	u_int16_t urg_ptr; //16λ����ָ��

};

//UDPͷ��
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
	unsigned int ihl : 4; //4λ�ײ�����
	unsigned int version : 4; //4λ�汾��

	u_int8_t tos; //8λ��������
	u_int16_t tot_len; //16λ�ܳ���
	u_int16_t id; //16λ��ʶ��
	u_int16_t frag_off; //3λ��־��13λƬƫ��
	u_int8_t ttl; //8λ����ʱ��
	u_int8_t protocol; //8λЭ��
	u_int16_t check; //16λ�ײ������
	u_int32_t saddr; //32λԴIP��ַ
	u_int32_t daddr; //32λĿ��IP��ַ
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

//��ӡ��·���Դmac��ַ��Ŀ��mac��ַ
void print_mac(struct ethhdr* p) {
	printf("%02x:%02x:%02x:%02x:%02x:%02x <=> ", p->h_source[0], p->h_source[1],
		p->h_source[2], p->h_source[3], p->h_source[4], p->h_source[5]);
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n", p->h_dest[0], p->h_dest[1],
		p->h_dest[2], p->h_dest[3], p->h_dest[4], p->h_dest[5]);
}

//����TCP����
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

//����UDP����
void parse_udp(char* buf) {
	struct udphdr* p = (struct udphdr*)buf;
	printf("%hu : %hu", ntohs(p->source), ntohs(p->dest));
	printf("\n\n");
}

//����ICMP����
void parse_icmp(char* buf) {
	struct icmphdr* p = (struct icmphdr*)buf;
	printf("icmp\n");
}

//����IPЭ��
void parse_ip(char* buf) {
	struct iphdr* pt = (struct iphdr*)buf;
	//printf("version: %x",pt->version); //����汾��
	struct in_addr ad;
	ad.s_addr = pt->saddr;
	printf("\t%s <=> ", inet_ntoa(ad)); //���ԴIP��ַ   inet_ntoa:��ad�ṹ��Ĳ���(ad.s_addr)ת��Ϊ�ַ���
	ad.s_addr = pt->daddr;
	printf("%s,protocol: %hhd,ttl:%hhu,tot_len:%hu\n", inet_ntoa(ad), pt->protocol, pt->ttl, pt->tot_len); //���Ŀ��IP��ַ,
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
		memset(buf, 0x00, sizeof(buf)); //��ջ�����
		int r = read(sfd, buf, 2000);
		if (r <= 0) break;
		struct ethhdr* peth = (struct ethhdr*) buf;
		print_mac(peth);
		//�ж��ϲ�Э��
		if (peth->h_proto == ETH_P_IP) {
			//�ϲ�Э��ΪIP
			parse_ip(buf + sizeof(struct ethhdr));
		}
		else if (peth->h_proto == ETH_P_ARP) {
			//�ϲ�Э��ΪARP
			parse_arp(buf + sizeof(struct ethhdr));
		}
	}
}

