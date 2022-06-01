#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define  BUFF_SIZE   1024
int player[3][24], player1[3][24], block[2][12]; 
int player_num=0, player1_num=0, end=0, end1=0, count=0, first=0;
char   buff_rcv[BUFF_SIZE+5];
char   buff_snd[BUFF_SIZE+5];
char   message[BUFF_SIZE];
int new[2][2];
int   client_socket;
int   client_socket1;
	char player_name[20], player1_name[20];
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Allocation_f(int who)
{
	int i=0,j=0;

   srand((unsigned)time(NULL) + (unsigned)getpid());

   while(1)
  {
	  int color, number;
	  color = rand()%2; number = rand()%12;
	  if(!block[color][number])
	  {
		if(who==0)
		{
			player[j++][i] = color;
			player[j--][i] = number;
			player_num++; end++;
		}
		else
		{
			player1[j++][i] = color;
			player1[j--][i] = number;	
			player1_num++; end1++;	
		}
		block[color][number]++;
		i++;
	  }
	  if(i==4) break;
  }
}

void Allocation(int who)
{
	int i,j=0;

	if(who == 0)
		i = player_num;
	else
		i = player1_num;

   srand((unsigned)time(NULL) + (unsigned)getpid());

   while(1)
  {
	  int color, number;
	  color = rand()%2; number = rand()%12;
	  if(!block[color][number])
	  {
		if(who==0)
		{
			player[j++][i] = color;
			player[j--][i] = number;
			new[0][0] = color; new[0][1] = number;
			player_num++; end++;
		}
		else
		{
			player1[j++][i] = color;
			player1[j--][i] = number;
			new[1][0] = color; new[1][1] = number;	
			player1_num++; end1++;	
		}
		block[color][number]++;
	
	  }
	  if(i+1 == player_num || i+1 == player1_num) break;
  }
}

void Sort(int who)
{
	int i,j;

	if(who==0)
	{
		for(i=0; i<player_num-1; i++)
			for(j=0; j<player_num-1-i; j++)
			{
				if(player[1][j] > player[1][j+1])
				{
					swap(&player[2][j], &player[2][j+1]);
					swap(&player[1][j], &player[1][j+1]);
					swap(&player[0][j], &player[0][j+1]);
				}

				else if(player[1][j] == player[1][j+1] && player[0][j] > player[0][j+1])
				{
					swap(&player[2][j], &player[2][j+1]);
					swap(&player[1][j], &player[1][j+1]);
					swap(&player[0][j], &player[0][j+1]);
				}
			}
	}

	else
	{
		for(i=0; i<player1_num-1; i++)
			for(j=0; j<player1_num-1-i; j++)
			{
				if(player1[1][j] > player1[1][j+1])
				{
					swap(&player1[2][j], &player1[2][j+1]);
					swap(&player1[1][j], &player1[1][j+1]);
					swap(&player1[0][j], &player1[0][j+1]);
				}

				else if(player1[1][j] == player1[1][j+1] && player1[0][j] > player1[0][j+1])
				{
					swap(&player1[2][j], &player1[2][j+1]);
					swap(&player1[1][j], &player1[1][j+1]);
					swap(&player1[0][j], &player1[0][j+1]);
				}
			}
	}
}

void Make_Message(int who)
{
	int i;
	if(who==0)
	{	
	   memset(message, 0, sizeof(message));
		for(i=0; i<player_num; i++)
		{
			if(player[2][i] == 0)
			{
				if(player[0][i] == 0)
					sprintf(buff_snd, " B%d  ", player[1][i]);
				else
					sprintf(buff_snd, " W%d  ", player[1][i]);

				strcat(message,buff_snd);
			}
			else
			{
				if(player[0][i] == 0)
					sprintf(buff_snd, "|B%d|  ", player[1][i]);
				else
					sprintf(buff_snd, "|W%d|  ", player[1][i]);

				strcat(message,buff_snd);				
			}			
			
		}	
	}
	else
	{
	   memset(message, 0, sizeof(message));
		for(i=0; i<player1_num; i++)
		{
			if(player1[2][i] == 0)
			{
				if(player1[0][i] == 0)
					sprintf(buff_snd, " B%d  ", player1[1][i]);
				else
					sprintf(buff_snd, " W%d  ", player1[1][i]);

				strcat(message,buff_snd);
			}
			else
			{
				if(player1[0][i] == 0)
					sprintf(buff_snd, "|B%d|  ", player1[1][i]);
				else
					sprintf(buff_snd, "|W%d|  ", player1[1][i]);

				strcat(message,buff_snd);				
			}
		}		
	}
}

