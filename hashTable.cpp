//David Samuel, dms4gt, hashtable.cpp

#include "hashTable.h"
#include <vector>


hashTable::hashTable(int size){
  hashtable = new vector<list<string> >;
  
  if(checkPrime(size)!=true){
    int nSize= getNextPrime(size);
    hashtable->resize(nSize);
    hashSize=nSize;
  }
  cout << "Hash SIZE: " << hashSize << "\n";  
  
  for(int i=0; i<hashSize; i++){
    list<string> p;
    hashtable->push_back(p);
  }
}

hashTable::~hashTable(){
  delete hashtable;
}
int hashTable::getNextPrime (unsigned int np) {
    while ( !checkPrime(++np) );
    return np; // all your primes are belong to us
}

void hashTable::insert(string s){
  if(!(this->contains(s))){
    hashtable->at(hash(s)).push_back(s);
  }
}

int hashTable::hash(string key){
  int h= 1;
  int length= key.length();
  for(int i=0; i<length; i++){
    h*= (key[i]*41)% (hashtable->size());
    h++;
  }
   h%=hashSize;
   return h;
}
bool hashTable::checkPrime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}// from the primenumber file

bool hashTable::contains(string st){
  list<string> container= hashtable->at(hash(st));
  return (find(container.begin(), container.end(), st)!=container.end());
  
}



