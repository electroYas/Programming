#include <stdio.h>   /* Standard input/output definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>   /* File control definitions */
#include <sys/signal.h>


void signal_handler_IO (int status);   /* definition of signal handler */

char ch;
int n;
int baud_rate = B115200;
struct termios options;
struct sigaction saio;
 int fd; /* File descriptor for the port */

  
int main(){
  
  setbuf(stdout, NULL);//this will print charactor on stdout without newline
 
  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
  
  if (fd == -1)
  {
    /* Could not open the port. */
    printf("Unable to open serial port\n");
    return -1;
    
  }
  
  saio.sa_handler = signal_handler_IO;
  saio.sa_flags = 0;
  saio.sa_restorer = NULL; 
  sigaction(SIGIO,&saio,NULL);
  
  fcntl(fd, F_SETFL, FNDELAY);
  fcntl(fd, F_SETOWN, getpid());
  fcntl(fd, F_SETFL,  O_ASYNC );
  
  
  tcgetattr(fd, &options);
  cfsetispeed(&options, baud_rate);
  cfsetospeed(&options, baud_rate);

  tcsetattr(fd, TCSANOW, &options);

  
  while(1){
    sleep(5000);   
  }  
  
  close(fd);
  
  return 0;
  
}

void signal_handler_IO (int status)
{
   while((n=read(fd,&ch,1))>0){
      putchar(ch);
   
   }
}
