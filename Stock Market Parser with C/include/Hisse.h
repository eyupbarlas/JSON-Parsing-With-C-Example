#ifndef HISSE_H
#define HISSE_H

#include <stdio.h>
#include <stdlib.h>

struct HISSE
{
    char *_id[200];
    char *sembol[200];
    char *ad[200];
    double fiyat[200];
};
typedef struct HISSE *Hisse;

Hisse decodeHisseJson(char *jsonfile);
char **returnHisseSembol(const Hisse myStock);
double *returnGuncelFiyat(const Hisse myStock);
int returnHisseSize(char *jsonfile);

#endif