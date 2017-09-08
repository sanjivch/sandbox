#include <iostream>
#include <map>

int main(){
  
  
  std::map<int,std::string> map1;
  
  map1.insert(std::make_pair(1,"Node"));
  map1.insert(std::make_pair(2,"Pipe"));
  map1.insert(std::make_pair(3,"Node"));
  map1.insert(std::make_pair(4,"Valve"));
  map1.insert(std::make_pair(5,"Pump"));
  
  //std::cout << map1;
  //typedef std::map<int, int>::iterator i;
  for(std::map<int, std::string>::iterator i = map1.begin(); i != map1.end(); ++i){
    if(i->second != "Node")
      std::cout << i->first << " " << i->second << std::endl;
  }
  
}
