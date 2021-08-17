#include <stdio.h>
#include "misc.h"
#include "tuple.h"
#include "tests.h"

int main(int argc, char** argv)
{
    int result = 0;;

    result = chapter_one_tests();
    if (result < 0) { printf("chapter_one_tests() failed.\n"); }
    else { printf("chapter_one_tests() passed.\n"); }

    result = chapter_two_tests();
    if (result < 0) { printf("chapter_two_tests() failed.\n"); }
    else { printf("chapter_two_tests() passed.\n"); }
}
