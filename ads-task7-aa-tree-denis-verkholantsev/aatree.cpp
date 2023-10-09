#include "AATree.h"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
  std::ifstream inFile(argv[1]);
  std::ofstream outFile(argv[2]);
  AATree tree;
  const char* False = "false\n";
  const char* True = "true\n";
  int N = 0;
  char sym = 0;
  int num = 0;
  inFile >> N;
  for (int i = 0; i < N; ++i) {
    inFile >> sym;
    inFile >> num;
    switch (sym) {
      case '+':
        tree.insert(num);
        outFile << tree.balance() << '\n';
        break;
      case '-':
        tree.erase(num);
        outFile << tree.balance() << '\n';
        break;
      case '?':
        if (tree.search(num)) {
          outFile << True;
        } else {
          outFile << False;
        }
        break;
      default:
        break;
    }
  }
  inFile.close();
  outFile.close();
}
