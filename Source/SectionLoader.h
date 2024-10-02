#ifndef __SECTION_LOADER__
#define __SECTION_LOADER__

typedef struct Section Section;

#ifdef _WIN32

#include <windows.h>

#define SECTION_FILE_EXTENSION ".dll"

struct Section
{
    HMODULE HModule;
};

#endif

typedef void(*Function)(void);

int LoadSection(const char *sectionFileName, Section *sectionDest);
int FreeSection(const Section *section);
Function GetSectionFunction(const Section *section, const char *functionName);

#endif