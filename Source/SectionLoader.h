#ifndef __SECTION_LOADER__
#define __SECTION_LOADER__

#include "Sectional.h"

typedef void(*Function)(void);

int LoadSection(const char *sectionFileName, Section *sectionDest);
int FreeSection(const Section *section);
Function GetSectionFunction(const Section *section, const char *functionName);

#endif