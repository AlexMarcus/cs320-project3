#include "Cache.h"


using namespace std;

int main(int argc, char** argv){
  vector<Cache*> c;
  for(int i = 0; i < 3; i++){ 
    Cache * cache = new Cache(4, i);
    c.push_back(cache);
  }
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(i != j){
	c[i]->addNeighbor(c[j]);
      }
    }
  }
 
  string operation = "";
  
  while(1){
    cout << "\nCommand (type 'END' to quit): ";
    cin >> operation;
    if(operation =="END") break;
    char ca = operation[0];
    int cache = ca - 48;
    char l = operation[2];
    int line = l - 48;
    char action = operation[1];
    if(action == 'r'){
      c[cache]->Read(line);
    }
    if(action == 'w'){
      c[cache]->Write(line);
    }
        for(auto it = c.begin(); it != c.end(); it++) cout << (*it)->to_string() << endl;
  }
  
  
}
