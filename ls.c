#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int ORDER = 1;
int SKIPDOTS = 1;
int SKIPPARENT = 1;

int comparator(const struct dirent **a, const struct dirent **b) {
  return ORDER * strcasecmp((*a)->d_name, (*b)->d_name);
}

int main(int argc, char *argv[]) {
   struct dirent **namelist;

   if (argc == 2){
     switch(*argv[1]){
       case 'r':
         ORDER = -1;
         break;
       case 'A':
         SKIPDOTS = 0;
         break;
       case 'a':
         SKIPDOTS = 0;
         SKIPPARENT = 0;
         break;
     }
   }

   int n = scandir(".", &namelist, 0, comparator);
   int p = 0;

   if (n < 0)
       perror("scandir");
   else {
        if (SKIPPARENT && ORDER == 1)
          p = 2;
        else if (SKIPPARENT && ORDER == -1)
          n -= 2;


        while (p < n){
          char *name = (namelist[p]->d_name);
          if (SKIPDOTS){
            if (name[0] != '.')
              printf("%s  ", name);
          } else
              printf("%s  ", name);

          p++;
        }

        printf("\n");
    }
}
