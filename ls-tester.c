#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */

int main(int argc, char **argv){
    system("#!/bin/bash");
    system("gcc ls.c -o ls2");

    FILE *fp_orig, *fp_test;
    char orig[128], test[128];
    char *args = "AacCdFfhiklnqRrSstux1"; // edit w, mistakes

    int suc = 0, fail = 0;

    for (char* i = args; *i; i++){
      char cmdorig[64], cmdtest[64], argument;

      strcpy(cmdorig, "ls -1");
      strcpy(cmdtest, "./ls2 -1");

      strcat(cmdorig, i);
      strcat(cmdtest, i);

      cmdorig[6] = cmdtest[9] = 0;
      argument = cmdorig[5];

      fp_orig = popen(cmdorig, "r");
      fp_test = popen(cmdtest, "r");

      fgets(orig, sizeof(orig)-1, fp_orig);
      fgets(test, sizeof(orig)-1, fp_test);

      if (!(strcmp(orig, test))) {
        printf(BOLDGREEN "Correct coverage: ls -");
        suc++;
      } else {
        printf(BOLDRED "Incorrect coverage: ls -");
        fail++;
      }

      printf("%c\n" RESET, argument);
      orig[0] = test[0] = 0;
    }

    printf("Score: %.2f/1.00\n", (suc * 1.00)/(suc + fail));

    popen("rm ls2", "r");
    pclose(fp_orig);
    pclose(fp_test);
    return 0;
}
