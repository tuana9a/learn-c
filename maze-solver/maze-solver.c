// cd Dropbox\vmware\cProgramming\bigExcercise\findPath\


#include <stdio.h>
//#include <stdlib.h>
#include <ctype.h>
#include <string.h>



int width,height;


int readNumberInFile(FILE *inputFile, char firstNotation){
	int result = firstNotation -'0';
	char c;
	while(isdigit(c = fgetc(inputFile))){
		result = result*10 + c - '0';
	};
	return result;
}
void reveseString (char *string){
	int stringLength = strlen(string);
	for(int i=0;i<stringLength/2;++i){
		char temp = string[i];
		string[i]=string[stringLength-i-1];
		string[stringLength-i-1]=temp;
	}
	string[stringLength]='\0';
}
char* numToString(int num,char *outString){
	int i;
	for(i=0;num>0;++i,num/=10) {
		outString[i]=num%10 + '0';
		//printf("%d\n",outString[i]%10 + '0');
	}
	outString[i]='\0';
	reveseString(outString);
	return outString;
}


int getOneIntFromFile(FILE* inputFile){
	int result=0;
	char c;
	while((c = fgetc(inputFile)) != EOF){
		if(isdigit(c)) {
			return readNumberInFile(inputFile,c);
		}
	}
	return EOF;
}
void readMapInFile(FILE *inputFile,int  originMap[][width]){
	int tempPos=0;

	while(1){
		int tempNum = getOneIntFromFile(inputFile);
		//printf("tempNum:%d -- tempPos:%d\n",tempNum,tempPos/width);
		if(tempNum == EOF) return;
		originMap[tempPos/width][tempPos%width]=tempNum==0?-1:0;//0 la bi chan -1 la di duoc
		tempPos++;
	}
}
void readMapInFileNice(FILE *inputFile,int  originMap[][width]){
	// int tempPos=0;
	int tempLine=0;
	int tempCol=0;
	char c;
	//printf("Entered\n");
	for(int i=0;i<height;++i) for(int j=0;j<width;++j) originMap[i][j]=0;//0 la bi chan -1 la di duoc
	tempCol++;

	while((c=fgetc(inputFile)) != '|'){}
	//tempCol++;
	//printf("%c -- %d -- %d\n",c,tempLine,tempCol);

	while((c=fgetc(inputFile)) != EOF) {
		if(c == ' ') {
			originMap[tempLine][tempCol]= -1;
			originMap[tempLine-1][tempCol]= -1;
			tempCol++;
		}
		if(c == '_') {
			originMap[tempLine-1][tempCol]= -1;
			tempCol++;
		}
		if(c =='\n') {
			tempCol=0;
			tempLine+=2;
		}
		if(c == '|') tempCol++;
	}
}



void copyMap(int fakeMap[][width] , int originMap[][width]){
	for(int i=0;i<height;++i)
		for(int j=0;j<width;++j)
			fakeMap[i][j] = originMap[i][j]; 
}
void printMap(int mapToPrint[][width]){
	for(int i=0;i<height;++i) {
		for(int j=0;j<width;++j) printf("%2d",mapToPrint[i][j]);
		printf("\n");
	}
}
void printMapNice(int mapToPrint[][width]) {
	for(int i=0;i<height;++i) {
		for(int j=0;j<width;++j) 
			switch(mapToPrint[i][j]) {
				case 0: printf("HH");break;// 0 la bi chan
				case -1:printf("  ");break;// -1 la di duoc
				default:printf("* ");break;// buoc di				
			}
		printf("\n");
	}	
}


// this algoristhm try to go any path as it can, out put only the way that correct
void mazeRunner_tryAll(int currentMap[height][width],int currentX,int currentY, int currentStep) { //X,Y bat dau tu 0, X:ngang   Y:doc
	//printf("%d\n",currentMap[currentY][currentX]);
	if(
		currentMap[currentY][currentX]!=-1 	||
		//currentMap[currentY][currentX]!=-1 	||
		currentX==width 					||
		currentY==height 					|| 
		currentX == -1 						|| 
		currentY == -1
	) {
		//printf("(x,y):(%d,%d)\n",currentX,currentY);
		//printf("Failed\n");
		return;
	}
	if(currentX == 5  && currentY == height-1) {
	//if(currentStep==9) {
		printf("Found\n");
		currentMap[currentY][currentX]=currentStep;
		//printMap(currentMap);
		printMapNice(currentMap);
		printf("\n");
		return;
	}
	//printf("ok\n");
	currentMap[currentY][currentX]=currentStep;
	int tempMap[4][height][width];
	for(int i=0;i<4;++i) {
		copyMap(tempMap[i],currentMap);
	}
	mazeRunner_tryAll(tempMap[0],currentX+1,currentY,currentStep+1);
	mazeRunner_tryAll(tempMap[1],currentX-1,currentY,currentStep+1);
	mazeRunner_tryAll(tempMap[2],currentX,currentY+1,currentStep+1);
	mazeRunner_tryAll(tempMap[3],currentX,currentY-1,currentStep+1);
}


int main(int argc, char const *argv[])
{
	FILE* inputFile = fopen("input-map.txt","r");
	width = getOneIntFromFile(inputFile);
	height = getOneIntFromFile(inputFile);

	printf("width:%d\nheight:%d\n",width,height);
	
	int originMap[height][width];
	int fakeMap[height][width];

	//readMapInFile(inputFile, originMap);
	readMapInFileNice(inputFile, originMap);
	//copyMap(fakeMap,originMap);

	printMap(originMap);
	printf("\n");
	printMapNice(originMap);
	printf("\n");
	//printMap(fakeMap);
	printf("============================================================\n");
	mazeRunner_tryAll(originMap,5,0,1);

	printf("END!\n");
	return 0;
}






