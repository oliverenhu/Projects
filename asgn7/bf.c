#include "bf.h"
#include "bv.h"
#include "salts.h"
#include "speck.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt .
    uint64_t secondary[2]; // Secondary hash function salt .
    uint64_t tertiary[2]; // Tertiary hash function salt .
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) { //Adds the salts to primary,secondary,and tertiary uint32_t[2] arrays through salts.h
        //creates a bit vector as filter

        bf->filter = bv_create(size);
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;
    }
    return bf;
}
void bf_delete(BloomFilter **bf) { //Frees dynamically allocated arrays,filter, and bf
    bv_delete(&(*bf)->filter);
    free(*bf);
    *bf = NULL;
}
uint32_t bf_size(BloomFilter *bf) { //returns bit vector length
    return bv_length(bf->filter);
}
void bf_insert(BloomFilter *bf,
    char *oldspeak) { //Hashes 3 salts with oldspeak for their indexes and sets the bits
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}
bool bf_probe(
    BloomFilter *bf, char *oldspeak) { //Returns true if oldspeak has been added to bloom filter
    return (bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
            && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
            && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf)));
}
uint32_t bf_count(BloomFilter *bf) { //Counts the number of initialized indexes
    uint32_t bf_count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i)) {
            bf_count += 1;
        }
    }
    return bf_count;
}
void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
