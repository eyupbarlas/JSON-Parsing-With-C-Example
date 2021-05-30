/**
 * @file                Test.c
 * @description         Bu programda Nesne Yönelimli benzetim esas alınarak, Struct kullanılarak oluşturulan yapı ile doc klasöründe bulunan JSON formatındaki
                        dosyaların okunup parse edilerek gerekli çıktıların alınması sağlanmıştır. 
 * @course              1. Öğretim A grubu
 * @assignment          2. Ödev
 * @date                09.05.2021
 * @author              Eyüp Barlas  eyup.barlas@ogr.sakarya.edu.tr
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "cJSON.h"
#include "Hisse.h"
#include "Emir.h"
#include "Portfoy.h"
#include "Banka.h"

//! Readfile function for reading files and returning as strings.
char *readFile(char *filename)
{
    FILE *f = fopen(filename, "rt");
    assert(f);
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = (char *)malloc(length + 1);
    buffer[length] = '\0';
    fread(buffer, 1, length, f);
    fclose(f);
    return buffer;
}

int main(int argc, char const *argv[])
{
    //! Reading files into strings.
    char *emirlerJSON_File = readFile("doc/emirler.json");
    char *portfoyJSON_File = readFile("doc/portfoy.json");
    char *hisselerJSON_File = readFile("doc/hisseler.json");

    //! Creating objects from structs.
    Hisse hisse = decodeHisseJson(hisselerJSON_File);
    Emir emir = decodeEmirJson(emirlerJSON_File);
    Portfoy portfoy = decodePortfoyJson(portfoyJSON_File);

    //! Storing all the JSON data into arrays.
    //* Hisseler
    char **hisseSembolArr = returnHisseSembol(hisse);
    double *hisseFiyatArr = returnGuncelFiyat(hisse);
    //* Emirler
    int *emirAdetArr = returnEmirAdet(emir);
    char **emirIslemArr = returnEmirIslem(emir);
    char **emirSembolArr = returnEmirSembol(emir);
    //* Portfoy
    char **portfoySembolArr = returnPortfoySembol(portfoy);
    int *portfoyAdetArr = returnPortfoyAdet(portfoy);
    double *portfoyMaliyetArr = returnPortfoyMaliyet(portfoy);

    //! Saving JSON file sizes into variables.
    int hisseSize = returnHisseSize(hisselerJSON_File);
    int emirSize = returnEmirSize(emirlerJSON_File);
    int portfoySize = returnPortfoySize(portfoyJSON_File);

    //! Creating arrays to save important data.
    double emirGuncelFiyat[emirSize]; // emir adet x güncel fiyat
    double maliyetXadet[portfoySize]; // portfoy maliyet x emir adet
    double portfoyEskiMaliyet[portfoySize]; // portfoy maliyet x portfoy adet

    int matchResultSatis;

    //! Comparing two array of strings and matching values.
    for (int i = 0; i < emirSize; i++)
    {
        for (int j = 0; j < hisseSize; j++)
        {
            matchResultSatis = strcmp(emirSembolArr[i], hisseSembolArr[j]);
            if (matchResultSatis == 0)
            {
                emirGuncelFiyat[i] += (emirAdetArr[i] * hisseFiyatArr[j]); // Finding current price of the ordered stock.
            }
        }
    }

    //! Calculating the cost of the stocks in portfolio.
    for (int i = 0; i < portfoySize; i++)
    {
        maliyetXadet[i] += (emirAdetArr[i] * portfoyMaliyetArr[i]); 
        portfoyEskiMaliyet[i] += (portfoyAdetArr[i] * portfoyMaliyetArr[i]);
    }
    printf("\n");

    //! Printing out the "kar-zarar" board and total exchange profit.
    double resultSatis[emirSize]; // For holding values of "Satis" operation.
    double resultAlis[emirSize];  // For holding values of "Alis" operation.
    double totalKarZarar = 0;

    char alis[] = "ALIS";
    char satis[] = "SATIS";

    printf("Satislar Kar/Zarar: \n");

    int satisIslemResult;
    int alisIslemResult;

    for (int i = 0; i < emirSize; i++)
    {
        satisIslemResult = strcmp(emirIslemArr[i], satis);
        alisIslemResult = strcmp(emirIslemArr[i], alis);
        
        if (satisIslemResult == 0) // if operation is :"SATIS"
        {
            resultSatis[i] += (emirGuncelFiyat[i] - maliyetXadet[i]);
            totalKarZarar += resultSatis[i];
            if (resultSatis[i] >= 0)
            {
                printf("%s : %g TL Kar\n", emirSembolArr[i], resultSatis[i]);
            }
            else
            {
                printf("%s : %g TL Zarar\n", emirSembolArr[i], resultSatis[i]);
            }
        }
        // if (alisIslemResult == 0) // if operation is :"ALIS"
        // {

        // }
    }
    printf("Toplam Kar/Zarar : %+g TL\n\n", totalKarZarar);

    //! Printing out the updated portfolio.
    printf("Guncel Portfoy:\n");

    for (int i = 0; i < portfoySize; i++)
    {
        printf("Hisse: %s\nAdet: %d\nMaliyet: %g\n", portfoySembolArr[i], portfoyAdetArr[i], portfoyMaliyetArr[i]);
        printf("--------------------------\n");
    }
    
    printf("\n");

    return 0;
}
