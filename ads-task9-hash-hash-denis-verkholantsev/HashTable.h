
#include<cmath>
class HashTable
{
	struct HashNode {
		HashNode* next;
		int data;
		HashNode(int x) : data(x), next(nullptr) {};
		~HashNode() {
			delete next;
		}
	};
	HashNode** arr;
	int size;
public:
	HashTable() : size(4096) {
		arr = new HashNode*[size];
		for (int i = 0; i < size; ++i) {
			arr[i] = nullptr;
		}
	}
	HashTable(int size_) : size(size_){
		arr = new HashNode*[size];
		for (int i = 0; i < size; ++i) {
			arr[i] = nullptr;
		}
	}
	~HashTable() {
		for (int i = 0; i < size; ++i) {
			delete arr[i];
		}
		delete[] arr;
	}
	void insert(int x) {
		int ind = abs(x) % size;
		if (arr[ind] != nullptr) {
			HashNode* now = arr[ind];
			while (now->next != nullptr) {
				now = now->next;
			}
			now->next = new HashNode(x);
		}
		else {
			arr[ind] = new HashNode(x);
		}
	}

	bool search(int x) {
		int ind = abs(x) % size;
		if (arr[ind] != nullptr) {
			HashNode* now = arr[ind];
			while (now->next != nullptr && x != now->data) {
				now = now->next;
			}
			if (x != now->data) {
				return x != now->data;
			}
			return true;
		}
		return false;
	}

	bool remove(int x) {
		int ind = abs(x) % size;
		if (arr[ind] != nullptr) {
			HashNode* now = arr[ind];
			HashNode* parent = now;
			while (now->next != nullptr && x != now->data) {
				parent = now;
				now = now->next;
			}
			if (x != now->data) {
				return false;
			}
			if (parent == now) {
				if (parent->next == nullptr) {
					delete now;
					arr[ind] = nullptr;
					return true;
				}
				arr[ind] = now->next;
				now->next = nullptr;
				delete now;
				return true;
			}
			parent->next = now->next;
			now->next = nullptr;
			delete now;
			now = nullptr;
			return true;
		}
		return false;
	}
	
};

