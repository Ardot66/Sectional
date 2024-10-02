#ifndef __SECTIONAL__
#define __SECTIONAL__

#include "SectionLoader.h"

#define _SECTION_ENTRY_POINT_RETURNS int
#define _SECTION_ENTRY_POINT_PARAMETERS int argCount, char **argValues

#define _SECTION_INITIALIZE_NAME SectionInitialize
#define _SECTION_REGISTER_NAME SectionRegister
#define _SECTION_READY_NAME SectionReady
#define _SECTION_EXIT_NAME SectionExit

#define SECTION_INITIALIZE _SECTION_ENTRY_POINT_RETURNS _SECTION_INITIALIZE_NAME (_SECTION_ENTRY_POINT_PARAMETERS)
#define SECTION_REGISTER _SECTION_ENTRY_POINT_RETURNS _SECTION_REGISTER_NAME (_SECTION_ENTRY_POINT_PARAMETERS)
#define SECTION_READY _SECTION_ENTRY_POINT_RETURNS _SECTION_READY_NAME (_SECTION_ENTRY_POINT_PARAMETERS)
#define SECTION_EXIT _SECTION_ENTRY_POINT_RETURNS _SECTION_EXIT_NAME (_SECTION_ENTRY_POINT_PARAMETERS)

typedef _SECTION_ENTRY_POINT_RETURNS (*SectionEntryPointFunction)(_SECTION_ENTRY_POINT_PARAMETERS);

int CallSectionEntryPoint(const Section *section, const char *entryPointName, int argCount, char **argValues);
void SetSectionsLength(size_t newLength);
int RemoveSection(const size_t sectionIndex);
Section *AddSection(const Section section);
int GetSection(const size_t sectionIndex, Section **sectionDest);
size_t GetSectionCount();
void SetProcessLoop(int (*processLoop)(int argCount, char **argValues));

#endif