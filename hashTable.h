//David Samuel, dms4gt, hashTable.h
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <iostream>

using namespace std;

class hashTable{
 public:
  hashTable(int size);
  ~hashTable();
  void insert(string s);
  int hash(string key);
  bool contains(string st);
  bool checkPrime(unsigned int p);
  int getNextPrime(unsigned int np);

 private:
  vector<list <string> > *hashtable;
  int hashSize;
};
#endif
  

