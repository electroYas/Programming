#include <stdio.h>

int main()
{
   FILE *fp;
   char buff[255];

   fp = fopen("test.txt", "r");
   
   if(fp == NULL){
      printf("Error!\n");
      return(-1);
   }
   
   while(fgets(buff, 255, fp)){
     printf("%s", buff );
   }
   
   printf("\n");
  
   fclose(fp);
   
   return 0;

}
