#include<iostream>
#include<queue>
using namespace std;

#define MAX_RESOURCES_NUM  100      //系统资源的最大种类
#define MAX_PROCESS_NUM  100        //进程的最大数量
queue<int> SecuritySequence;        //保存安全序列的队列

struct SYSTEM                           //定义系统状态，关系为：Need[i][j] = Max[i][j] - Allocation[i][j]
{
	int Finish[MAX_PROCESS_NUM];               //标记进程是否被完成
	int Available[MAX_RESOURCES_NUM];           //可利用资源向量
	int Max[MAX_PROCESS_NUM][MAX_RESOURCES_NUM];         //最大需求矩阵
	int Allocation[MAX_PROCESS_NUM][MAX_RESOURCES_NUM];  //分配矩阵
	int Need[MAX_PROCESS_NUM][MAX_RESOURCES_NUM];        //需求矩阵
};

//判断是否安全
int IsSafe(SYSTEM status, int process_num, int resources_num){
	while (!SecuritySequence.empty())          //清空安全序列
		SecuritySequence.pop();
	for (int i = 0; i < process_num; i++){
		int have_process = 0;               //标记该趟是否可以找到可调度的进程。
		for (int j = 0; j < process_num; j++)
		{
			if (status.Finish[j] == 0)       //进程j未被完成
			{
				int success = 1;            //由于标记系统可分配的各类资源是否满足进程j的需求
				for (int k = 0; k < resources_num; k++)      //检查系统可分配的各类资源是否满足进程j的需求
				{
					if (status.Available[k] < status.Need[j][k])     //系统有一类资源不满足进程需求
					{
						success = 0;
						break;
					}
				}
				if (success == 1)             //系统所有类资源都满足进程需求,调度进程 j ，运行完成 j ，并回收资源。
				{
					have_process = 1;                           //已找到可调度的进程
					status.Finish[j] = 1;                          //标记进程 j 已完成
					for (int l = 0; l < resources_num; l++)      //回收各类资源
					{
						status.Available[l] += status.Allocation[j][l];
					}
					SecuritySequence.push(j);                   //进程 j 入队保存
				}
			}
		}
		if (have_process == 0){                                   //没有可调度的进程跳出；
			break;
		}
	}
	int is_safe = 1;
	for (int i = 0; i < process_num; i++){                //判断所有进程是否以完成，如果已完成则存在安全序列，否则，不存在；
		if (status.Finish[i] == 0)                       //有进程未被调度，所有不存在安全序列；
			is_safe = 0;
	}
	return is_safe;
}

//银行家算法
int  BankerAlgorithm(SYSTEM status, int process_num, int resources_num, int process, int Request[]){
	for (int i = 0; i < resources_num; i++){          //判断需求资源是否大于最大需求
		if (Request[i] > status.Need[process][i])    {
			cout << "需求资源大于最大需求" << endl;
			return 0;
		}
	}
	for (int i = 0; i < resources_num; i++){             //需求资源是否大于可分配资源
		if (Request[i] > status.Available[i]){
			cout << "需求资源大于可分配资源" << endl;
			return 0;
		}
	}
	//满足分配要求
	for (int i = 0; i < resources_num; i++){
		status.Available[i] -= Request[i];
		status.Allocation[process][i] += Request[i];
		status.Need[process][i] -= Request[i];
	}
	//判断是否存在安全序列
	if (IsSafe(status, process_num, resources_num)){
		printf("存在安全序列：\n");
		while (!SecuritySequence.empty()){            //输出安全序列
			cout << SecuritySequence.front() << endl;
			SecuritySequence.pop();
		}
		return 1;
	}
	else{//没有安全序列
		cout << "不存在安全序列，不分配资源" << endl;
		for (int i = 0; i < resources_num; i++){
			status.Available[i] += Request[i];
			status.Allocation[process][i] -= Request[i];
			status.Need[process][i] += Request[i];
			return 0;
		}
	}
	return 0;
}

//输出系统状态
void display(SYSTEM status, int process_num, int resources_num)
{
	//系统状态Available
	cout << "系统状态Available：" << endl;
	for (int i = 0; i < resources_num; i++)
		cout << status.Available[i] << " ";
	cout << endl;
	//系统状态最大需求矩阵Max
	cout << "请初始化系统状态最大需求矩阵Max：" << endl;
	for (int i = 0; i < process_num; i++)
	{
		for (int j = 0; j < resources_num; j++)
		{
			cout << status.Max[i][j] << " ";
		}
		cout << endl;
	}
	//系统状态最大需求矩阵Allocation
	cout << "可利用资源向量Allocation：" << endl;
	for (int i = 0; i < process_num; i++)
	{
		for (int j = 0; j < resources_num; j++)
		{
			cout << status.Allocation[i][j] << " ";
		}
		cout << endl;
	}
	//需求矩阵Need
	cout << "需求矩阵Need" << endl;
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			cout << status.Need[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	SYSTEM status;      //定义系统状态
	int resources_num, process_num;      //定义资源数，进程数
	cout << "请初始化进程数，和资源种数：" << endl;
	cin >> process_num >> resources_num;
	cout << "请初始化系统状态Available：" << endl;
	for (int i = 0; i < resources_num; i++)
		cin >> status.Available[i];
	//初始化系统状态最大需求矩阵Max
	cout << "请初始化系统状态最大需求矩阵Max：" << endl;
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			cin >> status.Max[i][j];
		}
	}
	//初始化系统状态最大需求矩阵Allocation
	cout << "请初始化可利用资源向量Allocation：" << endl;
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			cin >> status.Allocation[i][j];
		}
	}
	//自动处理需求矩阵Need
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			status.Need[i][j] = status.Max[i][j] - status.Allocation[i][j];
		}
	}
	int process;                        //记录资源请求的进程的号
    int Request[MAX_RESOURCES_NUM];     //记录该进程对各资源请求的数量
	if (IsSafe(status, process_num, resources_num) == 0){
		cout << "初始状态不存在安全序列" << endl;
		return 0;
	}
	else{
		cout << "初始状态安全" << endl;
		cout << "存在安全序列：" << endl;
		while (!SecuritySequence.empty()){            //输出安全序列{
			cout << SecuritySequence.front() << " ";
			SecuritySequence.pop();
		}
		cout << endl;
	}
	return 0;
}