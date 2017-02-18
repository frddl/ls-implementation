#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void) {
   struct dirent **namelist;
   int n = scandir(".", &namelist, 0, alphasort);
   int p = 0;

   if (n < 0)
       perror("scandir");
   else
        while (p < n){
          printf("%s\n", namelist[p]->d_name);
          p++;
        }
}
