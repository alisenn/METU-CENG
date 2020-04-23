#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

int main(){

	FILE * filerecv = fopen("recv_3.txt","r");
	FILE * filesend = fopen("send_3.txt","r");

	long recv[3000];
	long send[3000];

	for(int i = 0; i < 3000; i++){
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
	long temp;
	for(int i = 0; i < 3000; i++){
		if(send[i] != -1 && recv[i] != -1){
			temp = recv[i]-send[i];
			cout << temp << endl;
		}
	}


	return 0;
}
