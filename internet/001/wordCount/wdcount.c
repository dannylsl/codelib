/**
 * FileName	: wdcount.c
 * Author	: Danny Lee
 * Email	: dannylsl@pku.edu.cn
 * StudentID: 1201210660
 *
 * Description : 
 *	The program is used to count words in a document,and output 
 *	the word by its appearaence time.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "substring.h"

#define MAX_LEN_WORD		64 
#define MAX_LEN_FILENAME	64
#define MAX_LEN_FILETYPE	10
#define HYPHEN				'-'  // Different about minus

typedef struct wNode{
	char word[MAX_LEN_WORD];	// Longest word length is 	
	int count;					// The appearance time 
	struct wNode* next;
}wNode;

void usage(){
	printf("Usage: wdcount [FileName][.FileType]\n");
	printf("Example:\n\twdcount file.txt\n");
	printf("[FileType]\n");
	printf("\tFileType is optional!\n\tSupport Type:txt\n\n");
}

// Check the word is exist or not
// if yes modify the Node.count+=1 and return 1
// else return 0
int IsExist(wNode*ptrHead,const char* word){
	while(ptrHead != NULL){
		if( strcasecmp(ptrHead->word,word) == 0 ){
			ptrHead->count+=1;
//			printf("Word:%s\tcount:%d\n",ptrHead->word,ptrHead->count);
			return 1;
		}else{
			ptrHead = ptrHead->next;
		}
	}	
	return 0;
}
// OutPut Link
void outPut(wNode*ptrHead){
	int i=1;
	while(ptrHead != NULL){
		printf("%d:%s\tcount:%d\n",i,ptrHead->word,ptrHead->count);
		ptrHead = ptrHead->next; 
		i++;
	}	
}

void PrintArr(wNode*nodeArr,int count){
	int i = 0;	
	for(i = 0; i < count; i++){
		printf("No.%d\tword: %-20scount:%d\n",i+1,nodeArr[i].word,nodeArr[i].count);	
	}
}

int main(int argc, char*argv[]){

	char fileName[MAX_LEN_FILENAME]; 
	char fileType[MAX_LEN_FILETYPE];
	char *res;
	int start=0,len=0;
	FILE* fp;
	char ch,flag=0;		// check word is complete or not [1:Yes  0:No]
	char word[MAX_LEN_WORD];
	char* nonTextSymbol = ".,:?!\'\"~%*()$#<>-1234567890";
	char* space="\n \t";
	//char* space=" ";
	int i,j,wId=0;		//Word Id
	int count,maxCnt;
	wNode *tmpwNode,*head=NULL,*curptr=NULL,*endptr=NULL,*pnext;
	wNode *nodeArr,wNode;
	
	memset(fileName,'\0',MAX_LEN_FILENAME);
	memset(fileType,'\0',MAX_LEN_FILETYPE);
	memset(word,'\0',MAX_LEN_WORD);

	if( argc != 2){
		printf("Argument is uncorrect.\n");
		usage();
		return 0;
	}

	if( strpbrk(argv[1],".") == NULL ){
		strcpy(fileName,argv[1]);
		printf("%s",argv[1]);
	}else{
		start = (int)(strrchr(argv[1],'.')-argv[1]) + 1;
		len   = strlen(argv[1]) -(int)(strrchr(argv[1],'.')-argv[1]);
	//	printf("start:%d\tlen:%d\n",start,len);

		if(substring(fileType,argv[1],len,start)){  /* Get the string behind '.'*/
			// Get the FileType
			printf("FileType:[%s]\n",fileType);

			if( strcmp(fileType,"txt")){					/*FileType invalidate */
				printf("FileType[%s] is not supported!\n ",fileType);			
				usage();
				return 0;		
			}else{
				strcpy(fileName,argv[1]);	
			}
		}	
	}
	printf("FileName:%s\n",fileName);

	//File Operation
	if(NULL==(fp=fopen(fileName,"rw+"))){
		printf("Error while open File[%s]\n",fileName);
		return 0;
	}

	printf("Successed to Open File[%s]\n",fileName);
			
	i = 0;
	while((ch = fgetc(fp)) != EOF){

		if( strchr(space,ch) != 0 ){
		// space found
	    //		count++;
			word[i]='\0';
			i=0;

			if(IsExist(head,word)==0 && strcmp(word,"")){ // NOT EXIST AND WORD != ""

				tmpwNode = (wNode*)malloc(sizeof(wNode));
				tmpwNode->count = 1;
				strcpy(tmpwNode->word,word);	
				//printf("word:%s\ttmpwNode->word:%s\n",word,tmpwNode->word);
				memset(word,'\0',MAX_LEN_WORD);

				if(wId == 0){	// THE FIRST WORD

					head	= tmpwNode;
					curptr	= tmpwNode; 
					wId++;
//					printf("word%d:%s\n",wId,head->word);
				}else{
					curptr->next = tmpwNode; 
					curptr = tmpwNode;
					wId++;
//					printf("word%d:%s\n",wId,curptr->word);
				}	
			};
			memset(word,'\0',MAX_LEN_WORD);

		}else if(strchr(nonTextSymbol,ch) != 0){
		// non-text symbol found		
		//	printf("nonText Symbol Found\n");
			continue;
		
		}else{
			word[i]=ch;		
			i++;
		}
	}

	nodeArr = (wNode*)malloc(wId*sizeof(wNode));
	curptr = head;
	for(i=0;i<wId;i++){
		strcpy(nodeArr[i].word,curptr->word); 
		nodeArr[i].count = curptr->count; 
		tmpwNode = curptr; 
		curptr = curptr->next;
		free(tmpwNode);
	}

	// RANK
	for(i = wId;i >= 0; i--){
		for(j=0;j < i-1;j++){
			if(nodeArr[j].count < nodeArr[j+1].count){
				wnode = nodeArr[j+1];	
				nodeArr[j+1] = nodeArr[j];
				nodeArr[j] = wnode;
			}else{
				continue;
			}	
		}
	}
	PrintArr(nodeArr,wId);	
 
	fclose(fp);
	return 0;
}

