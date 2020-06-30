#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

int main(){


	string list[8] = {"r1d","r1s","r2d","r2s","r3d","r3s","r2r1","r2r3"};
	string postfixrecv = "_recv.txt";
	string postfixsend = "_send.txt";
	for(int j = 0; j < 8; j++){

	FILE * filerecv = fopen((list[j]+postfixrecv).c_str(),"r");
	FILE * filesend = fopen((list[j]+postfixsend).c_str(),"r");

	long recv[1000];
	long send[1000];

	for(int i = 0; i < 1000; i++){
		send[i] = -1;
		recv[i] = -1;
	}

	int package;
	long time;
	while(fscanf(filerecv,"%d %ld",&package,&time) == 2){
		recv[package] = time;
	}
	while(fscanf(filesend,"%d %ld",&package,&time) == 2){
		send[package] = time;
	}
	long sum = 0;
	long count = 0;

	for(int i = 0; i < 1000; i++){
		if(send[i] != -1 && recv[i] != -1){
			sum += recv[i]-send[i];
			count++;
		}
	}

	double avg = (double)sum/count;

	printf("%s\t%lf\n", list[j].c_str(), avg);

	}



	return 0;
}
