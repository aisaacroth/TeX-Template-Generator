#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printUsage();
int isCSClass(char *classNumber);
void writeTechnicalTemplate(FILE *texFile, const char **classInfo);
void setTechnicalPackages(FILE *texFile);
void writeStandardTemplate(FILE *texFile, const char **classInfo);

int main(int argc, char **argv) {
    if (argc != 5) {
        printUsage();
    }

    char *className = argv[1];
    char *classNumber = argv[2];
    char *seriesType = argv[3];
    char *seriesNumber = argv[4];

    const char *classInfo[4];
    classInfo[0] = className;
    classInfo[1] = classNumber;
    classInfo[2] = seriesType;
    classInfo[3] = seriesNumber;

    char *fileName;
    const char *extension = ".tex";
    fileName = malloc(strlen(seriesType) + 1 + strlen(seriesNumber) + 
            strlen(extension));
    strcpy(fileName, seriesType);
    strcat(fileName, "-");
    strcat(fileName, seriesNumber);
    strcat(fileName, extension);

    FILE *texFile = fopen(fileName, "w");
    free(fileName); 
    if (texFile == NULL) { fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    if (isCSClass(classNumber)) {
        writeTechnicalTemplate(texFile, classInfo);
    } else {
        writeStandardTemplate(texFile, classInfo);
    }


    printf("Generated template for %s, %s %s\n", className, seriesType, 
            seriesNumber);
    fclose(texFile);
    return 0;
}

static void printUsage() {
    fprintf(stderr, "usage: templater <class> <class number> <series>"
            " <series number>\n");
    exit(1);
}

int isCSClass(char *classNumber) {
    return (strstr(classNumber, "COMS") || strstr(classNumber, "CSEE"));
}

void writeTechnicalTemplate(FILE *texFile, const char **classInfo) {
    fprintf(texFile, "\\documentclass[]{article}\n");
    setTechnicalPackages(texFile);
    fprintf(texFile, "\\title{%s \\\\ %s \\\\ %s %s}\n", classInfo[0], 
            classInfo[1], classInfo[2], classInfo[3]);
    fprintf(texFile, "\\author{}\n");
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
    fprintf(texFile, "\\title{%s \\\\ %s \\\\ %s %s}\n", classInfo[0], 
            classInfo[1], classInfo[2], classInfo[3]);
    fprintf(texFile, "\\author{}\n");
    fprintf(texFile, "\\maketitle\n");
    fprintf(texFile, "\n");
    fprintf(texFile, "\\end{document}\n");
}
