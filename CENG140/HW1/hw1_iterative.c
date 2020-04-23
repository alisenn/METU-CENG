#include <stdio.h>
int main(){
  int i,j,lent,least,l,num,numinverse;
  int arr[100][100],result[100][100][2];
  scanf("%d",&lent);
  for(i=0;i<lent;i++){
    for(j=0;j<i+1;j++){
      scanf("%d",&arr[i][j]);
    }
  }
  result[0][0][0]=arr[0][0];
  for(i=1;i<lent;i++){
    for(j=0;j<=i;j++){
      if(j==0){
        result[i][j][0]=result[i-1][0][0]+arr[i][j];
        result[i][j][1]=2*result[i-1][0][1];
      }
      else if(j==i){
        result[i][j][0]=result[i-1][j-1][0]+arr[i][j];
        result[i][j][1]=2*result[i-1][j-1][1]+1;
      }
      else{
          if(result[i-1][j-1][0]<result[i-1][j][0]){
            result[i][j][0]=result[i-1][j-1][0]+arr[i][j];
            result[i][j][1]=2*result[i-1][j-1][1]+1;
          }
          else{
            result[i][j][0]=result[i-1][j][0]+arr[i][j];
            result[i][j][1]=2*result[i-1][j][1];
          }
      }
    }
  }
  least=result[lent-1][0][0];
  l=0;
  for(i=1;i<lent;i++){
    if(result[lent-1][i][0]<least){
      least=result[lent-1][i][0];
      l=i;
    }
  }
  num=result[lent-1][l][1];
  numinverse=0;
  for(i=0;i<lent-1;i++){
    numinverse=2*numinverse+num%2;
    num /=2;
  }
  printf("%d",arr[0][0]);
  j=0;
  for(i=1;i<lent;i++){
    if(numinverse%2==0){
      printf(" %d",arr[i][j]);
    }
    else{
      j++;
      printf(" %d",arr[i][j]);
    }
    numinverse /=2;
  }
  printf("\n");
  return 0;
}
