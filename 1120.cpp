//˫ָ�뷨:
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;  //˫ָ��
		ListNode* cur = head;
		while (cur) {
			ListNode* next = cur->next; //������ʱ����������һ�ڵ�
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		return prev;
	}
};
//�ݹ鷽��:
class Solution {
public:
	ListNode* reverse(ListNode* cur, ListNode* pre) {
		if (cur == nullptr)  //��ֹ����
			return pre;
		//�ݹ麯�����㴦����    
		ListNode* next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
		return reverse(cur, pre); //��pre��Ϊͷ���һ��һ������return
	}
	ListNode* reverseList(ListNode* head) {
		return reverse(head, nullptr);
	}
};

class Solution {
public:
	bool hasCycle(ListNode *head) {
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (fast == slow)
				return true;
		}
		return false;
	}
};

class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		//���ÿ���ָ�����ж��Ƿ��л�
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) { //����ָ��������ʾ�л�
				ListNode* index1 = head;
				ListNode* index2 = slow;
				while (index1 != index2) {
					index1 = index1->next;
					index2 = index2->next;
				}
				return index1;
			}
		}
		return nullptr;
	}
};

//����ͷ���
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		//����һ:������ͷ���
		//Ҫɾ��������ͷ���,ɾ������ͷ���
		while (head && head->val == val) {
			ListNode* node = head;
			head = head->next;
			delete node;
		}
		//ɾ����ͷ���
		ListNode* cur = head;
		while (cur && cur->next) {  //ÿ���жϵĶ��ǵ�ǰ�ڵ����һ�ڵ�
			if (cur->next->val == val) {
				ListNode* tmp = cur->next;
				cur->next = tmp->next;
				delete tmp;
			}
			else
				cur = cur->next;
		}
		return head;
	}
};
//��ͷ���
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		//��ͷ���
		ListNode* newHead = new ListNode(0);
		newHead->next = head;
		ListNode* cur = newHead;
		while (cur && cur->next) {
			if (cur->next->val == val) {
				ListNode* node = cur->next;
				cur->next = node->next;
				delete node;
			}
			else
				cur = cur->next;
		}
		head = newHead->next;
		delete newHead; //��ֹ�ڴ�й©
		return head;
	}
};

class MyLinkedList {
public:
	//����ڵ�,����ʼ��
	struct ListNode {
		int val;
		ListNode* next;
		ListNode(int val) :val(val), next(nullptr) {}
	};

	MyLinkedList() {
		_head = new ListNode(0);
		_size = 0;
	}


	int get(int index) { //��ȡ��index���ڵ��ֵ
		if (index < 0 || index >(_size - 1))  //index��0��ʼ����
			return -1;
		ListNode* cur = _head->next;
		while (index--) {
			cur = cur->next;
		}
		return cur->val;
	}

	void addAtHead(int val) { //ͷ��
		ListNode* node = new ListNode(val); //�����½ڵ�
		node->next = _head->next;
		_head->next = node;
		_size++; //���ӽڵ����
	}

	void addAtTail(int val) { //β��
		ListNode* node = new ListNode(val); //����ڵ�
		ListNode* cur = _head;
		while (cur->next != nullptr) {
			cur = cur->next;
		}
		cur->next = node;
		_size++;
	}

	void addAtIndex(int index, int val) { //����
		ListNode* node = new ListNode(val);
		//if(index == _size)
			//addAtTail(val);
		//if(index < 0)
		  //  addAtHead(val);
		if (index > _size)
			return;
		ListNode* cur = _head;
		while (index--) {
			cur = cur->next;
		}
		node->next = cur->next;
		cur->next = node;
		_size++;
	}

	void deleteAtIndex(int index) { //
		if (index < 0 || index >(_size - 1))
			return;
		/*ListNode* cur = _head;
		while(index--){
			cur = cur->next;
		}
		ListNode* node = cur->next;
		cur->next = cur->next->next;
		delete node;*/
		ListNode* pre = _head;
		ListNode* cur = _head->next;
		while (index--) {
			pre = cur;
			cur = cur->next;
		}
		pre->next = cur->next;
		delete cur;
		_size--;
	}
private:
	int _size; //����ڵ����
	ListNode* _head; //ͷ���
};

class Solution {
public:
	ListNode* partition(ListNode* head, int x) {
		ListNode* h1 = new ListNode(985);
		ListNode* h2 = new ListNode(211);
		ListNode* t1 = h1;
		ListNode* t2 = h2;
		while (head) {
			if (head->val < x) {
				t1->next = head;
				t1 = t1->next;
			}
			else {
				t2->next = head;
				t2 = t1->next;
			}
			head = head->next;
		}
		t2->next = nullptr;
		t1->next = h2->next;
		return h1->next;
	}
};