//双指针法:
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* prev = nullptr;  //双指针
		ListNode* cur = head;
		while (cur) {
			ListNode* next = cur->next; //定义临时变量保存下一节点
			cur->next = prev;
			prev = cur;
			cur = next;
		}
		return prev;
	}
};
//递归方法:
class Solution {
public:
	ListNode* reverse(ListNode* cur, ListNode* pre) {
		if (cur == nullptr)  //终止条件
			return pre;
		//递归函数单层处理函数    
		ListNode* next = cur->next;
		cur->next = pre;
		pre = cur;
		cur = next;
		return reverse(cur, pre); //将pre作为头结点一层一层往上return
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
		//利用快慢指针先判断是否有环
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) { //快慢指针相遇表示有环
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

//不带头结点
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		//方法一:不利用头结点
		//要删除的若是头结点,删除更新头结点
		while (head && head->val == val) {
			ListNode* node = head;
			head = head->next;
			delete node;
		}
		//删除非头结点
		ListNode* cur = head;
		while (cur && cur->next) {  //每次判断的都是当前节点的下一节点
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
//带头结点
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		//带头结点
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
		delete newHead; //防止内存泄漏
		return head;
	}
};

class MyLinkedList {
public:
	//定义节点,并初始化
	struct ListNode {
		int val;
		ListNode* next;
		ListNode(int val) :val(val), next(nullptr) {}
	};

	MyLinkedList() {
		_head = new ListNode(0);
		_size = 0;
	}


	int get(int index) { //获取第index个节点的值
		if (index < 0 || index >(_size - 1))  //index从0开始计数
			return -1;
		ListNode* cur = _head->next;
		while (index--) {
			cur = cur->next;
		}
		return cur->val;
	}

	void addAtHead(int val) { //头插
		ListNode* node = new ListNode(val); //创造新节点
		node->next = _head->next;
		_head->next = node;
		_size++; //增加节点个数
	}

	void addAtTail(int val) { //尾插
		ListNode* node = new ListNode(val); //创造节点
		ListNode* cur = _head;
		while (cur->next != nullptr) {
			cur = cur->next;
		}
		cur->next = node;
		_size++;
	}

	void addAtIndex(int index, int val) { //插入
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
	int _size; //链表节点个数
	ListNode* _head; //头结点
};

class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		if (nums.size() < 2)
			return;
		int i = 0;
		int j = 1; //定义两个索引
		while (i < nums.size() && j < nums.size()) {
			if (nums[i] == 0) {
				if (nums[j] != 0) {
					swap(nums[i], nums[j]);
					i++;
				}
			}
			else {
				i++;
			}
			j++;
		}
	}
};

class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() == 0)
			return 0;
		int slow = 0;
		for (int fast = 0; fast < nums.size() - 1; fast++) {
			if (nums[fast] != nums[fast + 1])
				nums[slow++] = nums[fast];
		}
		nums[slow++] = nums[nums.size() - 1];
		return slow;
	}
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
class Solution {
public:
	int maxArea(vector<int>& height) {
		int sz = height.size();
		if (sz < 2)
			return 0;
		int maxCount = 0;
		int i = 0;
		int j = sz - 1;
		while (i < j) {
			int sum = min(height[i], height[j])*(j - i);
			maxCount = sum > maxCount ? sum : maxCount;
			if (height[i] < height[j])
				i++;
			else
				j--;

		}
		return maxCount;
	}
};
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int i = 0;
		int j = nums.size() - 1;
		int l = 0;
		while (i < j && l <= j) {
			if (nums[l] == 2) {
				swap(nums[l], nums[j]);
				j--;
			}
			else if (nums[l] == 0) {
				swap(nums[i], nums[l]);
				i++;
				l++;
			}
			else {
				l++;
			}
		}
	}
};
class Solution {
public:
	int trap(vector<int>& height) {
		int left = 0;
		int right = height.size() - 1;
		int left_max = 0;
		int right_max = 0;
		int ans = 0;
		while (left < right) {
			if (height[left] < height[right]) {
				if (height[left] >= left_max) {
					left_max = height[left];
				}
				else {
					ans += left_max - height[left];
				}
				left++;
			}
			else {
				if (height[right] >= right_max) {
					right_max = height[right];
				}
				else {
					ans += right_max - height[right];
				}
				right--;
			}
		}
		return ans;
	}
};