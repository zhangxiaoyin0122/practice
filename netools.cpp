#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


enum {
	BEGIN,
	MYIFCONF,
	SCANHOST,
	SCANPORT,
	SHARK,
	DOS,
	QUIT,
	END
};

struct proc_map {
	int id;
	char* proc_name;
}maps[] = {
	{BEGIN,NULL},
	{MYIFCONF, "./myifconfig"},
	{SCANHOST, "./scanhost"},
	{SCANPORT, "./scanport"},
	{SHARK,    "./shark"},
	{DOS,      "./dos"},
	{END,      NULL}
};

//网络小工具菜单栏
int menu() {
	int choose;
	do {
		system("clear");
		printf("\n\n\n\n\n");
		printf("\t\t\t\t网络小工具\n");
		printf("\t\t###########################################\n");
		printf("\t\t# %d. myifconfig                           #\n", MYIFCONF);
		printf("\t\t# %d. scanhost                             #\n", SCANHOST);
		printf("\t\t# %d. scanport                             #\n", SCANPORT);
		printf("\t\t# %d. shark                                #\n", SHARK);
		printf("\t\t# %d. dos                                  #\n", DOS);
		printf("\t\t# %d. quit                                 #\n", QUIT);
		printf("\t\t###########################################\n");
		printf("\t\t> ");
		scanf("%d%*c", &choose);
		if (choose <= BEGIN || choose >= END) {
			printf("菜单选择有误,是否重新输入?[y/n]:\n");
			char c;
			scanf("%c", &c);
			if (c == 'y')
				continue;
			exit(0);
		}
		else {
			break;
		}
	} while (1);
	return choose;
}
//程序退出
void do_quit() {
	printf("谢谢退出\n");
	exit(0);
}

void do_proc(int choose) {
	int i;
	for (i = BEGIN; i < END; i++) {
		if (choose == i) {
			if (fork() == 0) {
				sigset_t set;
				sigemptyset(&set);
				sigaddset(&set, SIGINT);
				sigprocmask(SIG_UNBLOCK, &set, NULL);

				execlp(maps[i].proc_name, maps[i].proc_name, NULL);
				perror("execlp");
				exit(0);
			}
			else {
				wait(NULL);
			}
		}
	}
}
int main(void) {
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);

	while (1) {
		int choice = menu();
		switch (choice) {
		case QUIT:
			do_quit();
			break;
		default:
			do_proc(choice);
			break;
		}
	}
}
