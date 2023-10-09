
class AATree {
  struct node {
    int data;
    int level;
    node* left;
    node* right;
    node() : data(0), level(1), left(nullptr), right(nullptr){};
    node(int x) : data(x), level(1), left(nullptr), right(nullptr){};
    ~node() {
      delete left;
      delete right;
      left = right = nullptr;
    }
  };
  node* root = nullptr;

 public:
  AATree() : root(nullptr){};

  ~AATree() {
    delete root;
    root = nullptr;
  }

  node* operator*() { return root; }

  int balance() const { return root != nullptr ? root->level : 0; }

  bool search(int x) {
    node* now = root;
    while (now != nullptr) {
      if (x < now->data) {
        now = now->left;
      } else if (x > now->data) {
        now = now->right;
      } else {
        return true;
      }
    }
    return false;
  }

  static node* skew(node* X) {
    if (X == nullptr) {
      return nullptr;
    }
    if (X->left == nullptr) {
      return X;
    }
    node* tmp;
    if (X->left->level == X->level) {
      tmp = X->left;
      X->left = tmp->right;
      tmp->right = X;
      return tmp;
    }
    return X;
  }

  node* split(node* X) {
    if (X == nullptr) {
      return nullptr;
    }
    if (X->right == nullptr || X->right->right == nullptr) {
      return X;
    }
    node* tmp;
    if (X->level == X->right->right->level) {
      tmp = X->right;
      if (X == root) {
        root = tmp;
      }
      X->right = tmp->left;
      tmp->left = X;
      ++tmp->level;
      return tmp;
    }
    return X;
  }

  node* insert_(node* now, int x) {
    if (now == nullptr) {
      now = new node(x);
      if (root == nullptr) {
        root = now;
      }
      return now;
    }
    if (x < now->data) {
      now->left = insert_(now->left, x);
    } else if (x > now->data) {
      now->right = insert_(now->right, x);
    }
    now = skew(now);
    now = split(now);
    return now;
  }

  void insert(int x) { root = insert_(root, x); }

  static node* predecessor(node* now) {
    now = now->left;
    while (now->right != nullptr) {
      now = now->left;
    }
    return now;
  }

  static node* successor(node* now) {
    now = now->right;
    while (now->left != nullptr) {
      now = now->right;
    }
    return now;
  }

  static node* decrease_level(node* now) {
    int right_level = 0;
    int left_level = 0;
    if (now->right != nullptr) {
      right_level = now->right->level;
    }
    if (now->left != nullptr) {
      left_level = now->left->level;
    }
    int lev = left_level < right_level ? left_level + 1 : right_level + 1;
    if (lev < now->level) {
      now->level = lev;
    }
    if (now->right != nullptr && lev < now->right->level) {
      now->right->level = lev;
    }
    return now;
  }

  node* erase_(node* now, int x) {
    if (now == nullptr) {
      return now;
    }
    if (x < now->data) {
      now->left = erase_(now->left, x);
    } else if (x > now->data) {
      now->right = erase_(now->right, x);
    } else {
      if (now->left == nullptr && now->right == nullptr) {
        delete now;
        return nullptr;
      }
      if (now->right == nullptr) {
        node* tmp = predecessor(now);
        now->data = tmp->data;
        now->left = erase_(now->left, now->data);
      } else {
        node* tmp = successor(now);
        now->data = tmp->data;
        now->right = erase_(now->right, now->data);
      }
    }
    decrease_level(now);
    now = skew(now);
    now->right = skew(now->right);
    if (now->right != nullptr && now->right->right != nullptr) {
      now->right->right = skew(now->right->right);
    }
    now = split(now);
    now->right = split(now->right);
    return now;
  }

  void erase(int x) { root = erase_(root, x); }

  node* get_root() { return root; }
};
