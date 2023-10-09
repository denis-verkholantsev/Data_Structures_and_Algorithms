
#include <fstream>
#include <iostream>

#include "two_stacks_queue.h"

int get_number(std::ifstream& inFile, char* line) {
  int i = 0;
  inFile.get();
  int ch = inFile.get();
  for (i = 0; i < 256 && (char)ch != '\n'; ++i) {
    line[i] = (char)ch;
    ch = inFile.get();
  }
  line[++i] = '\0';
  return std::atoi(line);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cout << "Not enough arguments" << std::endl;
  } else {
    std::ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
      std::cout << "Can't open input file" << std::endl;
    }
    std::ofstream outFile(argv[2]);
    if (!outFile.is_open()) {
      std::cout << "Can't open output file" << std::endl;
    }
    my::two_stacks_queue<int> que;
    int ch;
    ch = inFile.get();
    while ((char)ch != '\n') {
      ch = inFile.get();
    };
    ch = inFile.get();
    while (ch != EOF) {
      char line[256] = "";
      switch (ch) {
        case '+':
          que.push(get_number(inFile, line));
          break;
        case '?':
          outFile << (que.get_max() - que.get_min());
          outFile << '\n';
          inFile.get();
          break;
        case '-':
          que.pop();
          inFile.get();
          break;
        default: {
        }
      }
      ch = inFile.get();
    }
    inFile.close();
    outFile.close();
  }
}