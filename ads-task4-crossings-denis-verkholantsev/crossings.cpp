#include <fstream>
#include <iostream>
#include <string.h>

struct pair {
  int x1;
  int x2;
  pair() = default;
  pair(int x1_in, int x2_in) : x1(x1_in), x2(x2_in){};
  pair& operator=(const pair& X) {
    if (this != &X) {
      x1 = X.x1;
      x2 = X.x2;
    }
    return *this;
  }
};

int get_num(std::ifstream& inFile, char stop_sym) {
  char number[256] = "";
  int i = 0;
  number[i] = inFile.get();
  while (number[i] != stop_sym) {
    number[++i] = inFile.get();
  }
  number[i] = '\0';
  return std::atoi(number);
}

void filling_array(std::ifstream& inFile, pair* pairs, int size) {
  int i = 0;
  while (i < size) {
    int x1 = get_num(inFile, ' ');
    int x2 = get_num(inFile, '\n');
    pairs[i++] = pair(x1, x2);
  }
}

void merge_sort_1cord(pair* pairs, int size) {
  pair* src = pairs;
  pair* tmp = new pair[size];
  pair* dst = tmp;
  for (int i = 1; i < size; i *= 2) {
    int start1 = 0;
    int end1 = 0;
    int start2 = 0;
    int end2 = 0;
    int dst_ind = 0;
    for (int j = 0; j < size; j += 2 * i) {
      start1 = j;
      end1 = start1 + i < size ? start1 + i : size;  // if rem < i
      start2 = end1;
      end2 = start2 + i < size ? start2 + i : size;
      while (start1 < end1 && start2 < end2) {
        dst[dst_ind++] =
            src[start1].x1 < src[start2].x1 ? src[start1++] : src[start2++];
      }
      while (start1 < end1) {
        dst[dst_ind++] = src[start1++];
      }
      while (start2 < end2) {
        dst[dst_ind++] = src[start2++];
      }
    }
    std::swap(src, dst);
  }
  if (src != pairs) {  // num of iteration: odd or not
    for (int i = 0; i < size; ++i) {
      pairs[i] = tmp[i];
    }
  }
  delete[] tmp;
}

unsigned long long inversions_cnt_with_merge_sort_2cord(pair* pairs, int size) {
  unsigned long long res = 0;
  pair* src = pairs;
  pair* tmp = new pair[size];
  pair* dst = tmp;
  for (int i = 1; i < size; i *= 2) {
    int start1 = 0;
    int end1 = 0;
    int start2 = 0;
    int end2 = 0;
    int dst_ind = 0;
    for (int j = 0; j < size; j += 2 * i) {
      start1 = j;
      end1 = start1 + i < size ? start1 + i : size;
      start2 = end1;
      end2 = start2 + i < size ? start2 + i : size;
      while (start1 < end1 && start2 < end2) {
        if (src[start1].x2 < src[start2].x2) {
          dst[dst_ind++] = src[start1++];
        } else {
          dst[dst_ind++] = src[start2++];
          res += (unsigned long long)(end1 - start1);
        }
      }
      while (start1 < end1) {
        dst[dst_ind++] = src[start1++];
      }
      while (start2 < end2) {
        dst[dst_ind++] = src[start2++];
      }
    }
    std::swap(src, dst);
  }
  if (src != pairs) {
    for (int i = 0; i < size; ++i) {
      pairs[i] = tmp[i];
    }
  }
  delete[] tmp;
  return res;
}

int main(int argc, char* argv[]) {
  char input[256] = "";
  if (argc < 2) {
    std::cin.getline(input, 256);
  } else {
    strncpy(input, argv[1], 256);
  }
  std::ifstream inFile(input);
  if (!inFile.is_open()) {
    std::cout << "Can't open input file" << std::endl;
    return -1;
  }
  const int size = (const int)get_num(inFile, '\n');
  pair* pairs = new pair[size];
  filling_array(inFile, pairs, size);
  merge_sort_1cord(pairs, size);
  std::cout << inversions_cnt_with_merge_sort_2cord(pairs, size);
  delete[] pairs;
  inFile.close();
}