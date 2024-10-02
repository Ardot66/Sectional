#include <stdio.h>
#include "../Source/Sectional.h"

#define TEST_SUCCESS(...) {printf("Test Successful: %s\n", __VA_ARGS__); TestsPassed ++;}
#define TEST_FAIL(...) printf("Test Failed: %s\n", __VA_ARGS__);

size_t TestCount = 7;
size_t TestsPassed = 0;

int ProcessLoop(int argCount, char **argValues)
{   
    TEST_SUCCESS("Process loop activated")
    exit(0);
}

SECTION_INITIALIZE
{
    TEST_SUCCESS("SECTION_INITIALIZE called")
}

SECTION_REGISTER
{
    TEST_SUCCESS("SECTION_REGISTER called")
}

SECTION_READY
{
    TEST_SUCCESS("SECTION_READY called")

    size_t sectionCount = GetSectionCount();

    if(sectionCount > 0)
        TEST_SUCCESS("Section count greater than zero")
    else
        TEST_FAIL("Section count is zero")

    int canGetAllSections = 1;

    for(size_t x = 0; x < sectionCount; x++)
    {
        Section *section;
        canGetAllSections &= GetSection(x, &section);
        canGetAllSections &= section != NULL;
    }

    if(canGetAllSections)
        TEST_SUCCESS("All sections can be obtained")
    else
        TEST_FAIL("Not all sections can be obtained")

    SetProcessLoop(ProcessLoop);
}

SECTION_EXIT
{
    TEST_SUCCESS("SECTION_EXIT called")

    printf("%llu out of %llu tests passed.\n", TestsPassed, TestCount);
}