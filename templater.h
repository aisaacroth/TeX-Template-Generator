/*
 * templater.h - The header file for templater.c
 *
 * Author: Alexander Roth
 * Date:   2014-11-22
 */

#ifndef __TEMPLATER_H__
#define __TEMPLATER_H__

void prepareClassInfo(const char **classInfo, char **argv);
char *prepareFileName(const char **classInfo);
int isTechnicalClass(const char *classNumber);
void writeTechnicalTemplate(FILE *texFile, const char **classInfo);
void setTechnicalPackages(FILE *texFile);
void writeStandardTemplate(FILE *texFile, const char **classInfo);
void printGeneratedStatement(const char **classInfo);

#endif
