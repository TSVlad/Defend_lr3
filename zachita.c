#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>


typedef struct FILES{
	char name[256];
	unsigned short size;
	int number;
}FILES;


void check(char* dirPath, FILES** p, int* size){
	int f;
	char* dirCopy;
	DIR* dir = opendir(dirPath);
	struct dirent* de = readdir(dir);
	while (de){
		if (strstr(de->d_name, ".") != NULL && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
			if (*size == 1){
				strcpy((*p)[*size - 1].name, de->d_name);
				(*p)[*size - 1].size = de->d_reclen;
				(*p)[*size - 1].number = 1;
				*size += 1;
				*p = (FILES*)realloc(*p, *size * sizeof(FILES));
			}
			else{
				f = 0;
				for (int i = 0; i < *size - 1; i++){
					if (strcmp((*p)[i].name, de->d_name) == 0 && (*p)[i].size == de->d_reclen){
						f = 1;
						(*p)[i].number += 1;
						break;
					}
				}
				if (f == 0){
					strcpy((*p)[*size - 1].name, de->d_name);
					(*p)[*size - 1].size = de->d_reclen;
					(*p)[*size - 1].number = 1;
					*size += 1;
					*p = (FILES*)realloc(*p, *size * sizeof(FILES));
				}
				else{
					dirCopy = (char*)malloc((strlen(dirPath) + strlen(de->d_name) + 2) * sizeof(char));
					strcpy(dirCopy, dirPath);
					strcat(dirCopy, "/");
					strcat(dirCopy, de->d_name);
					remove(dirCopy);
					free (dirCopy);
				}
			}
		}
		else if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
			dirCopy = (char*)malloc((strlen(dirPath) + strlen(de->d_name) + 2) * sizeof(char));
			strcpy(dirCopy, dirPath);
			strcat(dirCopy, "/");
			strcat(dirCopy, de->d_name);
			check(dirCopy, p, size);
			free(dirCopy);
		}
		else if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0){
			de = readdir(dir);
			continue;
		}
		de = readdir(dir);
	}
	closedir(dir);
}


int main(){
	int size = 1;
	FILES* p = (FILES*)malloc(sizeof(FILES));
	check("rootd", &p, &size);
	for (int i = 0; i < size - 1; i++){
		printf("%s %hu\n", p[i].name, p[i].number);
	}
}
