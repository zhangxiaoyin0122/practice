#include <iostream>
#include <vector>
using namespace std;
//每日三道oj题:最大子序列 (贪心算法求最优解)

(一)
class Solution {
public:
	int maxsumofSubarray(vector<int>& arr) {
		int result = 0; //保存结果
		if (arr.size() == 1)
			return arr[0];
		int path = arr[0];
		for (int i = 1; i < arr.size(); i++) {
			if (path < 0) {
				path = arr[i];
			}
			else {
				path += arr[i];
			}
			result = result > path ? result : path;
		}
		return result;
	}
};

(二)
#include <iostream>
#include <string>
using namespace std;

int main() {
		string str = "123abc123456abc";
		//while (getline(cin, str)) {//接收一行字符串 abcd123hgf123456hffd   
		int i = 0;
		string ans; //保存输出结果
		int size = str.size();
		while (i < size) {
			string path = "";
			if (str[i] >= '0' && str[i] <= '9') {	
				path += str[i];
				while (i + 1 < str.size() && (str[i + 1] >= '0' && str[i + 1] <= '9')) {
					path += str[i + 1];
					i++;
				}
				i++;
				if (path.size() > ans.size()) {
					ans = path;
				}
			}
			else {
				i++;
			}
		}
		cout << ans << endl;
	return 0;
}
(三)

class Solution {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		if (numbers.empty())
			return 0;
		int size = numbers.size();
		int count = numbers[0];
		int time = 1;
		for (int i = 1; i < size; i++) {
			if (time == 0) {
				count = numbers[i];
				time = 0;
			}
			if (numbers[i] == count) {
				time++;
			}
			else {
				time--;
			}
		}
		time = 0;
		for (int i = 0; i < size; i++) {
			if (count == numbers[i]) {
				time++;
			}
		}
		int half = size / 2;
		return time > half ? count : 0;
	}
};

//linux知识相关代码:

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

//定义互斥量
pthread_mutex_t mutex;
int tickets = 100;
//线程回调函数
void* routine(void* arg) {
	while (1) {
		//上锁
		pthread_mutex_lock(&mutex);
		if (tickets > 0) {
			printf("哈哈哈哈  我抢到%d号票了~~\n", tickets);
			tickets--;
			usleep(1000); //睡眠1000微秒,也是一毫秒
			//解锁
			pthread_mutex_unlock(&mutex);
		}
		else {
			//解锁
			pthread_mutex_unlock(&mutex);
			//退出线程
			pthread_exit(NULL);
		}
	}
}

int main() {
	pthread_t tid[4];
	//互斥量初始化
	pthread_mutex_init(&mutex, NULL);
	int i;
	//创建4个线程
	for (i = 0; i < 4; i++) {
		pthread_create(&tid[i], NULL, routine, NULL);
	}

	//线程等待
	for (i = 0; i < 4; i++) {
		pthread_join(tid[i], NULL);
	}
	//互斥量的销毁
	pthread_mutex_destroy(&mutex);
	return 0;
}

//发送信息端
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define IPC_KEY 0x123456
int main() {
	//创建共享内存
	int shmid = shmget(IPC_KEY, 32, IPC_CREAT | 0664);
	if (shmid == -1) {
		perror("shmget failed\n");
		exit(0);
	}

	//将共享内存映射到虚拟内存
	void* start_shm = shmat(shmid, NULL, 0);
	if (start_shm == (void*)-1) {
		perror("shmat failed\n");
		exit(0);
	}
	int i = 0;
	while (1) {
		sprintf(start_shm, "鱼塘%d号", i++);
		sleep(1);
	}

	//解除映射
	shmdt(start_shm);
	//删除共享内存
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define IPC_KEY 0x123456
int main() {
	//创建/打开共享内存
	int shmid = shmget(IPC_KEY, 32, IPC_CREAT | 0664);
	if (shmid == -1) {
		perror("shmget failed\n");
		exit(0);
	}
	//将共享内存映射到自己的地址空间
	void* start_shm = shmat(shmid, NULL, 0);
	if (start_shm == (void*)-1) {
		perror("shmat failed\n");
		exit(0);
	}
	while (1) {
		printf("%s\n", (char*)start_shm);
		sleep(1);
	}
	//解除映射
	shmdt(start_shm);
	//删除共享内存
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
