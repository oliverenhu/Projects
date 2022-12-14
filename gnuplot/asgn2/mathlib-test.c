#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;

    bool et = false, b = false, m = false, r = false, v = false, n = false, s = false, h = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {
        case 's': s = true; break;

        case 'e': et = true; break;

        case 'm': m = true; break;

        case 'r': r = true; break;

        case 'b': b = true; break;

        case 'v': v = true; break;

        case 'n': n = true; break;

        case 'a':
            et = true;
            m = true;
            r = true;
            b = true;
            v = true;
            n = true;
            break;

        case 'h': h = true; break;
        }
    }
    if (h)
        printf("SYNOPSIS\n   A test harness for the small numerical library.\n\nUSAGE\n   "
               "./mathlib-test [-aebmrvnsh]\n\nOPTIONS\n  -a   Runs all tests.\n  -e   Runs e "
               "test.\n  -b   Runs BBP pi test.\n  -m   Runs Madhava pi test.\n  -r   Runs Euler "
               "pi test.\n  -v   Runs Viete pi test.\n  -n   Runs Newton square root tests.\n  -s  "
               " Print verbose statistics.\n  -h   Display program synopsis and usage.\n");
    else {
        if (et)
            e();
        if (s && et)
            printf("e() terms = %d\n", e_terms());
        if (r)
           
            pi_euler();
        if (s && r)
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        if (b)
            pi_bbp();
        if (s && b)
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        if (m)
           
        pi_madhava();
        if (s && m)
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        if (v)
            pi_viete();
        if (s && v)
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        if (n) 
            sqrt_newton(10);
                    }
    
    return 0;
}
