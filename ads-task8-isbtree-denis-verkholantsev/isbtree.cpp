#include <fstream>
#include <iostream>

struct node {
  bool leaf;
  int number_of_keys;
  int* keys;
  int number_of_descendants;
  int* descendants;
  int number_of_node;
  int level = 0;
  node() = default;
  node(bool leaf_, int number_of_node_, int number_of_keys_, int* keys_,
       int number_of_descendants_ = 0, int* descendants_ = nullptr) {
    leaf = leaf_;
    number_of_keys = number_of_keys_;
    keys = keys_;
    number_of_descendants = number_of_descendants_;
    descendants = descendants_;
    number_of_node = number_of_node_;
  };
  ~node() {
    delete[] keys;
    delete[] descendants;
  }
  void print() const {
    std::cout << "---------NODE-------\n";
    std::cout << "leaf: " << leaf << std::endl;
    std::cout << "level: " << level << std::endl;
    std::cout << number_of_keys << " keys: ";
    for (int i = 0; i < number_of_keys; ++i) {
      std::cout << keys[i] << " ";
    }
    std::cout << std::endl;
    std::cout << number_of_descendants << " descendants: ";
    for (int i = 0; i < number_of_descendants; ++i) {
      std::cout << descendants[i] << " ";
    }
    std::cout << std::endl;
  }
};

struct dp {
  int cnt = 0;
  dp() = default;
};

void ignore(std::ifstream& inFile) {
  while (inFile.get() != '\n') {
  };
}

int get_num(const char* buffer, int start_pos, char stop_sym = '\0') {
  char tmp[256] = "";
  int i = 0;
  while (buffer[start_pos] != stop_sym) {
    tmp[i++] = buffer[start_pos++];
  }
  tmp[i] = '\0';
  return std::atoi(tmp);
}

node* create_node(node** arr, std::ifstream& inFile) {
  char buffer[256] = "";
  inFile >> buffer;
  bool leaf = false;
  if (buffer[0] == 'l') {
    leaf = true;
  }
  inFile >> buffer;
  int num_of_node = get_num(buffer, 2);
  inFile >> buffer;
  int num_keys = get_num(buffer, 1, ':');
  int* keys = new int[num_keys];
  inFile >> keys[0];

  for (int i = 1; i < num_keys - 1; ++i) {
    inFile >> keys[i];
    if (keys[i] < keys[i - 1]) {
      return nullptr;
    }
  }
  inFile >> buffer;
  if (num_keys != 1) {
    keys[num_keys - 1] = get_num(buffer, 0, ')');
  }
  if (!leaf) {
    inFile >> buffer;
    int num_desc = get_num(buffer, 1, ':');
    int* descendants = new int[num_desc];
    for (int i = 0; i < num_desc - 1; ++i) {
      inFile >> descendants[i];
    }
    inFile >> buffer;
    descendants[num_desc - 1] = get_num(buffer, 0, ')');
    return new node(leaf, num_of_node, num_keys, keys, num_desc, descendants);
  }
  if (inFile.peek() != '\n') {
    ignore(inFile);
  }
  return new node(leaf, num_of_node, num_keys, keys);
}

node* search(node** arr, int num, int size) {
  for (int i = 0; i < size; ++i) {
    if (arr[i]->number_of_node == num) {
      return arr[i];
    }
  }
  return nullptr;
}

