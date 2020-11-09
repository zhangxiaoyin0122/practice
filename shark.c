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
//����IPЭ��
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
 //test.c

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
