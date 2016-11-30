#include "Cache.h"
#include <sstream>


using namespace std;
/*
 * Cache Constructor:
 * Sets all cache lines to INVALID
 */
Cache::Cache(int numLines, int id){
  this -> ID = id;
  this -> numLines = numLines;
  int i;
  for(i = 0; i < numLines; i++){
    lineStates.push_back('I');
  }
}

void Cache::Read(int line){
  cout << ID << "r" << line << endl;
  char ls = lineStates[line];
  if(ls == 'M' || ls == 'O' || ls == 'E' || ls == 'S'){
    cout << "Cache "<< ID << ", Hit "<< line  << endl;
    cout << ls << "->" << ls << endl;
  }
  else{
    cout << "Cache "<< ID << ", Miss "<< line  << endl;
    bool hit=false; //result of the probe read
    for(auto it = Neighbors.begin(); it != Neighbors.end(); it++){ 
      Cache * c = *it;
      if(c -> ProbeRead(line)){
	hit = true;
      }
    }
    cout << "\nCache " << ID <<endl;
    if(hit){
      cout << ls << "->" << 'S' << endl;
      lineStates[line] = 'S';
    }
    else{
      cout << ls << "->" << 'E' << endl;
      lineStates[line] = 'E';
    }
  }
}

void Cache::Write(int line){
  cout << ID << "w" << line << endl;
  char ls = lineStates[line];
  if(ls  == 'M'){
    cout << "Cache "<< ID << ", Hit "<< line  << endl;
    cout << ls << "->" << ls << endl;
  }
  else if(ls == 'E'){
    cout << "Cache "<< ID << ", Hit "<< line  << endl;
    cout << ls << "->M"  << endl;
    lineStates[line] = 'M';
  }
  else if(ls == 'O' || ls == 'S'){
    cout << "Cache "<< ID << ", Hit "<< line  << endl;
    cout << ls << "->M"  << endl;
    lineStates[line] = 'M';
    Invalidate(line);
  }
  else{
    cout << "Cache "<< ID << ", Miss "<< line << endl;
    bool hit=false; //result of the probe write
    for(auto it = Neighbors.begin(); it != Neighbors.end(); it++){
      Cache * c = *it;
      if(c -> ProbeWrite(line)){
        hit = true;
      }
    }
    cout << "\nCache " << ID <<endl;
    if(hit){
      cout << ls << "->" << 'M' << endl;
      lineStates[line] = 'M';
    }
    else{
      cout << ls << "->" << 'M' << endl;
      lineStates[line] = 'M';
    }
  }

}

bool Cache::ProbeRead(int line){
  cout << "\nCache " << ID << ", Probe Read " << line << endl;
  char ls = lineStates[line];
  bool retVal = true;
  if(ls == 'M' || ls == 'O'){
    cout << "Hit" << endl;
    cout << ls << "->O" << endl;
    lineStates[line] = 'O';
  }
  else if(ls == 'E'){
    cout << "Hit" << endl;
    cout << "E->S" << endl;
    lineStates[line] = 'S';
  }
  else if(ls == 'S'){
    cout << "Hit" << endl;
    cout << "S->S" << endl;
  }
  else{
    cout << "Miss" << endl;
    cout << ls << "->" << ls << endl;
    retVal = false;
  }
  cout << "End Probe Read" << endl;
  return retVal;

}
bool Cache::ProbeWrite(int line){
  cout << "\nCache " << ID << ", Probe Write " << line << endl;
  char ls = lineStates[line];
  bool retVal = true;
  if(ls == 'S' || ls == 'I'){ 
    cout << "Miss" << endl;
    cout << ls << "->I" << endl;
    lineStates[line] = 'I';
    retVal = false;
  }
  else{
    cout << "Hit" << endl;
    cout << ls << "->I" << endl;
    lineStates[line] = 'I';
  }
  cout << "End Probe Write" << endl;
  return retVal;
}

void Cache::addNeighbor(Cache::Cache * c){Neighbors.push_back(c);}

string Cache::to_string(){
  ostringstream out;
  out << "|\tCache " << ID << "\t|\tState\t|"<<endl;
  for(int i = 0; i < numLines; i++){
    out << "|\tLine " << i << "\t|\t" << lineStates[i] << "\t|" <<endl;
  }
  return out.str();

}

void Cache::Invalidate(int line){
  for(auto it = Neighbors.begin(); it != Neighbors.end(); it++){
    Cache *cache = (*it);
    cache -> SetLine(line, 'I');
  }
}

void Cache::SetLine(int line, char state){
  lineStates[line] = state;
}
