#include <stdio.h>   /* Standard input/output definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>   /* File control definitions */

char buff;
int n;
int main(){
  int fd; /* File descriptor for the port */
  int ch;
  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
  
  if (fd == -1)
  {
    /* Could not open the port. */
    printf("Unable to open serial port\n");
    return -1;
    
  }
  
  while(1){
    
    while((n=read(fd,&buff,1))>0){
      printf("%c",buff);
      printf("\n");
      
    }  
    
  }
  
  close(fd);
  
  return 0;
  
}
