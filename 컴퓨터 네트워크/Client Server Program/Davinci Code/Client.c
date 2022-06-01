#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int   main( int argc, char **argv)
{
   int   client_socket;
	int index, number;
   struct sockaddr_in   server_addr;

   char   buff[BUFF_SIZE+5];

   client_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == client_socket)
   {
      printf( "socket 생성 실패\n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons( 7000);
   server_addr.sin_addr.s_addr= inet_addr( "127.0.0.1");

   if( -1 == connect( client_socket, (struct sockaddr*)&server_addr,
                           sizeof( server_addr) ) )
   {
      printf( "접속 실패\n");
      exit( 1);
   }
    send( client_socket, argv[1], strlen( argv[1])+1, 0); // +1: NULL까지 포함해서 전송
    recv( client_socket, buff, BUFF_SIZE, 0);
    printf( "%s\n", buff);
    recv( client_socket, buff, BUFF_SIZE, 0);
    printf( "%s\n", buff);
    recv( client_socket, buff, BUFF_SIZE, 0);
    printf( "mine : %s\n", buff);

	
	while(1)
	{
		puts("");
		recv( client_socket, buff, BUFF_SIZE, 0);	
		printf( "others : %s\n", buff);
		puts("");

		recv( client_socket, buff, BUFF_SIZE, 0);	
		printf( "mine : %s\n", buff);
		puts("");	
	
		if(!strcmp(buff, "Lose..\n") || !strcmp(buff, "Win!!\n"))
			exit(1);

		recv( client_socket, buff, BUFF_SIZE, 0);	
		printf( "%s", buff);
		puts("");	

		if(!strcmp(buff, "Your turn\n"))
		{
			printf("Input Index and Number :");
			scanf("%d %d", &index, &number);
			*((int*)buff) = index;
			send(client_socket, buff, 4, 0);
			*((int*)buff) = number;
			send(client_socket, buff, 4, 0);
		}
	}

   close( client_socket);
   
   return 0;
}
