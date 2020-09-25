#include<iostream>
#include<queue>
using namespace std;

#define MAX_RESOURCES_NUM  100      //ϵͳ��Դ���������
#define MAX_PROCESS_NUM  100        //���̵��������
queue<int> SecuritySequence;        //���氲ȫ���еĶ���

struct SYSTEM                           //����ϵͳ״̬����ϵΪ��Need[i][j] = Max[i][j] - Allocation[i][j]
{
	int Finish[MAX_PROCESS_NUM];               //��ǽ����Ƿ����
	int Available[MAX_RESOURCES_NUM];           //��������Դ����
	int Max[MAX_PROCESS_NUM][MAX_RESOURCES_NUM];         //����������
	int Allocation[MAX_PROCESS_NUM][MAX_RESOURCES_NUM];  //�������
	int Need[MAX_PROCESS_NUM][MAX_RESOURCES_NUM];        //�������
};

//�ж��Ƿ�ȫ
int IsSafe(SYSTEM status, int process_num, int resources_num){
	while (!SecuritySequence.empty())          //��հ�ȫ����
		SecuritySequence.pop();
	for (int i = 0; i < process_num; i++){
		int have_process = 0;               //��Ǹ����Ƿ�����ҵ��ɵ��ȵĽ��̡�
		for (int j = 0; j < process_num; j++)
		{
			if (status.Finish[j] == 0)       //����jδ�����
			{
				int success = 1;            //���ڱ��ϵͳ�ɷ���ĸ�����Դ�Ƿ��������j������
				for (int k = 0; k < resources_num; k++)      //���ϵͳ�ɷ���ĸ�����Դ�Ƿ��������j������
				{
					if (status.Available[k] < status.Need[j][k])     //ϵͳ��һ����Դ�������������
					{
						success = 0;
						break;
					}
				}
				if (success == 1)             //ϵͳ��������Դ�������������,���Ƚ��� j ��������� j ����������Դ��
				{
					have_process = 1;                           //���ҵ��ɵ��ȵĽ���
					status.Finish[j] = 1;                          //��ǽ��� j �����
					for (int l = 0; l < resources_num; l++)      //���ո�����Դ
					{
						status.Available[l] += status.Allocation[j][l];
					}
					SecuritySequence.push(j);                   //���� j ��ӱ���
				}
			}
		}
		if (have_process == 0){                                   //û�пɵ��ȵĽ���������
			break;
		}
	}
	int is_safe = 1;
	for (int i = 0; i < process_num; i++){                //�ж����н����Ƿ�����ɣ�������������ڰ�ȫ���У����򣬲����ڣ�
		if (status.Finish[i] == 0)                       //�н���δ�����ȣ����в����ڰ�ȫ���У�
			is_safe = 0;
	}
	return is_safe;
}

//���м��㷨
int  BankerAlgorithm(SYSTEM status, int process_num, int resources_num, int process, int Request[]){
	for (int i = 0; i < resources_num; i++){          //�ж�������Դ�Ƿ�����������
		if (Request[i] > status.Need[process][i])    {
			cout << "������Դ�����������" << endl;
			return 0;
		}
	}
	for (int i = 0; i < resources_num; i++){             //������Դ�Ƿ���ڿɷ�����Դ
		if (Request[i] > status.Available[i]){
			cout << "������Դ���ڿɷ�����Դ" << endl;
			return 0;
		}
	}
	//�������Ҫ��
	for (int i = 0; i < resources_num; i++){
		status.Available[i] -= Request[i];
		status.Allocation[process][i] += Request[i];
		status.Need[process][i] -= Request[i];
	}
	//�ж��Ƿ���ڰ�ȫ����
	if (IsSafe(status, process_num, resources_num)){
		printf("���ڰ�ȫ���У�\n");
		while (!SecuritySequence.empty()){            //�����ȫ����
			cout << SecuritySequence.front() << endl;
			SecuritySequence.pop();
		}
		return 1;
	}
	else{//û�а�ȫ����
		cout << "�����ڰ�ȫ���У���������Դ" << endl;
		for (int i = 0; i < resources_num; i++){
			status.Available[i] += Request[i];
			status.Allocation[process][i] -= Request[i];
			status.Need[process][i] += Request[i];
			return 0;
		}
	}
	return 0;
}

//���ϵͳ״̬
void display(SYSTEM status, int process_num, int resources_num)
{
	//ϵͳ״̬Available
	cout << "ϵͳ״̬Available��" << endl;
	for (int i = 0; i < resources_num; i++)
		cout << status.Available[i] << " ";
	cout << endl;
	//ϵͳ״̬����������Max
	cout << "���ʼ��ϵͳ״̬����������Max��" << endl;
	for (int i = 0; i < process_num; i++)
	{
		for (int j = 0; j < resources_num; j++)
		{
			cout << status.Max[i][j] << " ";
		}
		cout << endl;
	}
	//ϵͳ״̬����������Allocation
	cout << "��������Դ����Allocation��" << endl;
	for (int i = 0; i < process_num; i++)
	{
		for (int j = 0; j < resources_num; j++)
		{
			cout << status.Allocation[i][j] << " ";
		}
		cout << endl;
	}
	//�������Need
	cout << "�������Need" << endl;
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			cout << status.Need[i][j] << " ";
		}
		cout << endl;
	}
}

int main(){
	SYSTEM status;      //����ϵͳ״̬
	int resources_num, process_num;      //������Դ����������
	cout << "���ʼ��������������Դ������" << endl;
	cin >> process_num >> resources_num;
	cout << "���ʼ��ϵͳ״̬Available��" << endl;
	for (int i = 0; i < resources_num; i++)
		cin >> status.Available[i];
	//��ʼ��ϵͳ״̬����������Max
	cout << "���ʼ��ϵͳ״̬����������Max��" << endl;
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			cin >> status.Max[i][j];
		}
	}
	//��ʼ��ϵͳ״̬����������Allocation
	cout << "���ʼ����������Դ����Allocation��" << endl;
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			cin >> status.Allocation[i][j];
		}
	}
	//�Զ������������Need
	for (int i = 0; i < process_num; i++){
		for (int j = 0; j < resources_num; j++){
			status.Need[i][j] = status.Max[i][j] - status.Allocation[i][j];
		}
	}
	int process;                        //��¼��Դ����Ľ��̵ĺ�
    int Request[MAX_RESOURCES_NUM];     //��¼�ý��̶Ը���Դ���������
	if (IsSafe(status, process_num, resources_num) == 0){
		cout << "��ʼ״̬�����ڰ�ȫ����" << endl;
		return 0;
	}
	else{
		cout << "��ʼ״̬��ȫ" << endl;
		cout << "���ڰ�ȫ���У�" << endl;
		while (!SecuritySequence.empty()){            //�����ȫ����{
			cout << SecuritySequence.front() << " ";
			SecuritySequence.pop();
		}
		cout << endl;
	}
	return 0;
}