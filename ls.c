#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int ORDER = 1;
int SKIPDOTS = 1;
int SKIPPARENT = 1;
int PERLINE = 0;
int INODE = 0;

int comparator(const struct dirent **a, const struct dirent **b) {
  return ORDER * strcasecmp((*a)->d_name, (*b)->d_name);
}

int processArgs(int argc, char *argv[]){
    int strsize = 0;
    int i;
    for (i = 1; i < argc; i++)
      strsize += strlen(argv[i]);

    char *cmdstring = malloc(strsize);

    for (i = 1; i < argc; i++) {
      strcat(cmdstring, argv[i]);
      if (argc > i+1)
        break;
    }

    for (i = 1; i < strlen(cmdstring); i++)
      switch(cmdstring[i]){
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
        case 'i':
          INODE = 1;
          break;
     }
}

int main(int argc, char *argv[]) {
   struct dirent **namelist;
   struct stat fileStat;
   processArgs(argc, argv);

   int n = scandir(".", &namelist, 0, comparator);
   int p = 0;

   if (n < 0)
       perror("scandir");
   else {
        char *divisor = PERLINE ? "\n" : "  ";

        while (p < n){
          char *name = (namelist[p]->d_name);
          lstat(name, &fileStat);

          if (SKIPDOTS){
            if (name[0] != '.'){
              if (INODE) printf("%d ", (int) fileStat.st_ino);
              printf("%s%s", name, divisor);
            }
          }

          else if (SKIPPARENT && !SKIPDOTS) {
              if (!(name[0] == '.' && (strlen(name) == 1 || ((name[1] == '.') && strlen(name) == 2)))){
                if (INODE) printf("%d ", (int) fileStat.st_ino);
                printf("%s%s", name, divisor);
              }
          }

          else {
              if (INODE) printf("%d ", (int) fileStat.st_ino);
              printf("%s%s", name, divisor);
          }

          p++;
        }

        printf(PERLINE ? "" : "\n");
    }
}
