#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printUsage();
void prepareClassInfo(const char **classInfo, char **argv);
char *prepareFileName(const char **classInfo);
int isCSClass(const char *classNumber);
void writeTechnicalTemplate(FILE *texFile, const char **classInfo);
void setTechnicalPackages(FILE *texFile);
void writeStandardTemplate(FILE *texFile, const char **classInfo);
void printGeneratedStatement(const char **classInfo);

int main(int argc, char **argv) {
    if (argc != 5) {
        printUsage();
    }

    const char *classInfo[4];
    prepareClassInfo(classInfo, argv);

    char *fileName = prepareFileName(classInfo);

    FILE *texFile = fopen(fileName, "w");
    free(fileName); 
    if (texFile == NULL) { 
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    if (isCSClass(classInfo[1])) {
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
            " <series number>\n");
    exit(1);
}

void prepareClassInfo(const char **classInfo, char **argv) {
    char *className = argv[1];
    char *classNumber = argv[2];
    char *seriesType = argv[3];
    char *seriesNumber = argv[4];
    classInfo[0] = className;
    classInfo[1] = classNumber;
    classInfo[2] = seriesType;
    classInfo[3] = seriesNumber;
}

char *prepareFileName(const char **classInfo) {
    const char *extension = ".tex";
    char *fileName = malloc(strlen(classInfo[2]) + 1 + strlen(classInfo[3]) 
            + strlen(extension));
    strcpy(fileName, classInfo[2]);
    strcat(fileName, "-");
    strcat(fileName, classInfo[3]);
    strcat(fileName, extension);
    return fileName;
}

int isCSClass(const char *classNumber) {
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
