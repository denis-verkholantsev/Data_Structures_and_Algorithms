#include<iostream>
#include<fstream>

void radixSort(char** arr, int size, int len, int phase) {
	int C[256] = {};
	char** out = new char* [size];
	for (int i = 0; i < phase; ++i) {
		for (int j = 0; j < 256; ++j) {
			C[j] = 0;
		}
		for (int j = 0; j < size; ++j) {
			int d = (int)arr[j][len - 1 - i];
			++C[d];
		}
		int count = 0;
		for (int j = 0; j < 256; ++j) {
			int tmp = C[j];
			C[j] = count;
			count += tmp;
		}
		for (int j = 0; j < size; ++j) {
			int d = (int)arr[j][len - 1 - i];
			out[C[d]] = arr[j];
			C[d]++;
		}
		for (int j = 0; j < size; ++j) {
			arr[j] = out[j];
		}
	}
	delete[] out;
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
	int size = get_num(inFile, ' ');
	int len = get_num(inFile, ' ');
	int phase = get_num(inFile, '\n');
	char** strings = new char* [size];
	for (int i = 0; i < size; ++i) {
		strings[i] = new char[len];
	}
	char* tmp = new char[size+1];
	for (int i = 0; i < len; ++i) {
		inFile >> tmp;
		for (int j = 0; j < size; ++j) {
			strings[j][i] = tmp[j];
		}
	}
	delete[] tmp;
	radixSort(strings, size, len, phase);
	for (int i = 0; i < size; ++i) {
		outFile << strings[i][0];
	}
	for (int i = 0; i < size; ++i) {
		delete[] strings[i];
	}
	delete[] strings;
	inFile.close();
	outFile.close();
}