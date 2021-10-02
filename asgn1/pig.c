#include <stdio.h>
#include <stdlib.h>
#include "names.h"
typedef enum { SIDE=0, RAZORBACK=10, TROTTER=10, SNOUTER=15, JOWLER=5} Position;
const Position pig[7]= { SIDE, SIDE , RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER} ;
int main(void) {
        int players;
	long long seed;
       // int scores[10]={0,0,0,0,0,0,0,0,0,0};
	
        
        printf("How many players ? ");
        scanf("%d",&players);
        if(players>1 && players<11 ){
            printf("%d players\n", players);
        }
        else {
            fprintf ( stderr , " Invalid number of players . Using 2 instead .\n");
        }

        printf("Random seed:");
        scanf("%lld",&seed);
        if(seed <= 4294967295 && seed >=0 ){
            srandom(seed);
            printf (" - generated %lu\n", random () );
 
        }
        else{
            fprintf ( stderr , " Invalid random seed . Using 2021 instead .\n");
	    srandom(2021);
            printf (" - generated %lu\n", random () );
        }
	for(int i = 0;i<10;i=i+1){
        printf("%s\n",names[i]);
        }
    
        return 0;
}