void Make_Message_Other(int who)
{
	int i;
	if(who==0)
	{	
	   memset(message, 0, sizeof(message));
		for(i=0; i<player1_num; i++)
		{
			if(player1[2][i] == 0)
			{
				if(player1[0][i] == 0)
					sprintf(buff_snd, " B  ");
				else
					sprintf(buff_snd, " W  ");

				strcat(message,buff_snd);
			}
			else
			{
				if(player1[0][i] == 0)
					sprintf(buff_snd, "|B%d|  ", player1[1][i]);
				else
					sprintf(buff_snd, "|W%d|  ", player1[1][i]);

				strcat(message,buff_snd);				
			}
		}	
	}
	else
	{

	   memset(message, 0, sizeof(message));
		for(i=0; i<player_num; i++)
		{
			if(player[2][i] == 0)
			{
				if(player[0][i] == 0)
					sprintf(buff_snd, " B  ");
				else
					sprintf(buff_snd, " W  ");

				strcat(message,buff_snd);
			}
			else
			{
				if(player[0][i] == 0)
					sprintf(buff_snd, "|B%d|  ", player[1][i]);
				else
					sprintf(buff_snd, "|W%d|  ", player[1][i]);

				strcat(message,buff_snd);				
			}				
		}		
	}
}

void Turn(int who)
{
	int index, guess;
	if(who == 0)
	{
		memset(message, 0, sizeof(message));
		Make_Message_Other(0);
		send( client_socket, message, strlen(message)+1, 0);	

		sleep(1);
	    memset(message, 0, sizeof(message));
		if(first==0)
		{
			Allocation(0);
			Sort(0);
		}
		Make_Message(0);
		printf("%s : %s\n", player_name, message);
		send( client_socket, message, strlen(message)+1, 0);

		sleep(1);
		sprintf(buff_snd, "Your turn\n");
		send( client_socket, buff_snd, strlen( buff_snd)+1, 0);

		recv  ( client_socket, buff_rcv, 4, 0);
		index = *buff_rcv;
		recv  ( client_socket, buff_rcv, 4, 0);
		guess = *buff_rcv;

		if(player1[1][index-1] == guess)
		{
			player1[2][index-1] = 1;

			if(--end1 <= 0)
			{
				printf("Winner : A\n");
				sprintf(message, "Win!!\n");
				send( client_socket, message, strlen(message)+1, 0);
				sprintf(message, "Lose..\n");
				send( client_socket1, message, strlen(message)+1, 0);
				close( client_socket);
     			close( client_socket1);
				exit(1);
			}
			first++;
			Make_Message_Other(1);
			send( client_socket1, message, strlen(message)+1, 0);
			sleep(1);
			Make_Message(1);
			send( client_socket1, message, strlen(message)+1, 0);
			sleep(1);
			sprintf(buff_snd, "Other's turn\n");
			send( client_socket1, buff_snd, strlen( buff_snd)+1, 0);
			
		}
		else
		{
			int i=0;
			for(i=0; i<player_num; i++)
			{
				if(new[0][1] == player[1][i] && new[0][0] == player[0][i])
					player[2][i] = 1;
			}
			count = -1;
			end--;
			first = 0;
		}
	}	
	else
	{

		Make_Message_Other(1);
		send( client_socket1, message, strlen(message)+1, 0);

		sleep(1);

		if(first==0)
		{
			Allocation(1);
			Sort(1);
		}

		Make_Message(1);
		printf("%s : %s\n", player1_name, message);
		send( client_socket1, message, strlen(message)+1, 0);

		sleep(1);
		sprintf(buff_snd, "Your turn\n");
		send( client_socket1, buff_snd, strlen( buff_snd)+1, 0);

		recv  ( client_socket1, buff_rcv, 4, 0);
		index = *buff_rcv;
		recv  ( client_socket1, buff_rcv, 4, 0);
		guess = *buff_rcv;

		if(player[1][index-1] == guess)
		{
			player[2][index-1] = 1;

			if(--end <= 0)
			{
				printf("Winner : B\n");
				sprintf(message, "Win!!\n");
				send( client_socket1, message, strlen(message)+1, 0);
				sprintf(message, "Lose..\n");
				send( client_socket, message, strlen(message)+1, 0);
				close( client_socket);
     			close( client_socket1);
				exit(1);
			}

			first++;
			Make_Message_Other(0);
			send( client_socket, message, strlen(message)+1, 0);
			sleep(1);
			Make_Message(0);
			send( client_socket, message, strlen(message)+1, 0);
			sleep(1);
			sprintf(buff_snd, "Other's turn\n");
			send( client_socket, buff_snd, strlen( buff_snd)+1, 0);

		}
		else
		{
			int i=0;
			for(i=0; i<player1_num; i++)
			{
				if(new[0][1] == player1[1][i] && new[0][0] == player1[0][i])
					player1[2][i] = 1;
			}
			count = -1;
			end1--;
			first = 0;
		}		
	}
}


