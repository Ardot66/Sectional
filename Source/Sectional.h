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

// The function pointer to the function that will contain the program's process loop, if any.
// If non-null, this function will be called right at the end of the main function.
extern int (*ProcessLoop)(int argCount, char **argValues);

extern Section *Sections;

#undef SECTION_ENTRY_POINT_RETURNS
#undef SECTION_ENTRY_POINT_PARAMETERS

#endif