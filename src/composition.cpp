#include "composition.h"

double composition::checkSum(){
      double sum = 0.0;
      for(int i = 0; i< 3; i++){
        sum+=z[i];
      }

      if(sum == 1.0)
        return 1.0;
      else
        return -1.0;
}

composition::composition()
{
    //ctor
}

composition::~composition()
{
    //dtor
}
