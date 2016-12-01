#ifndef CACHE_H
#define CACHE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Cache{
 public:
  Cache(int, int);
  void addNeighbor(Cache::Cache*);
  void Read(int);
  void Write(int);
  bool ProbeRead(int);
  bool ProbeWrite(int);
  //std::vector<char> lineStates;
  std::string to_string();
  void Invalidate(int);
  void SetLine(int, char);



 private:
  int ID;
  int numLines;
  std::vector<char> lineStates;
  std::vector<Cache::Cache*> Neighbors;
  
};


#endif
