	#include "the3.h"
using namespace std;
	/*****************************************************************Depth First to find components **************************************************************/

	void DFS(int start, vector<bool>& visited,int **adj,int len) 
	{
	    // Print the current node buna gerek yok
 
	    visited[start] = true; 
	    // For every node of the graph 
	    for (int i = 0; i < len; i++) { 
	        // If some node is adjacent to the current node with some weight
	        // and it has not already been visited 
	        if (adj[start][i] >= 1 &&  (!visited[i])) { 
	            DFS(i, visited,adj,len);
	        } 
	    } 
	} 

	/*#################################################################Depth First to find components##########################################################*/



	/*****************************************************************Dijkstra's shortest path********************************************************************/	

	int minDistance(int dist[], bool sptSet[],int len) 
	{ 
	    // Initialize min value 
	    int min = 2147483647, min_index; 
	  
	    for (int v = 0; v < len; v++) 
	        if (sptSet[v] == false && dist[v] <= min) 
	            min = dist[v], min_index = v; 
	  
	    return min_index; 
	} 
	 
	int ** dijkstra(int **graph, int src,int len) 
	{ 
		//result icin allocation
		int **res = new int*[len];
		for(int i=0; i<len; i++){
			res[i] = new int[len];
		}

	    
	    bool sptSet[len]; // sptSet[i] will be true if vertex i is included in shortest 
	    // path tree or shortest distance from src to i is finalized 
	  	for(int a=0; a<len; a++){
	    // Initialize all distances as INFINITE and stpSet[] as false 
		    for (int i = 0; i < len; i++) 
		        res[a][i] = 2147483647, sptSet[i] = false; 
		  
		    res[a][a] = 0; 
		  	
		    
		    for (int count = 0; count < len - 1; count++) { 
		        int u = minDistance(res[a], sptSet,len); 
		  
		        
		        sptSet[u] = true; 
		        for (int v = 0; v < len; v++) 
		            if (!sptSet[v] && graph[u][v] && res[a][u] != 2147483647 && res[a][u] + graph[u][v] < res[a][v]) 
		                res[a][v] = res[a][u] + graph[u][v]; 
		    } 
	    }
	  	return res;
	    // print the constructed distance array 
	} 

	/*#################################################################Dijkstra's shortest path#################################################################*/


	/*********************************************************************S-T **************************************************************/

	double * sTOverV(int len,int **shortestPaths){
		
		double *scores = new double[len];
		double score =0;
		for(int k=0; k<len; k++){
			for(int i=0; i<len; i++){
				for (int j = i; j < len; j++)
				{
					if(  (shortestPaths[k][i] != 2147483647) && (shortestPaths[k][j]!=2147483647) && k!=j && k!=i){
						if(shortestPaths[i][j]==0){shortestPaths[i][j]=1;
						}
						if(i==j){
							score += (shortestPaths[k][i] + shortestPaths[k][j])/2;
						}
						else{
							score += (shortestPaths[i][k] + shortestPaths[k][j]) /(double) shortestPaths[i][j];
						}
					}
				}
			}
			scores[k] = score*2;
			score = 0;
		}
		
		return scores;
	}

	/*####################################################################S-T#############################################################*/




	int Important (int n,  int**& edgeList, double *& scores)
	{
		int disconnectedComponents = 0;
		int **res = new int*[n];
		
		for(int i=0; i<n; i++){
			res[i] = new int[n];
		}

		vector<bool> visited(n, false);

		for(int i = 0;i < n;++i) {
			if(visited[i] == false){
				DFS(i,visited,edgeList,n);
	         	disconnectedComponents++;
	     	}
	    }

	    res=dijkstra(edgeList,0,n);
	    for(int i=0; i<n; i++){
	    	for(int j=0; j<n; j++){
	    		cout<<res[i][j]<<" ";
	    	}
	    	cout<<"\n";
	    	
	    }
//	    ustteki res aslında shortest pathler

	    scores=sTOverV(n,res);
	    for(int i=0; i<n; i++){
	    	cout<< "score  ["<<i<<"] :"<<scores[i]<<"\n";
	    }
	    //cout<<"disconnectedComponents: " <<disconnectedComponents<<"\n";

	   	return disconnectedComponents; 
	}


