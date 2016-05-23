#include "buffer.h"
buffer::buffer(){
   for (int i = 0; i < 9; ++i)
   {
      for (int j = 0; j < 9; ++j)
      {
         a[i][j]=0;
      }
   }
}
void buffer::setBuffer(int i,int j,int k){
   a[i][j]=k;
}
int buffer::getBuffer(int i,int j){
   return a[i][j];
}
