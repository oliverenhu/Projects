#include <stdio.h>
#include "stats.h"
#include "heap.h"
#include "insert.h"
#include "set.h"
#include "quick.h"
#include "shell.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "aeisqr:n:p:h:"
typedef enum { HEAP , SHELL , INSERTION , QUICK } Sorts;
const char *names[] = {"Heap Sort","Shell Sort","Insertion Sort","Quick Sort"};
void set_sort(Sorts i, Stats *stats,uint32_t *A, uint32_t size, int elements);

int main(int argc, char **argv){
	int opt = 0;
	uint64_t seed =  13371453;
        uint32_t size = 100;
	int elements = 100 ;
	uint64_t mask = 0x3FFFFFFF;
	Set command = empty_set();
	while((opt =getopt(argc, argv , OPTIONS))!=-1){
		switch(opt){
			case 'a':
		        command = insert_set(HEAP, command);
			command = insert_set(INSERTION, command);
			command = insert_set(SHELL,command);
			command = insert_set(QUICK, command);
			break;
			
			case 'e':
                        command = insert_set(HEAP, command);
			break;
			
			case 'i':
			command = insert_set(INSERTION, command);
                        break;
 			
			case 's':
			command = insert_set(SHELL,command);
                        break;
 			
			case 'q':
			command = insert_set(QUICK, command);
                        break;
 			
			case 'r':
			seed=atoi(optarg);
			
                        break;
 			
			case 'n':
			size=atoi(optarg);
                        break;
 			
			case 'p':
			elements=atoi(optarg);	
                        break;
 			
			case 'h':
                        break;
		}
	}
	

	uint32_t A[size];
	srandom(seed);
	for(uint32_t x =0;x<size;x +=1){
		A[x]=mask&random();
	 	
	}
	
  	for (Sorts i = HEAP;i < QUICK+1; i+=1){
		if(member_set(i,command)){

			Stats *stats=NULL;
			set_sort(i,stats,A,size,elements);
			
		}
		
	}	
	return 0;

}	

void set_sort(Sorts i,Stats *stats, uint32_t *A, uint32_t size, int elements){
	
	stats=malloc(sizeof *stats);	
	//if(i==0){
	//	heap_sort(stats,A,size);
	//}
	if(i==1){
		shell_sort(stats,A,size);
	} 
	if(i==2){
		insertion_sort(stats,A,size);
	}
	printf("%s, %d elements, %lu moves, %lu compares\n", names[i],elements,stats->moves,stats->compares);
	free(stats);
	for(uint32_t x =0;x<size;x +=1){
		if((x+1)%5==0&&x!=0){
			printf("%13" PRIu32"\n",A[x]);
	}	
		else{
               		printf("%13" PRIu32,A[x]);
		}
	}
		
		
}
		
	
