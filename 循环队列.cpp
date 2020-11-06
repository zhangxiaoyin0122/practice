//��һ��ʵ�ַ�ʽ
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int front;
	int rear;
	int* array;
	int size;
	int k;
} MyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue* mq = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
	mq->array = (int*)malloc(sizeof(int)*k);
	mq->front = mq->rear = 0;
	mq->size = 0;
	mq->k = k;
	return mq;
}

//����Ԫ��
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	//�ж϶����Ƿ�Ϊ��
	if (obj->size == obj->k)
		return false;
	obj->array[obj->rear++] = value;
	if (obj->rear == obj->k)
		obj->rear = 0;
		obj->size++;
	return true;
}

//ɾ��Ԫ��
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	if (obj->size == 0) {
		return false;
	}
	++obj->front;
	if (obj->front == obj->k) {
		obj->front = 0;
	}
	--obj->size;
	return true;
}

//��ȡ����Ԫ��
int myCircularQueueFront(MyCircularQueue* obj) {
	if (obj->size == 0)
		return -1;
	return obj->array[obj->front];
}

//��ȡ��βԪ��
int myCircularQueueRear(MyCircularQueue* obj) {
	if (obj->size == 0)
		return -1;
	if (obj->rear == 0)
		return obj->array[obj->k - 1];
	return obj->array[obj->rear - 1];
}
//�ж϶����Ƿ�Ϊ��
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	if (obj->size == 0)
		return true;
	return false;
}

//�ж϶����Ƿ�����
bool myCircularQueueIsFull(MyCircularQueue* obj) {
	if (obj->size == obj->k)
		return true;
	return false;
}
//��������
void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->array);
	free(obj);
}

//�ڶ���ʵ�ַ�ʽ

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct {
	int front;
	int rear;
	int* array;
	//int size;
	int k;
} MyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue* mq = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
	mq->array = (int*)malloc(sizeof(int)*(k + 1));
	mq->front = mq->rear = 0;
	//mq->size = 0;
	mq->k = k;
	return mq;
}

//����Ԫ��
bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
	//�ж϶����Ƿ�Ϊ��
	if ((obj->rear + 1) % (obj->k + 1) == obj->front)
		return false;
	//β��
	obj->array[obj->rear++] = value;
	if (obj->rear == obj->k + 1)
		obj->rear = 0;
	//obj->size++;
	return true;
}

//ɾ��Ԫ��
bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	if (obj->front == obj->rear) {
		return false;
	}
	++obj->front;
	if (obj->front == obj->k + 1) {
		obj->front = 0;
	}
	//--obj->size;
	return true;
}

//��ȡ����Ԫ��
int myCircularQueueFront(MyCircularQueue* obj) {
	if (obj->front == obj->rear)
		return -1;
	return obj->array[obj->front];
}

//��ȡ��βԪ��
int myCircularQueueRear(MyCircularQueue* obj) {
	if (obj->front == obj->rear)
		return -1;
	if (obj->rear == 0)
		return obj->array[obj->k - 1];
	return obj->array[obj->rear - 1];
}
//�ж϶����Ƿ�Ϊ��
bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	if (obj->front == obj->rear)
		return true;
	return false;
}

//�ж϶����Ƿ�����
bool myCircularQueueIsFull(MyCircularQueue* obj) {
	if ((obj->rear + 1) % (obj->k + 1) == obj->front)
		return true;
	return false;
}
//��������
void myCircularQueueFree(MyCircularQueue* obj) {
	free(obj->array);
	free(obj);
}