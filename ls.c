#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int ORDER = 1;

int comparator(const struct dirent **a, const struct dirent **b) {
  return ORDER * strcmp((*a)->d_name, (*b)->d_name);
}

int main(int argc, char *argv[]) {
   struct dirent **namelist;

   if (argc == 2 && *argv[1] == 'r')
       ORDER = -1;

   int n = scandir(".", &namelist, 0, comparator);
   int p = 0;

   if (n < 0)
       perror("scandir");
   else {
        while (p < n){
          printf("%s  ", namelist[p]->d_name);
          p++;
        }

        printf("\n");
    }
}
