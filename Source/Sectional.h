#ifndef __SECTIONAL__
#define __SECTIONAL__

#define SECTION_ENTRY_POINT_RETURNS int
#define SECTION_ENTRY_POINT_PARAMETERS int argCount, char **argValues

#define _SECTION_INITIALIZE_NAME SectionInitialize
#define _SECTION_REGISTER_NAME SectionRegister
#define _SECTION_READY_NAME SectionReady
#define _SECTION_EXIT_NAME SectionExit

#define SECTION_INITIALIZE SECTION_ENTRY_POINT_RETURNS _SECTION_INITIALIZE_NAME (SECTION_ENTRY_POINT_PARAMETERS)
#define SECTION_REGISTER SECTION_ENTRY_POINT_RETURNS _SECTION_REGISTER_NAME (SECTION_ENTRY_POINT_PARAMETERS)
#define SECTION_READY SECTION_ENTRY_POINT_RETURNS _SECTION_READY_NAME (SECTION_ENTRY_POINT_PARAMETERS)
#define SECTION_EXIT SECTION_ENTRY_POINT_RETURNS _SECTION_EXIT_NAME (SECTION_ENTRY_POINT_PARAMETERS)

typedef struct Section Section;
typedef SECTION_ENTRY_POINT_RETURNS (*SectionEntryPointFunction)(SECTION_ENTRY_POINT_PARAMETERS);

#ifdef _WIN32

#include <windows.h>

struct Section
{
    HMODULE HModule;
};

#endif

int CallSectionEntryPoint(const Section *section, const char *entryPointName, int argCount, char **argValues);
void SetSectionsLength(size_t newLength);
int RemoveSection(const size_t sectionIndex);
Section *AddSection(const Section section);
int GetSection(const size_t sectionIndex, Section **sectionDest);
size_t GetSectionCount();
void SetProcessLoop(int (*processLoop)(int argCount, char **argValues));

#undef SECTION_ENTRY_POINT_RETURNS
#undef SECTION_ENTRY_POINT_PARAMETERS

#endif