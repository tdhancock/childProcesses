#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int x = 0;
  pid_t childpid;

  childpid = fork();

  if (childpid == 0) {
    if (argc == 1) {
      printf("CHILD started. No arguments provided. Terminating child\n");
    } else if (argc == 2) {
      printf("CHILD started. One argument provided. Calling execlp(), never to "
             "return (sniff)\n");

      execlp(argv[1], argv[1], NULL);
    } else if (argc > 2) {
      printf("CHILD started. More than one argument provided. Calling "
             "execvp(), never to return (sniff)\n");

      execvp(argv[1], &argv[1]);
    }
  }

  else if (childpid > 0) {
    printf("PARENT started, now waiting for process ID#%d\n", childpid);
    wait(NULL);
    printf("PARENT resumed. Child exit code of 0. Now terminating parent\n");
  }

  return 0;
}