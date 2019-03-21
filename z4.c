#include <stdio.h>
#include <stdlib.h>
#define SIZE 5


//int cmp(const void* x, const void* y);
//int max_index(QWER* p, int n);



typedef struct QWER{
	float a;
	float b;
	int (*cmp)(struct QWER*, struct QWER*);
}QWER;


int cmp(const void* x, const void* y);
int max_index(QWER* p, int n);


int main(){
	QWER* p = (QWER*)malloc(SIZE * sizeof(QWER));
	for(int i = 0; i < SIZE; i++){
		scanf("%f %f", &(p[i].a), &(p[i].b));
	}
	printf("%d", max_index(p, SIZE));
}


int cmp(const void* x, const void* y){
	if (((QWER*)x)->a + ((QWER*)x)->b > ((QWER*)y)->a + ((QWER*)y)->b)
		return 1;
	if (((QWER*)x)->a + ((QWER*)x)->b < ((QWER*)y)->a + ((QWER*)y)->b)
		return -1;
	return 0;
}


int max_index(QWER* p, int n){
	QWER* max = p;
	for(int i = 1; i < n; i++){
		if (cmp(max, p + i) < 0){
			max = p + i;
		}
	}
	return (max - p);
}
