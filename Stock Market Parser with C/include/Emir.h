#ifndef EMIR_H
#define EMIR_H

#include <stdio.h>
#include <stdlib.h>

struct EMIR
{
    char *_id[100];
    char *sembol[100];
    char *islem[100];
    int adet[100];
};
typedef struct EMIR* Emir;

Emir decodeEmirJson(char *jsonfile);
int *returnEmirAdet(const Emir myOrder);
char **returnEmirSembol(const Emir myOrder);
char **returnEmirIslem(const Emir myOrder);
int returnEmirSize(char *jsonfile);

#endif