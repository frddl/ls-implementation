#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int ORDER = 1;
int SKIPDOTS = 1;
int SKIPPARENT = 1;
int PERLINE = 0;

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
       case '1':
         PERLINE = 1;
         break;
     }
   }

   int n = scandir(".", &namelist, 0, comparator);
   int p = 0;

   if (n < 0)
       perror("scandir");
   else {
        char *divisor = PERLINE ? "\n" : "  ";

        while (p < n){
          char *name = (namelist[p]->d_name);

          if (SKIPDOTS){
            if (name[0] != '.')
              printf("%s%s", name, divisor);
          }

          else if (SKIPPARENT && !SKIPDOTS) {
              if (!(name[0] == '.' && (strlen(name) == 1 || ((name[1] == '.') && strlen(name) == 2))))
                printf("%s%s", name, divisor);
          }

          else {
              printf("%s%s", name, divisor);
          }

          p++;
        }

        printf(PERLINE ? "" : "\n"); 
    }
}
