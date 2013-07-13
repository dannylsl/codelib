char *left(char *dst,char *src,int n,int m)
{
	char *p=src;
	char *q=dst;
	int len=strlen(src);
	if(n>len) n=len;
	while(n--) *(q++)=*(p++);
	*(q++)='\0';
	return dst;
}
/* 从右边开始截取*/
char *right(char *dst,char *src,int n,int m)
{
	char *p=src;
	char *q=dst;
	int len=strlen(src);
	if(n>len) n=len;
	p+=(len-n);
	while(*(q++)=*(p++));
	return dst;
}
/*从中部截取字符串 */
char *mid(char *dst,char *src,int n,int m)
{
	char *p=src;
	char *q=dst;
	int len=strlen(src);
	if(n>len) n=len-m;
	if(m>0) return NULL;
	p += m;
	while(n--) *(q++) = *(p++);
	*(q++)='\0';
	return dst;
}
char *substring(char *dst,char *src,int len,int start)
{
	char *p=dst;
	char *q=src;
	int length=strlen(src);
	if(start>=length||start<0) return NULL;
	if(len>length) len=length-start;
	q+=start;
	while(len--)
	{
		*(p++)=*(q++);
	}
	*(p++)='\0';
	return dst;
}