int   main( void)
{
   int   server_socket;

   int   client_addr_size;
   int   client_addr_size1;



   struct sockaddr_in   server_addr;
   struct sockaddr_in   client_addr;
   struct sockaddr_in   client_addr1;

   int i,j;   


   for(i=0; i<2; i++)
      for(j=0; j<12; j++)
         block[i][j]=0;

   server_socket  = socket( PF_INET, SOCK_STREAM, 0);
   if( -1 == server_socket)
   {
      printf( "server socket 생성 실패\n");
      exit( 1);
   }

   memset( &server_addr, 0, sizeof( server_addr));
   server_addr.sin_family     = AF_INET;
   server_addr.sin_port       = htons( 7000);
   server_addr.sin_addr.s_addr= htonl( INADDR_ANY);

   if( -1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
   {
      printf( "bind() 실행 에러\n");
      exit( 1);
   }

   while( 1)
   {
      if( -1 == listen(server_socket, 5))
      {
         printf( "대기상태 모드 설정 실패\n");
         exit( 1);
      }

      client_addr_size  = sizeof( client_addr);
      client_addr_size1  = sizeof( client_addr1);

      client_socket     = accept( server_socket, (struct sockaddr*)&client_addr,
                                          &client_addr_size);
      sprintf( buff_snd, "Welcome to this Game!!!\nPlease wait...");
      recv  ( client_socket, buff_rcv, BUFF_SIZE, 0);
      printf( "receive: %s\n", buff_rcv);
	strcpy(player_name, buff_rcv);
      send( client_socket, buff_snd, strlen( buff_snd)+1, 0);

      client_socket1    = accept( server_socket, (struct sockaddr*)&client_addr1,
                                          &client_addr_size1);

      if ( -1 == client_socket)
      {
         printf( "클라이언트 연결 수락 실패\n");
         exit( 1);
      }
      if ( -1 == client_socket1)
      {
         printf( "클라이언트 연결 수락 실패\n");
         exit( 1);
      }

      recv  ( client_socket1, buff_rcv, BUFF_SIZE, 0);
      printf( "receive: %s\n", buff_rcv);
strcpy(player1_name, buff_rcv);
      sprintf( buff_snd, "Welcome to this Game!!!");
      // +1: NULL까지 포함해서 전송
      send( client_socket1, buff_snd, strlen( buff_snd)+1, 0);

      break;
   }   


      sprintf( buff_snd, "The Game Begins!");
      send( client_socket, buff_snd, strlen( buff_snd)+1, 0);
	  sleep(1);
      send( client_socket1, buff_snd, strlen( buff_snd)+1, 0);

	Allocation_f(0);
	Sort(0);
	Make_Message(0);

	printf("%s : %s\n", player_name, message);

      sprintf( buff_snd, message, strlen(message));
      send( client_socket, buff_snd, strlen( buff_snd)+1, 0);


	Allocation_f(1);
	Sort(1);
	Make_Message(1);

	printf("%s : %s\n", player1_name, message);

      sprintf( buff_snd, message, strlen(message));
      sleep(1);
      send( client_socket1, buff_snd, strlen( buff_snd)+1, 0);

	while(1)
	{
		while(count != -1) Turn(0);
		count = 0;
		while(count != -1) Turn(1);
		count = 0;
		
	}

   
}
