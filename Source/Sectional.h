#ifndef __SECTIONAL__
#define __SECTIONAL__

#include "SectionLoader.h"

#define _SECTION_ENTRY_POINT_RETURNS int
#define _SECTION_ENTRY_POINT_PARAMETERS int argCount, char **argValues

#define _SECTION_INITIALIZE_NAME SectionInitialize
#define _SECTION_REGISTER_NAME SectionRegister
#define _SECTION_READY_NAME SectionReady
#define _SECTION_EXIT_NAME SectionExit

// Macro for defining SectionInitialize entry point.
// This is the first entry point called for any section.
// This entry point should be used to make necessary memory allocations and set up the basic functionality of the section.
#define SECTION_INITIALIZE _SECTION_ENTRY_POINT_RETURNS _SECTION_INITIALIZE_NAME (_SECTION_ENTRY_POINT_PARAMETERS)

// Macro for defining SectionRegister entry point.
// This is the second entry point called for any section.
// This entry point should be used to register data with other entry points, but not to perform any actual functionality.
#define SECTION_REGISTER _SECTION_ENTRY_POINT_RETURNS _SECTION_REGISTER_NAME (_SECTION_ENTRY_POINT_PARAMETERS)

// Macro for defining SectionInitialize entry point.
// This is third first entry point called for any section.
// This is where sections can actually do stuff like creating windows and running functions.
#define SECTION_READY _SECTION_ENTRY_POINT_RETURNS _SECTION_READY_NAME (_SECTION_ENTRY_POINT_PARAMETERS)

// Macro for defining SectionInitialize entry point.
// This is the fourth and final entry point called for any section.
// This entry point should be used to free any outstanding memory allocations, and should safely remove this section from the program.j
#define SECTION_EXIT _SECTION_ENTRY_POINT_RETURNS _SECTION_EXIT_NAME (_SECTION_ENTRY_POINT_PARAMETERS)

// The function signature of any section entry point.
// All section enty points should be passed the same arguments as from the main function of the program.
typedef _SECTION_ENTRY_POINT_RETURNS (*SectionEntryPointFunction)(_SECTION_ENTRY_POINT_PARAMETERS);

// Calls a particular entry point function in a section.
// Returns 0 on failure, or 1 on success.
// All entry point functions follow the same pattern as the main function of any program.
// There are four default entry points included in sectional: Initialize, Register, Ready, and Exit.
int CallSectionEntryPoint(const Section *section, const char *entryPointName, int argCount, char **argValues);

// Removes a section from the list of sections.
// This function should almost always be coupled with FreeSection and calling section entry point Exit, which actually unloads and frees the section.
int RemoveSection(const size_t sectionIndex);

// Adds a section to the list of sections.
Section *AddSection(const Section section);

// Gets a section from the list of sections.
int GetSection(const size_t sectionIndex, Section **sectionDest);

// Gets the total number of sections in the list of sections.
size_t GetSectionCount();

// Sets the function that will be called after all sections are initialized, and should contain the processing loop of the program.
// This does not need to be set, and for programs that do not need a processing loop this function does not need to be called.
void SetProcessLoop(int (*processLoop)(int argCount, char **argValues));

// The main function of Sectional.c.
// Only intended to be called from the main executeable, do not call from anywhere else.
int SectionalMain(int argCount, char **argValues);

#endif