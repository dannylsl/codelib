/**
 * FileName : fileClient.c
 * Author   : Danny Lee
 * Email    : dannylsl@hotmail.com
 * Date     : 2013-07-11  21:00PM
 * Brief    :
 *  file transform client between C language and python server
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <wait.h>

#define BUFSIZE     1024
#define PORT        6000
#define INFOSIZE    64


void infoInit(char *info,const char ch,int len){
    int i;
    for(i = 0;i < len; i++){
        info[i] = ch;
    }
}

int infoDeal(const char* filename,char * Info){
    struct stat sb; // stat buffer
    int fsize;
    char fileInfo[INFOSIZE+1];
    char tmp[INFOSIZE+1];

    memset(fileInfo,0,INFOSIZE+1);
    memset(tmp,0,INFOSIZE+1);
    infoInit(fileInfo,'#',INFOSIZE);

    //Get file Size
    stat(filename,&sb);
    fsize = (int)sb.st_size;

    sprintf(tmp,"#%s$%d",filename,fsize);

//  printf("BEFORE:fileInfo = %s\n",fileInfo);
//  printf("BEFORE:tmp      = %s\n",tmp);
    strncpy(fileInfo,tmp,strlen(tmp));
//  printf("AFTER :fileInfo = %s\n",fileInfo);
    strcpy(Info,fileInfo);
    return 0;
}

int sendInfo(int sockfd,char * fileInfo){
    int number_bytes;

    if(strlen(fileInfo) != INFOSIZE){   
        printf("fileInfo length is illegal\n");
        exit(EXIT_FAILURE);
    }else{
        if(-1 == (number_bytes = send(sockfd, fileInfo, INFOSIZE,0))){
        //if(-1 == (number_bytes = send(sockfd, fileInfo, number_bytes,0))){
        // [BUG FIXED]   number_bytes ==> INFOSIZE
        //      date : 2013-07-13 00:43 
            perror("send error");   
            return -1; 
        }else{
            return 0;   
        }   
    }
}

int recvInfo(int sockfd, char *fileInfo){
    int number_bytes;

    memset(fileInfo,0,INFOSIZE);
    if(-1 == (number_bytes = recv(sockfd, fileInfo, INFOSIZE,0))){
        perror("recv error");           
        return -1;
    }
    if(number_bytes != INFOSIZE){
        printf("fileInfo recv error\n");    
        return -1;
    }
    return 0;

}

void infoRmEnd(char *fileInfo,int len){
    int i;  
    for(i = len-1; i > 0; i--){
        if(fileInfo[i] == '#')  
            fileInfo[i] = 0;
        else //fileInfo[i] != 0
            break;
    }
}

int infoParse(char* fileInfo,char * filename,int * filesize){

    char fname[30];
    char fsize[30];

    memset(fname,0,30);
    memset(fsize,0,30);
    
    //printf("BEFORE:%s\n",fileInfo);   
    infoRmEnd(fileInfo,INFOSIZE);
    //printf("AFTER:%s fileInfo len=%d\n",fileInfo,strlen(fileInfo));   

    strncpy(fname,fileInfo+1,strchr(fileInfo,'$')-fileInfo-1);  
    strcpy(fsize,strchr(fileInfo,'$')+1);

    //printf("FileName:%s\n",fname);
    //printf("Filesize:%s\n",fsize);

    strcpy(filename,fname);
    *filesize = atoi(fsize);
    return 0;

}

ssize_t sendfile(int sockfd, char * filename){
        
    FILE *fp;
    char sendbuf[BUFSIZE];
    ssize_t number_bytes = 0;
    int ret;

    if(NULL == (fp = fopen(filename,"rb"))){
        perror("sendfile() file open failed!\n");               
        ret = 0;
        //exit(EXIT_FAILURE);
    }else{
        while(!feof(fp)){
            memset(sendbuf,0,BUFSIZE);  
            number_bytes = fread(sendbuf,1,BUFSIZE,fp);
            if(-1==(number_bytes = send(sockfd,sendbuf,number_bytes,0))){
                perror("send error");       
                ret = -1; 
                fclose(fp);
                return ret;
            //  exit(EXIT_FAILURE);
            };
            printf("number_bytes=%d\n%s",number_bytes,sendbuf);
        }           
        ret = 1;
    }   
    fclose(fp);
    return ret;
}

ssize_t recvfile(int sockfd,const char * filename,int filesize){
    FILE *fp;   
    char recvbuf[BUFSIZE];
    ssize_t number_bytes;
    int ret,restsize;

    restsize = filesize;

    if(NULL==(fp = fopen(filename,"wb"))){
        perror("recvfile    failed to open ");
        ret = 0;
    }else{
        while(1){   
            memset(recvbuf,0,BUFSIZE);  
            if(restsize > BUFSIZE ){
                if((number_bytes = recv(sockfd, recvbuf, BUFSIZE,0))==-1){
                    perror("recvfile    recv() error");
                    fclose(fp);
                    return -1;
                }else{
                    fwrite(recvbuf,1,number_bytes,fp);              
                    restsize -= number_bytes;
                }
            }else if(restsize == 0){
                break;
            }else{
                if((number_bytes = recv(sockfd, recvbuf, restsize,0)) == -1){
                    perror("recvfile    recv() error");
                    fclose(fp);
                    return -1;
                }else{
                    fwrite(recvbuf,1,number_bytes, fp); 
                    restsize -= number_bytes;
                }
            }
        }
        fclose(fp);
    }   
    return ret;
}

int main(int argc, char* argv[]){
    int sockfd;
    int conn_ret;
    struct sockaddr_in servaddr;
    char filename[64];
    char recvname[64];
    char recvbuf[BUFSIZE];
    ssize_t number_bytes;
    char fileInfo[INFOSIZE+1];
    int fsize;
    FILE *fp;


    if(argc != 3){
        printf("Usage: %s <address> <file2send>\n",argv[0]);
        return 0;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(PORT);
    inet_pton(AF_INET,argv[1], &servaddr.sin_addr);

    if((sockfd = socket(AF_INET, SOCK_STREAM,0 )) == -1){
        perror("SOCKET ERROR");
        exit(EXIT_FAILURE);
    }

    conn_ret = connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(conn_ret == -1){
        perror("CONNECT ERROR");
        exit(EXIT_FAILURE);
    }

    printf("starting...\n");
//  infoDeal("abc.txt",fileInfo);
    infoDeal(argv[2],fileInfo);
    printf("fileInfo:%s\n",fileInfo);
    sendInfo(sockfd,fileInfo);
    sendfile(sockfd,argv[2]);


    recvInfo(sockfd,fileInfo);  
    printf("recv fileInfo:%s\n",fileInfo);

    infoParse(fileInfo,filename,&fsize);
    printf("recv filename: %s   filesize:%d\n",filename,fsize);
    recvfile(sockfd,filename,fsize);

    close(conn_ret);
}


