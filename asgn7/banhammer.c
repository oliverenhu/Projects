# include "parser.h"
# include <regex.h>
# include <stdio.h>
# include "node.h"
# include "bst.h"
# include "bf.h"
# include "bv.h"
# include "salts.h"
#include <stdint.h>
#include "speck.h"
#include "ht.h"
#include <stdbool.h>
#include "messages.h"
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
# define WORD "[a-z0-9A-Z'_-]+"

int main (int argc,char **argv){
	uint32_t htsize=2<<16;
	uint32_t bfsize=2<<20;
	int opt = 0;
	bool stats=false;
	bool rightspeak=false;
	bool thoughtcrime=false;
	FILE *bad;
	FILE *new;
	char badspeak[1024];
	char oldspeak[1024];
	char newspeak[1024];
	
	while ((opt = getopt(argc, argv, "t:f:sh")) != -1) { //commands for encryption
        switch (opt) {
        case 't': htsize = atoi(optarg); break; //opens specified infile for reading
        case 'f': bfsize = atoi(optarg); break;
        case 's': stats = true; break; //sets name of pubfile
        case 'h':	
		  return 0;
	}
	}
	BloomFilter *bf=bf_create(bfsize);
	HashTable *ht=ht_create(htsize);
	bad=fopen("badspeak.txt","r");
	new=fopen("newspeak.txt","r");
	uint32_t bad_count=0;
	uint32_t bad_index=0;
	uint32_t new_count=0;
	uint32_t new_index=0;
	while(1){
		fscanf(bad,"%s\n",badspeak);
		
		
		bf_insert(bf,badspeak);
		ht_insert(ht,badspeak,NULL);
		bad_count+=1;
		if(feof(bad)){
			break;
		}
	}
	while(1){
                fscanf(new,"%s %s\n",oldspeak,newspeak);
		bf_insert(bf,oldspeak);
                ht_insert(ht,oldspeak,newspeak);
		new_count+=1;
		if(feof(new)){
                        break;
                }

        }
		
	char *bad_message[bad_count];
	char *new_message[new_count];


	regex_t re;
	if ( regcomp(&re , WORD , REG_EXTENDED ) ) {
	fprintf(stderr , "Failed to compile regex .\n") ;
	return 1;
}
	
	char *word = NULL ;
	while (( word = next_word(stdin,&re))!= NULL ) {
		if(bf_probe(bf,word)){
			
			if(ht_lookup(ht,word)->oldspeak){
				if(ht_lookup(ht,word)->newspeak){
					new_message[new_index]=ht_lookup(ht,word)->oldspeak;
					new_index+=1;
					rightspeak=true;	
				}
				
				else{
					bad_message[bad_index]=ht_lookup(ht,word)->oldspeak;
					bad_index+=1;
					thoughtcrime=true;	
				}
				
			}
		}
	}
	if(rightspeak&&thoughtcrime){
		printf("%s",mixspeak_message);
		for(int i=0;i<bad_index;i+=1){
			printf("%s\n",bad_message[i]);	
		}
		for(int i=0;i<new_index;i+=1){
                        node_print(ht_lookup(ht,new_message[i]));
                }



	}
	else if(thoughtcrime&&!rightspeak){
		printf("%s",badspeak_message);
		for(int i=0;i<bad_index;i+=1){
                        printf("%s\n",bad_message[i]);
                }

	}
	else if(!thoughtcrime&&rightspeak){
                printf("%s",goodspeak_message);
		for(int i=0;i<new_index;i+=1){
                        node_print(ht_lookup(ht,new_message[i]));
                }
        }
	
		


	fclose(bad);
	fclose(new);
	bf_delete(&bf);
	ht_delete(&ht);
	clear_words();
	regfree(&re);
	return 0;
}
