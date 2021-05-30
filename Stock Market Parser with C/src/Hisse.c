/**
 * @file                Test.c
 * @description         Bu programda Nesne Yönelimli programlama esas alınarak, Struct kullanılarak oluşturulan yapı ile doc klasöründe bulunan JSON formatındaki
                        dosyaların okunup parse edilerek gerekli çıktıların alınması sağlanmıştır. 
 * @course              1. Öğretim A grubu
 * @assignment          2. Ödev
 * @date                09.05.2021
 * @author              Eyüp Barlas  eyup.barlas@ogr.sakarya.edu.tr
 */

#include "Hisse.h"
#include "cJSON.h"
#include <string.h>

Hisse decodeHisseJson(char *jsonfile) // constructor
{
    cJSON *hisselerRoot = cJSON_Parse(jsonfile);
    if (hisselerRoot == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    cJSON *hisseler = cJSON_GetObjectItem(hisselerRoot, "Hisseler");
    int hisseCount = cJSON_GetArraySize(hisseler);

    Hisse hisseTest = (Hisse)malloc(sizeof(struct HISSE));
    for (int i = 0; i < hisseCount; i++)
    {
        cJSON *hisse = cJSON_GetArrayItem(hisseler, i);

        char *_id = cJSON_GetObjectItem(hisse, "_id")->valuestring;
        hisseTest->_id[i] = _id;
        char *sembol = cJSON_GetObjectItem(hisse, "Sembol")->valuestring;
        hisseTest->sembol[i] = sembol;
        char *ad = cJSON_GetObjectItem(hisse, "Ad")->valuestring;
        hisseTest->ad[i] = ad;
        double fiyat = cJSON_GetObjectItem(hisse, "Fiyat")->valuedouble;
        hisseTest->fiyat[i] = fiyat;
    }

end:
    return hisseTest;
}

char **returnHisseSembol(const Hisse myStock){
    return myStock->sembol;
}

double *returnGuncelFiyat(const Hisse myStock){
    return myStock->fiyat;
}

int returnHisseSize(char *jsonfile){
    cJSON *hisselerRoot = cJSON_Parse(jsonfile);

    cJSON *hisseler = cJSON_GetObjectItem(hisselerRoot, "Hisseler");
    int hisseCount = cJSON_GetArraySize(hisseler);
    
    return hisseCount;
}