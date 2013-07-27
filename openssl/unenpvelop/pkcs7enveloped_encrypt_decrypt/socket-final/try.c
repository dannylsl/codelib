#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int addSocketfdToFileName(char *filename,int sockfd);
int main()
{
  char filename[64];
  strcpy(filename,"clientfile.txt");
  addSocketfdToFileName(filename,1);
  printf("filename=%s\n",filename);

  strcpy(filename,"clientfile.txt");
  addSocketfdToFileName(filename,9);
  printf("filename=%s\n",filename);

  strcpy(filename,"clientfile.txt");
  addSocketfdToFileName(filename,10);
  printf("filename=%s\n",filename);
  
  strcpy(filename,"clientfile.txt");
  addSocketfdToFileName(filename,99);
  printf("filename=%s\n",filename);

  strcpy(filename,"clientfile.txt");
  addSocketfdToFileName(filename,199);
  printf("filename=%s\n",filename);

  return 0;
}

//给文件名添加一个数字
int addSocketfdToFileName(char *filename,int sockfd)
{
    char numstr[20][3]={"0\0","1\0","2\0","3\0","4\0","5\0","6\0","7\0","8\0","9\0"};
    int i,bai,shi,ge;
    int first=1,hastype=0;
    //最大999
    if(sockfd>999){printf("invalid number..\n"); return 0;}

    char last[16];
    memset(last,'\0',sizeof(last));
    
    //判断是否有后缀名
    int len=strlen(filename);
    for(i=len-1;i>0;i--)
    {
      if(filename[i]=='.')
        {
            hastype=1;
            break;
        }
    }  
    //有后缀名，先保存后缀名
    if(hastype==1)
    {
      strcpy(last,filename+i);
      memset(filename+i,'\0',strlen(filename)-i);
    }

    //百位
    bai=sockfd/100;
    if(bai>0) { strcat(filename,numstr[bai]); first=0;}
    sockfd=sockfd%100;
    //十位
    shi=sockfd/10;
    if(shi>0) { strcat(filename,numstr[shi]); first=0;}
    else if(shi==0&&first==0){ strcat(filename,numstr[shi]); first=0;}
    sockfd=sockfd%10;
    //个位
    ge=sockfd;
    { strcat(filename,numstr[ge]); first=0;}
 
    //如果原来有后缀名，将后缀名添上
    if(hastype==1)
    {
      strcat(filename,last);
    }
    return 0;

}
