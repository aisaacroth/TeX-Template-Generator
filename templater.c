#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "templater.h"

/*
 * Templater.c - Generates a TeX template with required depcenies based on
 * what type of class is specified.
 * 
 * Author: Alexander Roth
 * Date:   2014-11-22
 */
static void printUsage();

int main(int argc, char **argv) {
    if (argc != 6) {
        printUsage();
    }

    const char *classInfo[5];
    prepareClassInfo(classInfo, argv);

    char *fileName = prepareFileName(classInfo);

    FILE *texFile = fopen(fileName, "w");
    free(fileName); 
    if (texFile == NULL) { 
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    if (isTechnicalClass(classInfo[1])) {
        writeTechnicalTemplate(texFile, classInfo);
    } else {
        writeStandardTemplate(texFile, classInfo);
    }

    printGeneratedStatement(classInfo);
    fclose(texFile);
    return 0;
}

static void printUsage() {
    fprintf(stderr, "usage: templater <class> <class number> <series>"
            " <series number> <directory>\n");
    exit(1);
}

void prepareClassInfo(const char **classInfo, char **argv) {
    char *className = argv[1];
    char *classNumber = argv[2];
    char *seriesType = argv[3];
    char *seriesNumber = argv[4];
    char *directory = argv[5];
    classInfo[0] = className;
    classInfo[1] = classNumber;
    classInfo[2] = seriesType;
    classInfo[3] = seriesNumber;
    classInfo[4] = directory;
}

char *prepareFileName(const char **classInfo) {
    const char *extension = ".tex";
    char *fileName = malloc(strlen(classInfo[4]) + strlen(classInfo[2]) + 1 
            + strlen(classInfo[3]) + strlen(extension));
    strcpy(fileName, classInfo[4]);
    strcat(fileName, classInfo[2]);
    strcat(fileName, "-");
    strcat(fileName, classInfo[3]);
    strcat(fileName, extension);
    return fileName;
}

int isTechnicalClass(const char *classNumber) {
    return (strstr(classNumber, "COMS") || strstr(classNumber, "CSEE"));
}

void writeTechnicalTemplate(FILE *texFile, const char **classInfo) {
    fprintf(texFile, "\\documentclass[]{article}\n");
    setTechnicalPackages(texFile);
    fprintf(texFile, "\\title{%s \\\\ %s \\\\ %s %s}\n", classInfo[0], 
            classInfo[1], classInfo[2], classInfo[3]);
    fprintf(texFile, "\\author{}\n");
    fprintf(texFile, "\\date{}\n");
    fprintf(texFile, "\\maketitle\n");
    fprintf(texFile, "\n");
    fprintf(texFile, "\\end{document}\n");
}

void setTechnicalPackages(FILE *texFile) {
    fprintf(texFile, "\\usepackage[all]{xy}\n");
    fprintf(texFile, "\\usepackage{amsmath}\n");
    fprintf(texFile, "\\usepackage{amssymb}\n");
    fprintf(texFile, "\\usepackage{amsthm}\n");
    fprintf(texFile, "\\usepackage{enumitem}\n");
    fprintf(texFile, "\\usepackage{indentfirst}\n");
    fprintf(texFile, "\\usepackage{listings}\n");
    fprintf(texFile, "\\usepackage{multirow}\n");
    fprintf(texFile, "\\usepackage{tikz}\n");
    fprintf(texFile, "\\usepackage{tikz-qtree}\n");
    fprintf(texFile, "\\usepackage{tipa}\n");
    fprintf(texFile, "\\begin{document}\n");
    fprintf(texFile, "\n");
    fprintf(texFile, "\\newtheorem{thm}{Theorem}\n");
}

void writeStandardTemplate(FILE *texFile, const char **classInfo) {
    fprintf(texFile, "\\documentclass[]{article}\n");
    fprintf(texFile, "\\usepackage{indentfirst}\n");
    fprintf(texFile, "\\begin{document}\n");
    fprintf(texFile, "\n");
    fprintf(texFile, "\\title{%s \\\\ %s \\\\ %s %s}\n", classInfo[0], 
            classInfo[1], classInfo[2], classInfo[3]);
    fprintf(texFile, "\\author{}\n");
    fprintf(texFile, "\\date{}\n");
    fprintf(texFile, "\\maketitle\n");
    fprintf(texFile, "\n");
    fprintf(texFile, "\\end{document}\n");
}

void printGeneratedStatement(const char **classInfo) {
    printf("Generated template for %s, %s %s\n", classInfo[0], classInfo[2], 
            classInfo[3]);
}
