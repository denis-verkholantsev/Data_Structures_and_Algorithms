#include<iostream>
#include<fstream>

void QuickSortS(int* arr, int Len, int k1, int k2) {
    int N = Len, size = 1;
    while (N > 0) {
        N >>= 1;
        ++size;
    }
    int* StackLeft = new int[size];
    int* StackRight = new int[size];
    int topInStack = -1;
    ++topInStack; StackLeft[topInStack] = 0; StackRight[topInStack] = Len - 1;

    while (topInStack > -1) {
        int left = StackLeft[topInStack];
        int right = StackRight[topInStack];
        --topInStack;
        int i = left, j = right;
        int pindex = i + (j - i) / 2;
        int p = arr[pindex];
        while (i < j) {
            while (arr[i] < p) {
                ++i;
            }
            while (p < arr[j]) {
                --j;
            }
            if (i < j) {
                std::swap(arr[i], arr[j]);
                ++i; --j;
            }
            else if (i == j) {
                ++i; --j;
            }
        }
        if (pindex < i) {
            if (j > left && j > k1 - 2) { ++topInStack; StackLeft[topInStack] = left; StackRight[topInStack] = j; }
            if (i < right && i < k2) { ++topInStack; StackLeft[topInStack] = i; StackRight[topInStack] = right; }
        }
        else {
            if (i < right && i < k2) { ++topInStack; StackLeft[topInStack] = i; StackRight[topInStack] = right; }
            if (j > left && j > k1 - 2) { ++topInStack; StackLeft[topInStack] = left; StackRight[topInStack] = j; }
        }
    }
    delete[] StackLeft;
    delete[] StackRight;
}

int get_num(std::ifstream& inFile, char stop_sym) {
    char number[256] = "";
    int i = 0;
    number[i] = inFile.get();
    while (number[i] != stop_sym && number[i] != EOF) {
        number[++i] = inFile.get();
    }
    number[i] = '\0';
    return std::atoi(number);
}


int main(int argc, char* argv[]) {
    std::ifstream inFile(argv[1]);
    std::ofstream outFile(argv[2]);
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    }
    int size = get_num(inFile, ' ');
    int k1 = get_num(inFile, ' ');
    int k2 = get_num(inFile, '\n');
    int A = get_num(inFile, ' ');
    int B = get_num(inFile, ' ');
    int C = get_num(inFile, ' ');
    int* arr = new int[size];
    arr[0] = get_num(inFile, ' ');
    arr[1] = get_num(inFile, '\n');
    for (int i = 2; i < size; ++i) {
        arr[i] = A * arr[i - 2] + B * arr[i - 1] + C;
    }
    QuickSortS(arr, size, k1, k2);
    for (int i = k1 - 1; i < k2-1; ++i) {
        outFile << arr[i] << " ";
    }
    outFile << arr[k2 - 1];
    delete[] arr;
    inFile.close();
    outFile.close();
}