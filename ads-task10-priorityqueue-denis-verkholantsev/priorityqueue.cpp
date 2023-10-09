#include <iostream>
#include<fstream>
#include"FibHeap.h"

int main(int argc, char* argv[])
{
	FibNode** nodes_for_ops = new FibNode * [100000];
	for (int i = 0; i < 100000; ++i) {
		nodes_for_ops[i] = nullptr;
	}

	std::ifstream inFile(argv[1]);
	std::ofstream outFile(argv[2]);
	int counter = 0;
	char buffer[256] = "";
	FibHeap heap;
	bool stop_flag = true;
	int number = 0;
	int value = 0;
	FibNode* tmp;
	while (stop_flag) {
		inFile >> buffer;
                if (inFile.peek() == EOF) {
                  break;
		}
		switch (buffer[0]) {
		case 'e':
			tmp = heap.extract_min();
			if (tmp != nullptr) {
				outFile << tmp->data << '\n';
			}
			else {
				outFile << "*\n";
			}
			break;
		case 'p':
			inFile >> number;
			nodes_for_ops[counter] = heap.insert(number);
			break;
		case 'd':
			inFile >> number;
			inFile >> value;
			heap.decrease_key(nodes_for_ops[number-1], value);
			break;
		default:
			stop_flag = false;
			break;
		}
		counter++;
	}
    for (int i = 0; i < 100000; ++i) {
            delete nodes_for_ops[i];
            nodes_for_ops[i] = nullptr;
    }
	delete[] nodes_for_ops;
    inFile.close();
    outFile.close();
}

