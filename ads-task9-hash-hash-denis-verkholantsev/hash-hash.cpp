#include <fstream>
#include <iostream>

#include "HashTable.h"

int main(int argc, char* argv[]) {
  std::ifstream inFile(argv[1]);
  HashTable table;
  int number_of_operations = 0;
  inFile >> number_of_operations;
  char sym;
  int number;
  std::ofstream outFile(argv[2]);
  for (int i = 0; i < number_of_operations; ++i) {
    inFile >> sym;
    inFile >> number;
    switch (sym) {
      case '+':
        table.insert(number);
        break;
      case '-':
        table.remove(number);
        break;
      case '?':
        outFile << (table.search(number) ? "true\n" : "false\n");
        break;
      default:
        break;
    }
  }
  inFile.close();
  outFile.close();
}