/**
 * @file                Test.c
 * @description         Bu programda Nesne Yönelimli programlama esas alınarak, Struct kullanılarak oluşturulan yapı ile doc klasöründe bulunan JSON formatındaki
                        dosyaların okunup parse edilerek gerekli çıktıların alınması sağlanmıştır. 
 * @course              1. Öğretim A grubu
 * @assignment          2. Ödev
 * @date                09.05.2021
 * @author              Eyüp Barlas  eyup.barlas@ogr.sakarya.edu.tr
 */

#include "Portfoy.h"
#include "cJSON.h"

Portfoy decodePortfoyJson(char *jsonfile)
{
    cJSON *portfoyRoot = cJSON_Parse(jsonfile);
    if (portfoyRoot == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    cJSON *portfoyler = cJSON_GetObjectItem(portfoyRoot, "Portfoy");
    int portfoyCount = cJSON_GetArraySize(portfoyler);

    Portfoy portfoyTest = (Portfoy)malloc(sizeof(struct PORTFOY));
    for (int i = 0; i < portfoyCount; i++)
    {
        cJSON *portfoy = cJSON_GetArrayItem(portfoyler, i);

        char *_id = cJSON_GetObjectItem(portfoy, "_id")->valuestring;
        portfoyTest->_id[i] = _id;
        char *sembol = cJSON_GetObjectItem(portfoy, "Sembol")->valuestring;
        portfoyTest->sembol[i] = sembol;
        double maliyet = cJSON_GetObjectItem(portfoy, "Maliyet")->valuedouble;
        portfoyTest->maliyet[i] = maliyet;
        int adet = cJSON_GetObjectItem(portfoy, "Adet")->valueint;
        portfoyTest->adet[i] = adet;
    }

end:
    return portfoyTest;
}

char **returnPortfoySembol(const Portfoy myPortfolio){
    return myPortfolio->sembol;
}

int *returnPortfoyAdet(const Portfoy myPortfolio){
    return myPortfolio->adet;
}

double *returnPortfoyMaliyet(const Portfoy myPortfolio){
    return myPortfolio->maliyet;
}

int returnPortfoySize(char *jsonfile){
    cJSON *portfoyRoot = cJSON_Parse(jsonfile);

    cJSON *portfoyler = cJSON_GetObjectItem(portfoyRoot, "Portfoy");
    int portfoyCount = cJSON_GetArraySize(portfoyler);

    return portfoyCount;
}