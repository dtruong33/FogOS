#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "stdbool.h"

void
strcat(char *dst, char *src)
{
  int startLen = strlen(dst);
  int combLen = strlen(dst) + strlen(src) + 1;
  int i = 0;

  for(i = startLen; i < combLen ; i++){
    dst[i] = src[i-startLen];
  }

  dst[i] = '\0';
}

void
man(char *path)
{
  char *arg = path;
  uint size = 256;
  char *manPage = malloc(size);
  char controller[] = " ";

  char manPath[128];
  char suffix[] = ".md";
  strcpy(manPath, arg);
  strcat(manPath, suffix);

  int fd = open(manPath, O_RDONLY);
  if(fd <= 0){
    printf("Man error: %s\nNo such man page exists\n", manPath);
    exit(0);
  }

  //printf("%s\n", manPath);
  while(true){
    int bytes = getline(&manPage, &size, fd);
    printf("%s", manPage);
    if(bytes <= 0){
      break;
    }
  }

  while(true){
    gets(controller, 1);
    //if(controller[0] == 'q'){
      break;
    //}
  }
}

int
main(int argc, char *argv[])
{
  if(strlen(argv[1]) + 9 > 128){
    printf("Man error: Argument exceeds path limit\n");
    exit(0);
  }
  if(argc > 3){
    printf("Man error: Too many arguments, limit of 3\n");
    exit(0);
  }
  if(argc < 2){
    man("man");
    exit(0);
  }

  man(argv[1]);
  exit(0);
}

