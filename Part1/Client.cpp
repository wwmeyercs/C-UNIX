#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <fstream>

unsigned int microseconds;

#define MAXLINE 8192 /*max text line length*/
#define SERV_PORT 10010 /*port*/
using namespace std;
int
main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in servaddr;
  char sendline[MAXLINE], recvline[MAXLINE];
  ofstream myfile;
  int id = 0;
  if(argc == 3){
    id = 0;
  }
  else if (argc == 4){
    id = atoi(argv[3]);
  }
  if (argc < 3) {
    perror("Usage: TCPClient <Server IP> <Server Port>");
    exit(1);
  }
  // alarm(300);  // to terminate after 300 seconds

  //basic check of the arguments
  //additional checks can be inserted


  //Create a socket for the client
  //If sockfd<0 there was an error in the creation of the socket
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
    perror("Problem in creating the socket");
    exit(2);
  }

  //Creation of the socket
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr= inet_addr(argv[1]);
  servaddr.sin_port =  htons(atoi(argv[2]));
  //servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

  //Connection of the client to the socket
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
    perror("Problem in connecting to the server");
    exit(3);
  }
  if(id == 0 || id == 1){
    if (id == 0 ){
      if(fgets(sendline, MAXLINE, stdin) != NULL){

      }
    }
    else{
      strcpy(sendline, "select * from classics;");
    }
    myfile.open ("a4Client1Log_.txt");

    for(;;)
    {

      send(sockfd, sendline, strlen(sendline), 0);

      if (recv(sockfd, recvline, MAXLINE,0) == 0){
        //error: server terminated prematurely
        perror("The server terminated prematurely");
        exit(4);
      }
      fputs(recvline, stdout);     // Sleep for 50*1000ms
      myfile << recvline;

      usleep(50*1000);

      printf("\nPID: %d ", getpid());
      //fprintf(myfile, "\nPID: %d ", getpid());
      myfile <<  "\nPID: " << getpid();
      printf(" Thread ID: %u\n", pthread_self());
      //fprintf(myfile," Thread ID: %u\n", (unsigned int)pthread_self());
      myfile <<  " Thread ID: " << (unsigned int)pthread_self() << "\n";
      time_t t = time(0);   // get time now
      struct tm * now = localtime( & t );
      cout << (now->tm_year + 1900) << '-'
      << (now->tm_mon + 1) << '-'
      <<  now->tm_mday << ' '
      <<  now->tm_hour << ':'
      <<  now->tm_min << ':'
      <<  now->tm_sec
      << endl;
      myfile << (now->tm_year + 1900) << '-'
      << (now->tm_mon + 1) << '-'
      <<  now->tm_mday << ' '
      <<  now->tm_hour << ':'
      <<  now->tm_min << ':'
      <<  now->tm_sec
      << endl;
      usleep(3000000);

    }
  }
  if(id == 2){
    myfile.open ("a4Client2Log_.txt");

    while(1)
    {
      strcpy(sendline, "UPDATE classics SET author=\"*** UNKNOWN ***\" WHERE title=\"Moby Dick\"");

      send(sockfd, sendline, strlen(sendline), 0);

      fputs(recvline, stdout);     // Sleep for 50*1000ms
      myfile << recvline;
      usleep(2000000);
      char outerline[MAXLINE], receiverline[MAXLINE];

      strcpy(outerline, "UPDATE classics SET author=\"Herman Melville\" WHERE title=\"Moby Dick\"");

      send(sockfd, outerline, strlen(outerline), 0);

      usleep(2000000);

      //
      fputs(receiverline, stdout);     // Sleep for 50*1000ms
      myfile << receiverline;
      //
      //
      printf("\nPID: %d ", getpid());
      //fprintf(myfile, "\nPID: %d ", getpid());
      myfile <<  "\nPID: " << getpid();
      printf(" Thread ID: %u\n", pthread_self());
      //fprintf(myfile," Thread ID: %u\n", (unsigned int)pthread_self());
      myfile <<  " Thread ID: " << (unsigned int)pthread_self() << "\n";
      time_t t = time(0);   // get time now
      struct tm * now = localtime( & t );
      cout << (now->tm_year + 1900) << '-'
      << (now->tm_mon + 1) << '-'
      <<  now->tm_mday << ' '
      <<  now->tm_hour << ':'
      <<  now->tm_min << ':'
      <<  now->tm_sec
      << endl;
      myfile << (now->tm_year + 1900) << '-'
      << (now->tm_mon + 1) << '-'
      <<  now->tm_mday << ' '
      <<  now->tm_hour << ':'
      <<  now->tm_min << ':'
      <<  now->tm_sec
      << endl;

    }

  }
  if(id == 3){
    myfile.open ("a4Client3Log_.txt");
    while(1)
    {
      strcpy(sendline, "DELETE FROM classics WHERE author=\"Mark Twain\"");

      send(sockfd, sendline, strlen(sendline), 0);

      fputs(recvline, stdout);     // Sleep for 50*1000ms
      myfile << recvline;
      usleep(2000000);
      char outerline[MAXLINE], receiverline[MAXLINE];

      strcpy(outerline, "INSERT INTO `classics` (`author`,`title`,`category`,`year`,`isbn`) "  \
      "VALUES('Mark Twain','The Adventures of Tom Sawyer', 'Fiction', '1876','9781598184891'); ");

      send(sockfd, outerline, strlen(outerline), 0);

      usleep(2000000);

      //
      fputs(receiverline, stdout);     // Sleep for 50*1000ms
      myfile << receiverline;
      //
      //
      printf("\nPID: %d ", getpid());
      //fprintf(myfile, "\nPID: %d ", getpid());
      myfile <<  "\nPID: " << getpid();
      printf(" Thread ID: %u\n", pthread_self());
      //fprintf(myfile," Thread ID: %u\n", (unsigned int)pthread_self());
      myfile <<  " Thread ID: " << (unsigned int)pthread_self() << "\n";
      time_t t = time(0);   // get time now
      struct tm * now = localtime( & t );
      cout << (now->tm_year + 1900) << '-'
      << (now->tm_mon + 1) << '-'
      <<  now->tm_mday << ' '
      <<  now->tm_hour << ':'
      <<  now->tm_min << ':'
      <<  now->tm_sec
      << endl;
      myfile << (now->tm_year + 1900) << '-'
      << (now->tm_mon + 1) << '-'
      <<  now->tm_mday << ' '
      <<  now->tm_hour << ':'
      <<  now->tm_min << ':'
      <<  now->tm_sec
      << endl;

    }

  }
  myfile.close();
  exit(0);
}
