#ifndef PORTFOY_H
#define PORTFOY_H

#include <stdio.h>
#include <stdlib.h>

struct PORTFOY
{
    char *_id[100];
    char *sembol[100];
    double maliyet[100];
    int adet[100];
};
typedef struct PORTFOY* Portfoy;

Portfoy decodePortfoyJson(char *jsonfile);
char **returnPortfoySembol(const Portfoy myPortfolio);
int *returnPortfoyAdet(const Portfoy myPortfolio);
double *returnPortfoyMaliyet(const Portfoy myPortfolio);
int returnPortfoySize(char *jsonfile);

#endif