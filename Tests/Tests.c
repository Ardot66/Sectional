#include <stdio.h>
#include "../Source/Sectional.h"

#define TEST_SUCCESS(...) printf("Test Successful: %s\n", __VA_ARGS__); TestsPassed ++;
#define TEST_FAIL(...) printf("Test Failed: %s\n", __VA_ARGS__);

const size_t TestCount = 4;
size_t TestsPassed = 0;

SECTION_READY
{
    TEST_SUCCESS("SECTION_READY called")
}

SECTION_INITIALIZE
{
    TEST_SUCCESS("SECTION_INITIALIZE called")
}

SECTION_REGISTER
{
    TEST_SUCCESS("SECTION_REGISTER called")
}

SECTION_EXIT
{
    TEST_SUCCESS("SECTION_EXIT called")

    printf("%llu out of %llu tests passed.\n", TestsPassed, TestCount);
}