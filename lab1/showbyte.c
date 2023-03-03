# include <stdio.h>
# include <stdlib.h>
# include <string.h> 

int main() 
{
	FILE *fp = fopen("hello.c", "r"); // 文件指针
	if (fp == NULL) 
    	{
        printf("file open error!\n");
		return 0;
	}
	int len = 0;
	int i;
	
	// 获取文件长度
	fseek(fp, 0, SEEK_END);	// 文件指针移到末尾
	len = ftell(fp);	// 获取文件长度
	rewind(fp);		// 将文件指针移到开头
		
    char * buf = (char *)malloc(len + 1);	// char为1字节
	// 将缓冲区初始化为0
	for(i = 0; i < len + 1; i ++)
		buf[i] = 0;
	int k = fread(buf, 1, len, fp);
	fclose(fp);		// 关闭文件 
	int buf_len = strlen(buf);


	//printf("fread: %d\n", k);
	//printf("file_len: %d\n", len);
	//printf("strlen(buf): %d\n", buf_len);
	// 读取正常时 k == len == buf_len

	int flag = 0;	// 0为字母行，1为数字行 
	int end = 0;    // 0为未到最后一行，1为到
	for(i = 0; i < buf_len; i++) 
	{
		if(i != 0 && i % 16 == 0 && end == 0) 
		{
			printf("\n");
			if(flag == 0) i -= 16;
			flag = !flag;
		}
		if (!flag) // 0 状态打印字母 
		{	
			if(buf[i] == ' ') printf("SP\t");
			else if(buf[i] == '\n') printf("\\n\t");// \t \n 都需要转义
			else if(buf[i] == '\t') printf("\\t\t");
			else printf("%c\t", buf[i]);
		}else // 1 状态打印ASCII码
		{			
			if(buf[i] == ' ') printf("%d\t", ' ');
			else if(buf[i] == '\n') printf("%d\t", '\n');
			else if(buf[i] == '\t') printf("%d\t", '\t');
			else printf("%d\t", buf[i]);
		}
		if(i + 1 == buf_len && !end) // 最后不够16个字母的要特殊处理
		{	
			printf("\n");
			i -= (buf_len % 16);
			flag = !flag;
			end = 1;
		}
	}
	printf("\n");	
	free(buf);
	return 0;
}
