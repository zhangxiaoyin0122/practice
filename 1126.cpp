#include <iostream>
#include <vector>
using namespace std;
//ÿ������oj��:��������� (̰���㷨�����Ž�)

(һ)
class Solution {
public:
	int maxsumofSubarray(vector<int>& arr) {
		int result = 0; //������
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

(��)
#include <iostream>
#include <string>
using namespace std;

int main() {
		string str = "123abc123456abc";
		//while (getline(cin, str)) {//����һ���ַ��� abcd123hgf123456hffd   
		int i = 0;
		string ans; //����������
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
(��)

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

//linux֪ʶ��ش���:

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

//���廥����
pthread_mutex_t mutex;
int tickets = 100;
//�̻߳ص�����
void* routine(void* arg) {
	while (1) {
		//����
		pthread_mutex_lock(&mutex);
		if (tickets > 0) {
			printf("��������  ������%d��Ʊ��~~\n", tickets);
			tickets--;
			usleep(1000); //˯��1000΢��,Ҳ��һ����
			//����
			pthread_mutex_unlock(&mutex);
		}
		else {
			//����
			pthread_mutex_unlock(&mutex);
			//�˳��߳�
			pthread_exit(NULL);
		}
	}
}

int main() {
	pthread_t tid[4];
	//��������ʼ��
	pthread_mutex_init(&mutex, NULL);
	int i;
	//����4���߳�
	for (i = 0; i < 4; i++) {
		pthread_create(&tid[i], NULL, routine, NULL);
	}

	//�̵߳ȴ�
	for (i = 0; i < 4; i++) {
		pthread_join(tid[i], NULL);
	}
	//������������
	pthread_mutex_destroy(&mutex);
	return 0;
}

//������Ϣ��
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define IPC_KEY 0x123456
int main() {
	//���������ڴ�
	int shmid = shmget(IPC_KEY, 32, IPC_CREAT | 0664);
	if (shmid == -1) {
		perror("shmget failed\n");
		exit(0);
	}

	//�������ڴ�ӳ�䵽�����ڴ�
	void* start_shm = shmat(shmid, NULL, 0);
	if (start_shm == (void*)-1) {
		perror("shmat failed\n");
		exit(0);
	}
	int i = 0;
	while (1) {
		sprintf(start_shm, "����%d��", i++);
		sleep(1);
	}

	//���ӳ��
	shmdt(start_shm);
	//ɾ�������ڴ�
	shmctl(shmid, IPC_RMID, NULL);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define IPC_KEY 0x123456
int main() {
	//����/�򿪹����ڴ�
	int shmid = shmget(IPC_KEY, 32, IPC_CREAT | 0664);
	if (shmid == -1) {
		perror("shmget failed\n");
		exit(0);
	}
	//�������ڴ�ӳ�䵽�Լ��ĵ�ַ�ռ�
	void* start_shm = shmat(shmid, NULL, 0);
	if (start_shm == (void*)-1) {
		perror("shmat failed\n");
		exit(0);
	}
	while (1) {
		printf("%s\n", (char*)start_shm);
		sleep(1);
	}
	//���ӳ��
	shmdt(start_shm);
	//ɾ�������ڴ�
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
