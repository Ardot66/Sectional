#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "Sectional.h"
#include "SectionLoader.h"

#define QUOTE(value) # value
#define STRING(value) QUOTE(value)

#define STARTING_SECTIONS_LENGTH 4

int (*ProcessLoop)(int argCount, char **argValues);

size_t SectionsLength = 0;
size_t SectionsCount = 0;
Section *Sections = NULL;

int ProgramArgCount = 0;
char **ProgramArgValues = NULL;

int IsSection(const struct dirent *entry)
{   
    return strcmp(entry->d_name + entry->d_namlen - strlen(SECTION_FILE_EXTENSION), SECTION_FILE_EXTENSION) == 0;
}

int CallSectionEntryPoint(const Section *section, const char *entryPointName, int argCount, char **argValues)
{
    SectionEntryPointFunction entryPoint = (SectionEntryPointFunction)GetSectionFunction(section, entryPointName);

    if(entryPoint == NULL)
        return 0;

    return entryPoint(argCount, argValues);
}

void SetSectionsLength(size_t newLength)
{
    SectionsLength = newLength;
    Section *newSections;

    if(Sections == NULL)
        newSections = malloc(sizeof(Section) * newLength);
    else
        newSections = realloc(Sections, sizeof(Section) * newLength);

    if(newSections == NULL)
        exit(errno);

    Sections = newSections;
}

int RemoveSection(const size_t sectionIndex)
{
    if(sectionIndex >= SectionsCount)
        return 0;

    for(int x = sectionIndex; x < SectionsCount - 1; x++)
        Sections[x] = Sections[x + 1];
    
    SectionsCount--;

    return 1;
}

Section *AddSection(const Section section)
{
    if(SectionsCount >= SectionsLength)
        SetSectionsLength((SectionsLength * 3) / 2);
    
    Section *sectionPointer = Sections + SectionsCount;
    *sectionPointer = section;
    SectionsCount++;

    return sectionPointer;
}

int GetSection(const size_t sectionIndex, Section **sectionDest)
{
    if(sectionIndex >= SectionsCount)
        return 0;

    *sectionDest = Sections + sectionIndex;
    return 1;
}

size_t GetSectionCount()
{
    return SectionsCount;
}

void SetProcessLoop(int (*processLoop)(int argCount, char **argValues))
{
    ProcessLoop = processLoop;
}

void Exit()
{
    for(int x = 0; x < SectionsCount; x++)
    {
        Section *section = Sections + x;

        CallSectionEntryPoint(section, STRING(_SECTION_EXIT_NAME), ProgramArgCount, ProgramArgValues);
        FreeSection(section);
    }

    if(Sections != NULL)
        free(Sections);
}

int SectionalMain(int argCount, char **argValues)
{
    atexit(Exit);

    ProgramArgCount = argCount;
    ProgramArgValues = argValues;

    SetSectionsLength(STARTING_SECTIONS_LENGTH);

    {
        DIR *directory = opendir(".");

        if(directory == NULL)
            return errno;

        struct dirent *entry;

        while(entry = readdir(directory))
        {
            if(!IsSection(entry))
                continue;
            
            Section section;

            if(!LoadSection(entry->d_name, &section))
                continue;

            Section *sectionPointer = AddSection(section);
            CallSectionEntryPoint(sectionPointer, STRING(_SECTION_INITIALIZE_NAME), argCount, argValues);
        }

        closedir(directory);
    }

    for(int x = 0; x < SectionsCount; x++)
        CallSectionEntryPoint(Sections + x, STRING(_SECTION_REGISTER_NAME), argCount, argValues);

    for(int x = 0; x < SectionsCount; x++)
        CallSectionEntryPoint(Sections + x, STRING(_SECTION_READY_NAME), argCount, argValues);

    if(ProcessLoop != NULL)
        return ProcessLoop(argCount, argValues);
}