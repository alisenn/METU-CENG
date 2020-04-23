#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cassert>
#include "the3.h"

using namespace std;
/*******************************************************************YAPILACAKLAR*******************************************************
1-SCORELARI BUL
-bir nodun score'u onun target noda giden en kısa yol ile diger tum nodelardan teker teker gecerek giden en kısa yola bolumunun toplamları
2-disconnected component sayısını don
-dfs kullan

#################################################################YAPILACAKLAR######################################################*/



void printVector(std::vector<int>& array){

    std::cout << "size: " << array.size() << std::endl;
    for (unsigned i = 0; i < array.size(); ++i){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}


bool TestTask()
{
    
    // time variables
  clock_t begin;
  clock_t end;
  double duration;
  int expectedTime = 500;
  int true_answer = -1;
  int solution = -1;
  
    // generate solution
  if ((begin = clock ()) == -1) 
      std::cerr << "clock err" << std::endl;
      
  //solution =Important (n, edgeList, scores);


  if ((end = clock ()) == -1) 
      std::cerr << "clock err" << std::endl;
      
  duration = ((double)end-begin) / CLOCKS_PER_SEC * 1000000;
  
  cout << "Elapsed time  " << duration << " vs " << expectedTime << " microsecs" << std::endl;

  return (solution == true_answer);
}





int main()
{
   // srandom(time(0));       // no need to initialize second time
    //printVector(scores);
  //if (TestTask())
   // std::cout << "PASSED TASK" << std::endl << std::endl;
  //else
   // std::cout << "FAILED TASK" << std::endl << std::endl;
  //int v = 5, e = 4; 
  
    // Create the graph 
   int val = 42;
/*******************************************************************Test icin grap olustur*******************************************************/
   int *a  = &val;
   a = new int [10];
   int **b = &a;
   


   int grap[5][5] = {
	0, 0, 2, 5, 3,
	0, 0, 0, 2, 3,
	2, 0, 0, 1, 0,
	5, 2, 1, 0, 4,
	3, 3, 0, 4, 0,
	};
   
   int grap1[6][6] = {
   	0, 0, 0, 3, 0, 2,
	0, 0, 3, 0, 2, 0,
	0, 3, 0, 0, 0, 0,
	3, 0, 0, 0, 0, 4,
	0, 2, 0, 0, 0, 0,
	2, 0, 0, 4, 0, 0,
   };
   int graph[9][9] = {  { 0, 4, 0, 0, 0, 0, 0, 8, 0 }, 
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
   /*grapları degistirmek icin  akare degerini degistr bide grap adını guncelle*/
   int akare =  5; //aslında len
   double *aa  = new double[akare];
   
   b = new int *[akare];
   for(int i=0 ; i<akare; i++){
   	b[i] = new int[akare];
   }
   int array_1000[1000][1000]={0};
    for(int i=0;i<999;i++)
    {
        for(int k=i+1;k<1000;k++)
        {
            if(i==k)   array_1000[i][k]=array_1000[k][i]=0;
            else
            array_1000[i][k]=array_1000[k][i]=rand()%100;
        }
    }



   for(int i=0; i< akare; i++){
   	for(int j=0; j<akare; j++){
		b[i][j] = grap	[i][j];
   		
   	}
   }
   
   

/*#################################################################Test icin grap olustur##########################################################*/   

  
  Important(akare,b,aa);


  return 0;
}
  












