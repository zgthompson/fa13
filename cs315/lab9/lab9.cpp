#include "AvlTree.h"
#include "BinarySearchTree.h"

#include <iostream>
#include <fstream>
#include <cctype>
#include <ctime>

void printInfo(int words, int lines, double time) {
  std::cout << "Total number of words \t" << words << std::endl;
  std::cout << "Total number of lines \t" << lines << std::endl;
  std::cout << "Time taken to build index is " << time << " sec" << std::endl;
}

void buildTree(char* inputFile) {
  // create trees
  AvlTree<std::string> avlTree = AvlTree<std::string>();
  BinarySearchTree<std::string> bsTree = BinarySearchTree<std::string>();

  double bsTime = 0, avlTime = 0;

  // open file
  ifstream myfile(inputFile);

  // set up variables
  double startTime, endTime;
  char ch;
  int lineCount = 0, wordCount = 0;
  std::string curString = "";

  while ((ch = myfile.get()) != EOF) {

    if ( isalnum(ch) ) {
      curString += ch;
    }

    else {

      if (!curString.empty()) {
        // new word
        wordCount++;

        // insert and time avl tree
        startTime = clock();
        avlTree.insert(curString, lineCount + 1);
        endTime = clock();
        avlTime += (double) (endTime - startTime) / CLOCKS_PER_SEC;

        //insert and time binary search tree
        startTime = clock();
        bsTree.insert(curString, lineCount + 1);
        endTime = clock();
        bsTime += (double) (endTime - startTime) / CLOCKS_PER_SEC;

        // reset curString
        curString = "";
      }

      if (ch == '\n') {
        lineCount++;
      }
    }
  }

  bsTree.printTree();
  std::cout << std::endl << "Binary Search Tree" << std::endl;
  printInfo(wordCount, lineCount, bsTime);
  avlTree.printTree();
  std::cout << std::endl << "AVL Tree" << std::endl;
  printInfo(wordCount, lineCount, avlTime);
}
  
int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: ./lab9 test.txt" << std::endl;
  }
  else {
  buildTree(argv[1]);
  }
  return 0;
}
