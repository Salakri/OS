#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
writelines(int fd, char *name, int lineNum)
{
  int i, n;
  int l;

  l = 0;
 
  while((n = read(fd, buf, sizeof(buf))) > 0)
  {
    for(i=0; i<n; i++)
    {

      // print each character
      printf(1, "%c", buf[i]);
      // count num of lines
      if(buf[i] == '\n')
      {
        l++;
      }
      // quite program after output required lines of content
      if (l >= lineNum)
      {
        return;      
      }
    }
  }
  if(n < 0)
  {
    printf(1, "head: read error\n");
    exit();
  }

}

int
main(int argc, char *argv[])
{
  int fd, i;
  int lineNum, defaultNum;
  char* argument;
  // default value of lines is 10
  lineNum = 10;
  defaultNum = 10;
  fd = 0;
  argument = "";

  // when only one argv
  if(argc <= 1)
  {
    writelines(fd, argument, defaultNum);
    exit();
  }

  // more than one argv
  for(i = 1; i < argc; i++)
  {
    // if the argv is number of lines
    if(argv[i][0] == '-')
    {
      // skip first character
      lineNum = atoi(++argv[i]);
      if (i == (argc - 1))
      {
        writelines(fd, argument, lineNum);
      }
      continue;
    }
    // if the argv is the name of the file
    
    if((fd = open(argv[i], 0)) < 0)
    {
      printf(1, "head: cannot open %s\n", argv[i]);
      exit();
    }
    else
    {
      argument = argv[i];
    }
    writelines(fd, argument, lineNum);
    close(fd);
    
  }
  exit();
}


