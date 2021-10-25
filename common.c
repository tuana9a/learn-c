

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <string.h>
#include <math.h>

//--------------- ĐỌC SỐ TỪ FILE ---------------------

//NOTE hàm ngay dưới chỉ để hỗ trợ hàm getOneIntFromFile
int readNumberInFile(FILE *inputFile, char firstNotation){
	int result = firstNotation -'0';
	char c;
	while(isdigit(c = fgetc(inputFile))){
		result = result*10 + c - '0';
	};
	return result;
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

//--------------- XỬ LÝ XÂU ---------------------------

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

//--------------- CÁC HÀM SORT ------------------------

void swap(int* x, int* y) {
	int temp = *x;
	*x = *y;
	*y = temp;
}
void quickSort_SGK(int a[], int start, int end) {
	if(start >= end) return;
	int chosenOne  = a[start];
	int i = start;
	int j = end;
	while(i < j) {
		while(a[i] <= chosenOne && i <= end  ) i++;
		while(a[j] >  chosenOne && j >= start) j--;
		if(i < j) swap(&a[i++] , &a[j--]);
	}
	swap(&a[start],&a[j]);// đoạn swap này max hay khi swap thì không làm thay đổi thứ tự tăng dần của dãy không ngu như mình
	quickSort_SGK(a,start,j-1);
	quickSort_SGK(a,j+1,end);
}


//--------------- CÁC HÀM IN  ------------------------

void printOneDimArray(int length, int a[]){
	printf("OneDimArray:\n");
	for(int i=0;i<length;++i) {
		printf(i==length-1?"%d":"%d ",a[i]);
	}
	printf("\n");
}
void printTwoDimArray(int length, int height, int a[][length]){
	printf("TwoDimArray:\n");
	for(int i=0;i<height;++i) {
		for (int j = 0; j < length; ++j)
		{
			printf(i==length-1?"%d\n":"%d ",a[i][j]);
		} 
	}
	printf("\n");
}

//--------------- THAO TÁC VỚI MẢNGk  ------------------------

void copyOneDimArray(int length,int copied[],int origin[]) {
	for(int i=0;i<length;++i) {
		copied[i] = origin[i];
	}
}
void copyTwoDimArray(int length,int height,int copied[][length],int origin[][length]) {
	for(int i=0;i<height;++i) for(int j=0;j<length;++j) copied[i][j] = origin[i][j];
}
void initOneDimArray(int length, int a[]) {
	for(int i=0;i<length;++i) a[i] = 0;
}
void initTwoDimArray(int length, int heigth, int a[][length]) {
	for(int i=0;i<length;++i) for(int j=0;j<length;++j) a[i][j] = 0;
}

//--------------- CẤU TRÚC HÀNG ĐỢI ------------------------

struct QUEUE_NODE {
	int apex;
	struct QUEUE_NODE* next;
};
typedef struct QUEUE_NODE QUEUE_NODE;

QUEUE_NODE* newNodeQueue(int newApex) {
	QUEUE_NODE* new = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	(*new).apex = newApex;
	(*new).next = NULL;
	return new;
}
void insertToQueue(QUEUE_NODE* startQueue, int newApex){
	QUEUE_NODE* temp = startQueue;
	while((*temp).next != NULL) temp = (*temp).next;
	(*temp).next = newNodeQueue(newApex);
}
void popQueueStart(QUEUE_NODE** startQueue) {
	//phải dùng con trỏ cấp 2 vì mình đang thay đổi giá trị của nó, trỏ sang vùng nhớ khác :V
	QUEUE_NODE* temp = (*startQueue);
	*startQueue = (**startQueue).next;
	free(temp);
}
void popQueueEnd(QUEUE_NODE* startQueue) {
	QUEUE_NODE* temp = startQueue;
	while(temp!= NULL) {
		QUEUE_NODE* nextTemp = (*temp).next;
		if((*nextTemp).next == NULL) {
			free(nextTemp);
			(*temp).next = NULL;
			return;
		}
	}
}
void printQueue(QUEUE_NODE* startQueue) {
	QUEUE_NODE* temp = startQueue;
	printf("InQueue |");
	do{
		printf((*temp).next==NULL?"%d":"%d -> ",(*temp).apex);
		temp = (*temp).next;
	}
	while(temp!=NULL);
	printf("|\n");
}
void popQueueSpecific(QUEUE_NODE * startQueue, int pos) {
	int i = 0;
	QUEUE_NODE* temp = startQueue;
	QUEUE_NODE* prevNode = startQueue;
	while((*temp).next != NULL && i < pos) {
		prevNode = temp;
		temp = (*temp).next;
		++i;
	}
	(*prevNode).next = (*temp).next;
	free(temp);
}


//--------------- CẤU TRÚC CÂY ------------------------

struct TREE_NODE {
	int apex;
	struct TREE_NODE* child;
	struct TREE_NODE* sibling;
};
typedef struct TREE_NODE TREE_NODE;

TREE_NODE* newTreeNode(int whichApex) {
	TREE_NODE* new = (TREE_NODE*)malloc(sizeof(TREE_NODE));
	(*new).apex = whichApex;
	(*new).child = NULL;
	(*new).sibling = NULL;
	return new;
}
//NOTE những cái trong comment là trường hợp mà đi xóa hết tất cả quan hệ cha con (kể cả một con những nhiều cha nhưng đây là cây thê lên là ko hợp lý)
//void deleteChild(TREE_NODE* resultTree[], TREE_NODE* currentNode, int childToDelete) {
void deleteChild(TREE_NODE* resultTree[], TREE_NODE* currentNode, int childToDelete, int* stop) {
	//if((*stop) == 0) return;
	if((*stop) == 0) return;
	TREE_NODE* tempChild = (*currentNode).child;
	TREE_NODE* prevChild;
	int childCount=0;
	while(tempChild != NULL) {
		if((*tempChild).apex == childToDelete) {
			//*stop = 0;
			*stop = 0;

			if(childCount == 0) (*currentNode).child = (*tempChild).sibling;
			else (*prevChild).sibling = (*tempChild).sibling;
			
			(*tempChild).sibling = NULL;
			//return;  
			return;  
		}
		childCount++;
		prevChild = tempChild;
		tempChild = (*tempChild).sibling;
	}

	//if((*currentNode).child != NULL) deleteChild(resultTree,(*currentNode).child,childToDelete);
	//if((*currentNode).sibling != NULL) deleteChild(resultTree,(*currentNode).sibling,childToDelete);
	if((*currentNode).child != NULL) deleteChild(resultTree,(*currentNode).child,childToDelete,stop);
	if((*currentNode).sibling != NULL) deleteChild(resultTree,(*currentNode).sibling,childToDelete,stop);
}
void appendChild(TREE_NODE* resultTree[], int whichChild, int dad) {
	TREE_NODE* tempChild = (*resultTree[dad]).child;
	if(tempChild == NULL) {
		(*resultTree[dad]).child = resultTree[whichChild];
		return;
	}
	while((*tempChild).sibling != NULL) {
		tempChild = (*tempChild).sibling;
	}
	(*tempChild).sibling = resultTree[whichChild];
}
int startApex = 1;
void changeDad(TREE_NODE* resultTree[],int child, int dad) {
	int stop=1;
	//deleteChild(resultTree,resultTree[startApex],child);
	deleteChild(resultTree,resultTree[startApex],child,&stop);
	appendChild(resultTree,child,dad);
}

//--------------- OTHER ------------------------------
//cách random
// #include<time.h>
// #include<stdlib.h>
// srand(time(NULL));
// pruferCode[i]= rand() % (soCanh); 




