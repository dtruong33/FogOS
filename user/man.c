#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "stdbool.h"
#include "stddef.h"

/***
 * Helped function for the find flag, seeing if the line contains the word
 * 
 * @param line line to be read
 * @return true if found, false if not
 */
bool
find(char* line, char* word)
{
  int lineLen = strlen(line);
  int wordLen = strlen(word);
  int readableLen = lineLen - wordLen;
  char *linePtr = line;
  char *wordPtr = word;
  int count = 0;

  if(readableLen < 0)
    return false;

  for(int i = 0; i < readableLen; i++){
    for(int j = 0; j < wordLen; j++){
      if(linePtr[j] != wordPtr[j])
        break;
      count++;
    }
    if(count == wordLen)
      return true;
    linePtr++;
    count = 0;
  }
  return false;  
}

/***
 * Concatenating function for strings, automatically appends the .md file extension
 *
 * @param dst destination string to concatenate to
 * @param src source string to concatenate from
 */
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

/***
 * Man command to print and afind man page
 *
 * @param path name of wanted manpage
 * @param f flag for find functionality
 * @param word word wanted to be found
 */
void
man(char *path, bool f, char *word)
{
  int i = 0;int foundLines = 0;
  char *arg = path;
  uint size = 256;
  char *manPage = malloc(size);
  if(manPage == NULL){
    exit(0);
  }

  char manPath[128];
  char suffix[] = ".md";
  strcpy(manPath, arg);
  strcat(manPath, suffix);

  int fd = open(manPath, O_RDONLY);
  if(fd <= 0){
    printf("Man error: %s\nNo such man page exists\n", manPath);
    exit(0);
  }

  while(true){
    int bytes = getline(&manPage, &size, fd);
    i++;
    
    if(f == false){
      printf("%s", manPage);
    }else if(find(manPage, word)){
      printf("%d:%s", i, manPage);
      foundLines++;
    }

    if(bytes <= 0){
      break;
    }
  }

  if(f == true && foundLines == 0)
    printf("%s not found in man page", word);

  printf("\n");
  free(manPage);
}

int
main(int argc, char *argv[])
{
  if(argc > 1 && strlen(argv[1]) + 3 > 128){
    printf("Man error: Argument exceeds path limit\n");
    exit(0);
  }if(argc > 4){
    printf("Man error: Too many arguments, limit of 4\n");
    exit(0);
  }if(argc > 2 && *argv[2] != 'f'){
    printf("Man error: Unknown Flag\n");
    exit(0);
  }

  if(argc < 2){
    man("man", false, NULL);
    exit(0);
  }else if(argc == 2){
    man(argv[1], false, NULL);
  }else if(argc == 4 && *argv[2] == 'f'){
    man(argv[1], true, argv[3]);
  }

  exit(0);
}

