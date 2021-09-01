#include <stdio.h>
#include "misc.h"
#include "tuple.h"
#include "tests.h"

int main(int argc, char** argv)
{
    int result = 0;
    int num_failed = 0;

    num_failed = chapter_one_tests();
    if (num_failed > 0) { printf("%i chapter_one_tests() failed.\n", num_failed); }
    else { printf("chapter_one_tests() passed.\n"); }

    num_failed = chapter_two_tests();
    if (num_failed > 0) { printf("%i chapter_two_tests() failed.\n", num_failed); }
    else { printf("chapter_two_tests() passed.\n"); }

    num_failed = chapter_three_tests();
    if (num_failed > 0) { printf("%i chapter_three_tests() failed.\n", num_failed); }
    else { printf("chapter_three_tests() passed.\n"); }

    num_failed = chapter_four_tests();
    if (num_failed > 0) { printf("%i chapter_four_tests() failed.\n", num_failed); }
    else { printf("chapter_four_tests() passed.\n"); }
}
