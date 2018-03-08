#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void logprintf();
char* getcgidata(FILE* fp, char* requestmethod);
void dealwithjavaserver();
void error_handling(char *MEG);

int main()
{

  char *input;
  char *req_method;
  char name[64];
  char pass[64];
  int i = 0;
  int j = 0;

  puts("<Content-type:text/html>\n");
  puts("<html>");
  puts("<head>");
  puts("<title>login Successfully</title>");
  puts("</head>");
  puts("<body>");
    logprintf();

    req_method = getenv("REQUEST_METHOD");
    input = getcgidata(stdin, req_method);


  // 我们获取的input字符串可能像如下的形式
  // Username="admin"&Password="aaaaa"
  // 其中"Username="和"&Password="都是固定的
  // 而"admin"和"aaaaa"都是变化的，也是我们要获取的
  // 前面9个字符是UserName=
  // 在"UserName="和"&"之间的是我们要取出来的用户名
	for (i = 9; i < (int)strlen(input); i++)
	{
   		if (input[i] == '&')
   		{
			name[j] = '\0';
			break;
   		}
   		name[j++] = input[i];   
	}

// 前面9个字符 + "&Password="10个字符 + Username的字符数
// 是我们不要的，故省略掉，不拷贝
	for ( i = 19 + strlen(name), j = 0; i < (int)strlen(input); i++ )
	{
    		pass[j++] = input[i];
	}
    		pass[j] = '\0';
  printf("Your Username is %s<br>Your Password is %s<br> \n", name, pass);
  //chuan begin
  dealwithjavaserver();
  //printf("getjavaServer is s%",socketstring);
  

  puts("CGI---Loading---we Are Successed!!!\n\n");
  puts("StephenSoftWare\n");
  puts("</body>");
  puts("</html>");

return 0;
}

char* getcgidata(FILE* fp, char* requestmethod)
{
    char* input;
    int len;
    int size = 1024;
    int i = 0;
   if (!strcmp(requestmethod, "GET"))
   {
	input = getenv("QUERY_STRING");
	return input;
   }
   else if (!strcmp(requestmethod, "POST"))
	{
	 len = atoi(getenv("CONTENT_LENGTH"));
	 input = (char*)malloc(sizeof(char)*(size + 1));
	   if (len == 0)
	   {
	    input[0] = '\0';
	    return input;
	   }
	  while(1)
	  {
	    input[i] = (char)fgetc(fp);
	    if (i == size)
	    {
	      input[i+1] = '\0';
     	      return input;   
	     } 

	   if (feof(fp) || (!(len)))
	   {
	     i++;
	     input[i] = '\0';
	     return input;
	    }
	   i++;
	  }   
	 }
return NULL;
}

void dealwithjavaserver(){
   int server_sock;
	struct sockaddr_in server_addr;
	char* message;
	char readmessage[128];
	int str_len = 0;
	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(server_sock == -1)
	{
		puts("Socket---Failure---we Are Successed!!!<br>\n\n");
	}
	puts("Socket---Open---we Are Successed!!!<br>\n\n");
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(30000);
	if(-1 == connect(server_sock, (struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		puts("Socket---conect---Failure---we Are Successed!!!<br>\n\n");
	}
	puts("Socket---conected---we Are Successed!!!<br>\n\n");

	message = "\n111111\n";
	//printf("C:send the data: %s",message);	
	write(server_sock, message, strlen(message));
	puts("Socket---write---we Are Successed!!!<br>\n\n");
	int goon=1;
	memset(readmessage, 185, sizeof(readmessage));
	//建立连接之后的处理逻辑
			//while(goon)
			//{
				str_len = read(server_sock, readmessage, 128-1);

				readmessage[str_len]=0;
				if(-1 == str_len){
				  puts("Socket---read---we Are Successed!!!<br>\n\n");
				}
				//if(str_len > 0) 
					//goon = 0;
			//}


	 printf("C:Message from server : %s \n", readmessage);
	 close(server_sock);

	//断开连接，关闭套接字	
}

void logprintf()
{
	printf("REQUEST_METHOD=%s<br> \n", getenv("REQUEST_METHOD"));
	printf("SERVER_ADDR=%s<br> \n", getenv("SERVER_ADDR"));
	printf("SERVER_PROTOCOL=%s<br> \n", getenv("SERVER_PROTOCOL"));
	printf("REQUEST_URI=%s<br> \n", getenv("REQUEST_URI"));
	printf("PATH_INFO=%s<br> \n", getenv("PATH_INFO"));
	printf("PATH_TRANSLATED=%s<br> \n", getenv("PATH_TRANSLATED"));
	printf("SCRIPT_NAME=%s<br> \n", getenv("SCRIPT_NAME"));
	printf("QUERY_STRING=%s<br> \n", getenv("QUERY_STRING"));
	printf("REMOTE_ADDR=%s<br> \n", getenv("REMOTE_ADDR"));
	printf("REMOTE_PORT=%s<br> \n", getenv("REMOTE_PORT"));
	printf("CONTENT_TYPE=%s<br> \n", getenv("CONTENT_TYPE"));
	printf("CONTENT_LENGTH=%s<br> \n", getenv("CONTENT_LENGTH"));
	printf("HTTP_ACCEPT=%s<br> \n", getenv("HTTP_ACCEPT"));
}
