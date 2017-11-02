#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

void listfiles(char *path){
  DIR *d = opendir(path);
  struct dirent *entry;
  entry = readdir(d);
  while(entry){
    int type = entry->d_type;
    if(type == DT_DIR){
      printf("Directory:  %s\n",entry->d_name);
    }
    if(type == DT_REG){
      printf("File:  %s\n",entry->d_name);
    }
    entry = readdir(d);
  }
  closedir(d);
}

int filesize(char *path){
  DIR *d = opendir(path);
  int totalsize = 0;
  struct dirent *entry;
  entry = readdir(d);
  while(entry){
    int type = entry->d_type;
    if(type == DT_REG){
      //printf("%s\n",entry->d_name);
      char path[256];
      strcpy(path,"test");
      strcat(path,"/");
      strcat(path,entry->d_name);
      //printf("%s\n",path);
      struct stat sb;
      stat(path, &sb);
      size_t size = sb.st_size;
      totalsize += size;
    }
    entry = readdir(d);
  }
  closedir(d);
  return totalsize;
}

void readable_size(int size){
  int gb = size / 1024;
  size = size % 1024;
  int mb = size / 1024;
  size = size % 1024;
  int kb = size / 1024;
  size = size % 1024;
  int b = size;
  printf("Readable file size: %d GB %d MB %d KB %d B\n",gb,mb,kb,b);
}

int main(){
  printf("Statistics for directory: test\n");
  int totalfilesize = filesize("test");
  printf("Total directory size: %d Bytes\n",totalfilesize);
  readable_size(totalfilesize);
  printf("\n");
  listfiles("test"); 
}
