#ifndef Fibq
#define Fibq
#include<iostream>

struct FibNode {
  FibNode *left, *right, *parent, *descendant;
  int data = 0;
  bool marked;
  int degree = 0;

  FibNode()
      : left(this),
        right(this),
        parent(nullptr),
        descendant(nullptr),
        degree(0),
        marked(false),
        data(0){};

  FibNode(int data_)
      : left(this),
        right(this),
        parent(nullptr),
        descendant(nullptr),
        degree(0),
        marked(false),
        data(data_){};
};

class FibHeap {
  FibNode* min;
  int size;

 public:
  FibHeap() : min(nullptr), size(0){};

  FibHeap(int size_) : min(nullptr), size(size_){};
  ~FibHeap() { clear(min); }

  int get_min() const { return min->data; }

  void clear(FibNode* now) {
    if (now != nullptr) {
      FibNode* now1 = now;
      FibNode* now2 = nullptr;
      do {
        now2 = now1;
        now1 = now1->right;
        clear(now2->descendant);
        delete now2;
        now2 = nullptr;
      } while (now1 != nullptr);
    }
  }

  FibNode* insert(int value) {
    FibNode* tmp = new FibNode(value);
    if (size == 0) {
      min = tmp;
      min->left = tmp;
      min->right = tmp;
      ++size;
      return min;
    }
    merge(min, tmp);
    if (tmp->data < min->data) {
      min = tmp;
    }
    ++size;
    return tmp;
  }

  static bool separating_from_parent(FibNode* x) {
    if (x == nullptr) {
      return false;
    }
    FibNode* now = x;
    do {
      now->parent = nullptr;
      now = now->right;
    } while (now != x);
    return true;
  }

  FibNode* extract_min() {
    FibNode* prev_min = min;
    if (prev_min == nullptr || size == 0) {
      return nullptr;
    }
    separating_from_parent(min->descendant);
    merge(min, min->descendant);
    if (prev_min->right == prev_min) {
      min = nullptr;
    } else {
      min = min->right;
    }
    remove_from_list(prev_min);
    if (min != nullptr) {
      consolidate();
    }
    --size;
    return prev_min;
  }

  static void remove_from_list(FibNode* x) {
    x->left->right = x->right;
    x->right->left = x->left;
    x->right = x->left = x;
  }

  static FibNode* merge(FibNode* first, FibNode* second) {
    if (first == nullptr) {
      return second;
    }
    if (second == nullptr) {
      return first;
    }
    if (second == first) {
      return first;
    }
    if (second->data < first->data) {
      std::swap(first, second);
    }
    FibNode* first_left = first->left;
    FibNode* second_right = second->right;
    second->right = first;
    first->left = second;
    second_right->left = first_left;
    first_left->right = second_right;
    return first;
  }

  void consolidate() {
    FibNode** A = new FibNode*[size / 2 + 3];
    for (int i = 0; i < size / 2 + 3; ++i) {
      A[i] = nullptr;
    }
    A[min->degree] = min;
    FibNode* x = min->right;
    FibNode* x_prev = nullptr;
    int d = x->degree;

    while (A[d] != x) {
      x_prev = x;

      if (A[d] != nullptr) {
        FibNode* y = A[d];
        if (y->data < x->data) {
          remove_from_list(x);
          merge(y->descendant, x);
          y->descendant = x;
          x->parent = y;
          ++y->degree;
          x->marked = false;
          x = y;
        } else {
          remove_from_list(y);
          merge(x->descendant, y);
          x->descendant = y;
          y->parent = x;
          ++x->degree;
          y->marked = false;
        }
        A[d] = nullptr;
      } else {
        A[d] = x;
        x = x->right;
      }
      if (x_prev->data < min->data) {
        min = x_prev;
      }
      d = x->degree;
    }
    delete[] A;
  }

  void decrease_key(FibNode* x, int new_data) {
    x->data = new_data;
    FibNode* y = x->parent;
    if (y != nullptr && x->data < y->data) {
      cut(x, y);
      cascading_cut(y);
    }
    if (x->data < min->data) {
      min = x;
    }
  }

  void cut(FibNode* x, FibNode* y) {
    if (x == y) {
      return;
    }
    if (x == x->right) {
      y->descendant = nullptr;
    } else {
      y->descendant = x->right;
    }
    remove_from_list(x);
    if (y != nullptr && y->degree > 0) {
      --y->degree;
    }
    min = merge(min, x);
    x->marked = false;
  }

  void cascading_cut(FibNode* y) {
    FibNode* z = y->parent;
    if (z != nullptr) {
      if (!y->marked) {
        y->marked = true;
      } else {
        cut(y, z);
        cascading_cut(z);
      }
    }
  }
};
#endif
