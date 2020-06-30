
#include <stdio.h>

double water_amount(int level, int horizantal , double result){
  if (level == 0){
    return 100;
  }
  else if( horizantal==0 || level == horizantal ){
    return 100 + water_amount(level-1,0,result)/2 ;
  }
  else{
    return 100+(water_amount(level-1,horizantal,result)+ water_amount(level-1,horizantal-1,result))/2;
  }
  return result;
}

int main(){
  printf("%f\n",water_amount(0,0,0)-100);
  return 0;
}