bool check_intervals(node* X, int left_wall, int right_wall, bool leftw,
                     bool rightw) {
  if (leftw && rightw) {
    for (int i = 0; i < X->number_of_keys; ++i) {
      if (X->keys[i] <= left_wall || X->keys[i] >= right_wall) {
        return false;
      }
    }
    return true;
  }
  if (leftw && !rightw) {
    for (int i = 0; i < X->number_of_keys; ++i) {
      if (X->keys[i] <= left_wall) {
        return false;
      }
    }
    return true;
  }
  if (!leftw && rightw) {
    for (int i = 0; i < X->number_of_keys; ++i) {
      if (X->keys[i] >= right_wall) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool checking(node** arr, node* X, int t, int size, int left_wall,
              int right_wall, bool leftw, bool rightw, dp& height) {
  if (X != nullptr) {
    if (X->leaf) {
      X->level = height.cnt + 1;
      if (X->number_of_keys >= t - 1 && X->number_of_keys <= 2 * t - 1) {
        bool checking_intervals =
            check_intervals(X, left_wall, right_wall, leftw, rightw);
        if (!checking_intervals) {
          return checking_intervals;
        }
        return true;
      }
      return false;
    }
    if (X->number_of_keys >= t - 1 && X->number_of_keys <= 2 * t - 1 &&
        X->number_of_descendants >= t && X->number_of_descendants <= 2 * t) {
      if (!check_intervals(X, left_wall, right_wall, leftw, rightw)) {
        return false;
      }
      bool result = true;
      height.cnt++;
      bool tmp_res = checking(arr, search(arr, X->descendants[0], size), t,
                              size, left_wall, X->keys[0], leftw, true, height);
      height.cnt--;
      result = tmp_res;
      if (!result) {
        return false;
      }
      if (X->number_of_descendants > 2) {
        for (int i = 1; i < X->number_of_descendants - 1; ++i) {
          height.cnt++;
          tmp_res = checking(arr, search(arr, X->descendants[i], size), t, size,
                             X->keys[i - 1], X->keys[i], true, true, height);
          height.cnt--;
          result = tmp_res;
          if (!result) {
            return false;
          }
        }
      }
      height.cnt++;
      tmp_res = checking(
          arr, search(arr, X->descendants[X->number_of_descendants - 1], size),
          t, size, X->keys[X->number_of_keys - 1], right_wall, true, rightw,
          height);
      result = tmp_res;
      height.cnt--;
      if (!result) {
        return result;
      }
      return true;
    }
    return false;
  }
  return false;
}

bool checking_r(node** arr, node* root, int t, int size) {
  if (root->number_of_keys > 0 && root->number_of_keys < 2 * t &&
      root->number_of_descendants > 1 &&
      root->number_of_descendants < 2 * t + 1) {
    dp height;
    if (!checking(arr, search(arr, root->descendants[0], size), t, size, 0,
                  root->keys[0], false, true, height)) {
      return false;
    }
    // if >2 descendants
    if (root->number_of_descendants > 2) {
      for (int i = 1; i < root->number_of_descendants - 1; ++i) {
        if (!checking(arr, search(arr, root->descendants[i], size), t, size,
                      root->keys[i - 1], root->keys[i], true, true, height)) {
          return false;
        }
      }
    }
    if (!checking(
            arr,
            search(arr, root->descendants[root->number_of_descendants - 1],
                   size),
            t, size, root->keys[root->number_of_keys - 1], 0, true, false,
            height)) {
      return false;
    }
  }
  return true;
}

bool check_levels(node** arr, int size) {
  int tmp_level = 0;
  int i = 0;
  if (size > 1) {
    while (tmp_level == 0) {
      if (arr[i]->leaf) {
        tmp_level = arr[i]->level;
      }
      ++i;
    }
    for (int j = i; j < size; ++j) {
      if (arr[j]->leaf) {
        if (arr[j]->level != tmp_level) {
          return false;
        }
      }
    }
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::ifstream inFile(argv[1]);
  int N = 0;
  int root = 0;
  int t = 0;
  inFile >> N;
  inFile >> t;
  inFile >> root;
  node** arr = new node*[N];
  bool flag = true;
  int actual_size = N;
  for (int i = 0; i < N; ++i) {
    node* tmp = create_node(arr, inFile);
    if (tmp != nullptr) {
      arr[i] = tmp;
    } else {
      flag = false;
      actual_size = i;
      break;
    }
  }
  if (flag && checking_r(arr, search(arr, root, N), t, N)) {
    if (check_levels(arr, N)) {
      std::cout << "yes";
    } else {
      std::cout << "no";
    }
  } else {
    std::cout << "no";
  }
  inFile.close();
  for (int i = 0; i < actual_size; ++i) {
    delete arr[i];
  }
  delete[] arr;
}