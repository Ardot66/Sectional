#include "SectionLoader.h"

#define SECTION_INIT_FUNCTION "Initialize"
#define SECTION_EXIT_FUNCTION "Exit"

#ifdef _WIN32

#include <windows.h>

int LoadSection(const char *sectionFileName, Section *sectionDest)
{    
    Section section;

    section.HModule = LoadLibrary(sectionFileName);

    if(section.HModule == NULL)
        return 0;

    *sectionDest = section;
    return 1;
}

int FreeSection(const Section *section)
{
    return FreeLibrary(section->HModule);
}

Function GetSectionFunction(const Section *section, const char *functionName)
{
    return (Function)GetProcAddress(section->HModule, functionName);
}

#endif