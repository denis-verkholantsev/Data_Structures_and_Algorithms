#include <fstream>
#include <iostream>

struct range {
  int start;
  int stop;
  range() : start(0), stop(0){};
};

int partition(double* arr, int* keys, range from_to) {
  int left = from_to.start;
  int right = from_to.stop;
  double pivot = arr[right];
  int i = left;
  for (int j = left; j < right; ++j) {
    if (arr[j] <= pivot) {
      std::swap(arr[i], arr[j]);
      std::swap(keys[i], keys[j]);
      ++i;
    }
  }
  std::swap(arr[i], arr[right]);
  std::swap(keys[i], keys[right]);
  return i;
}

void kthSmallest(double* arr, int* keys, range from_to, int searchable_pos) {
  int left = from_to.start;
  int right = from_to.stop;
  while (left < right + 1) {
    range newnew;
    newnew.start = left;
    newnew.stop = right;
    int pivotIndex = partition(arr, keys, newnew);
    if (pivotIndex == searchable_pos) {
      return;
    }
    if (pivotIndex > searchable_pos) {
      right = pivotIndex - 1;
    } else {
      left = pivotIndex + 1;
    }
  }
}

int get_num(std::ifstream& inFile, char end) {
  char tmp[256] = "";
  int i = 0;
  while ((char)inFile.peek() != end && i < 256) {
    tmp[i++] = (char)inFile.get();
  }
  tmp[i] = '\0';
  return std::atoi(tmp);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Not enough arguments";
    return -1;
  }
  std::ifstream inFile(argv[1]);
  if (!inFile.is_open()) {
    std::cout << "Can't open input file" << std::endl;
    return -1;
  }
  int size = get_num(inFile, '\n');
  double max_val = 0.0;
  int max_ind = 0;
  double min_val = 0.0;
  int min_ind = 0;
  int* keys = new int[size];
  for (int i = 0; i < size; ++i) {
    keys[i] = i;
  }
  double* arr = new double[size];
  for (int j = 0; j < size; ++j) {
    double int_part = (double)get_num(inFile, '.');
    inFile.get();
    arr[j] = int_part + (double)(inFile.get() - 48) / 10.0 +
             (double)(inFile.get() - 48) / 100.0;
    if (j != 0) {
      if (arr[j] > max_val) {
        max_ind = j;
        max_val = arr[j];
      }
      if (arr[j] < min_val) {
        min_ind = j;
        min_val = arr[j];
      }
    } else {
      max_ind = min_ind = j;
      min_val = max_val = arr[j];
    }
    inFile.get();
  }
  range newnew;
  newnew.start = 0;
  newnew.stop = size - 1;
  kthSmallest(arr, keys, newnew, size / 2);
  std::cout << min_ind + 1 << " " << keys[size / 2] + 1 << " " << max_ind + 1;
  delete[] keys;
  delete[] arr;
  inFile.close();
  return 0;
}
