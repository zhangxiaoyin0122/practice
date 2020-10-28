//1~n中1的个数
class Solution {
public:
	int countDigitOne(int n) {
		int count = 0;
		long i = 1;
		while (n / i) {
			long high = n / (10 * i);    //获取高位
			long cur = (n / i) % 10;     //获取当前位
			long low = n - (n / i)*i;    //获取低位
			if (cur == 0) { //当前位为0
				count += high * i;
			}
			else if (cur == 1) { //当前位为1
				count += high * i + low + 1;
			}
			else { //当前位大于1
				count += high * i + i;
			}
			i *= 10;
		}
		return count;
	}
};
//子数组最大连续和
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int tmp = nums[0];
		int result = tmp;
		for (int i = 1; i < nums.size(); i++) {
			if (tmp <= 0) {
				tmp = nums[i];
			}
			else {
				tmp += nums[i];
			}
			if (tmp > result)
				result = tmp;
		}
		return result;
	}
};
//二叉树路径满sum的全部路径
class Solution {
public:
	vector<vector<int> > result;
	vector<int> path;
	void backtraving(TreeNode* root, int sum) {
		path.push_back(root->val);
		if (root->val == sum && root->left == nullptr && root->right == nullptr) {
			result.push_back(path);
		}
		if (root->left) {
			backtraving(root->left, sum - (root->val));
			path.pop_back();
		}
		if (root->right) {
			backtraving(root->right, sum - (root->val));
			path.pop_back();
		}
	}
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		if (root == nullptr)
			return result;
		backtraving(root, sum);
		return result;
	}
};
//树的子结构
class Solution {
public:
	//判断两棵树是否相等
	bool IsSame(TreeNode* A, TreeNode* B) {
		if (A == nullptr || B == nullptr)
			return B == nullptr ? true : false;
		if (A->val != B->val)
			return false;
		return IsSame(A->left, B->left) && IsSame(A->right, B->right);
	}
	bool isSubStructure(TreeNode* A, TreeNode* B) {
		//两个结点相等,再判断其子树是否相等
		if (A == nullptr || B == nullptr)
			return false;
		return IsSame(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
	}
};
//同构字符串:
class Solution {
public:
	bool isIsomorphic(string s, string t) {
		if (s.size() != t.size())
			return false;
		for (int i = 0; i < s.size(); i++) {
			if (s.find(s[i]) != t.find(t[i]))
				return false;
		}
		return true;
	}
};

class Solution {
public:
	bool IsZhishu(int n) {
		if (n == 2)
			return true;
		for (int i = 2; i < n; i++) {
			if (n%i == 0)
				return false;
		}
		return true;
	}
	int countPrimes(int n) {
		int count = 0;
		for (int i = 2; i < n; i++) {
			if (IsZhishu(i))
				count++;
		}
		return count;
	}
};
//一个进程fork出两个子进程
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i;
	printf("this is parent: %d\n", getpid());
	for (i = 0; i < 2; i++) {
		if (fork() == 0) {
			printf("this is child%d: %d\n", i + 1, getpid());
			break;
		}
	}
}
//实现管道全双工通信
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main(void) {
	pid_t pid;
	int fds1[2];
	int fds2[2];
	pipe(fds1);
	pipe(fds2); //创建两个管道实现全双工通信
	int x = 1;
	pid = fork();
	int i;
	if (pid == 0) { //子进程
		close(fds1[1]); //关闭管道1的写端
		close(fds2[0]); //关闭管道2的读端
		for (i = 0; i < 5; i++) {
			read(fds1[0], &x, sizeof(int));
			printf("child %d read: %d\n", getpid(), x++);
			write(fds2[1], &x, sizeof(int));
		}
		close(fds1[0]);
		close(fds2[1]);
	}
	else { //父进程
		close(fds1[0]); //关闭管道1的读端
		close(fds2[1]); //关闭管道2的写端
		for (i = 0; i < 5; i++) {
			write(fds1[1], &x, sizeof(int));
			read(fds2[0], &x, sizeof(int));
			printf("parent %d read %d\n", getpid(), x++);
		}
		close(fds1[1]);
		close(fds2[0]);
	}
}

//消息队列
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
void handler(int s) {
	int msgid = msgget(1234, 0);
	int id = msgctl(msgid, IPC_RMID, NULL);
	if (id == -1)
		perror("msgctl"), exit(1);
}

struct msgbuf {
	long channel;
	char buf[100];
};
int main(void) {
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGCHLD, &act, NULL);

	pid_t pid;
	pid = fork();
	if (pid == 0) { //子进程
		//sleep(1);
		int msgid = msgget(1234, 0);
		if (msgid == -1)
			perror("msgget"), exit(1);
		struct msgbuf mb;
		memset(&mb, 0x00, sizeof(mb));
		int id = msgrcv(msgid, &mb, 100, 5, 0);
		if (id == -1)
			perror("msgrcv"), exit(1);
		printf("Child:Receiving from the message queue: %s\n", mb.buf);

	}
	else {  //父进程
		int msgid = msgget(1234, IPC_CREAT | 0664);
		if (msgid == -1)
			perror("msgget"), exit(1);
		struct msgbuf mb;
		memset(&mb, 0x00, sizeof(mb));
		mb.channel = 5;
		strcpy(mb.buf, "This is the input!");
		int id = msgsnd(msgid, &mb, strlen(mb.buf), 0);
		if (id == -1)
			perror("msgsnd"), exit(1);
		printf("Parent:Send to the message queue successfully!\n");
		printf("The message sent is : %s\n", mb.buf);
	}

}
