#include <stdio.h>

int main()
{
   FILE *fp;

   fp = fopen("test2.txt", "w+");
   
   if(fp == NULL){
     printf("Error!\n");
     return -1;
   }
   
   fputs("Test2 file\n", fp);
   fputs("This is a test\n", fp);
   fclose(fp);
   
   return 0;
}
