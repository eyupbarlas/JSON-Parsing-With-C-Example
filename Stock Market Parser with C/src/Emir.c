/**
 * @file                Test.c
 * @description         Bu programda Nesne Yönelimli programlama esas alınarak, Struct kullanılarak oluşturulan yapı ile doc klasöründe bulunan JSON formatındaki
                        dosyaların okunup parse edilerek gerekli çıktıların alınması sağlanmıştır. 
 * @course              1. Öğretim A grubu
 * @assignment          2. Ödev
 * @date                09.05.2021
 * @author              Eyüp Barlas  eyup.barlas@ogr.sakarya.edu.tr
 */

#include "Emir.h"
#include "cJSON.h"

Emir decodeEmirJson(char *jsonfile)
{
    cJSON *emirRoot = cJSON_Parse(jsonfile);
    if (emirRoot == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    cJSON *emirler = cJSON_GetObjectItem(emirRoot, "Emirler");
    int emirCount = cJSON_GetArraySize(emirler);

    Emir emirTest = (Emir)malloc(sizeof(struct EMIR));
    for (int i = 0; i < emirCount; i++)
    {
        cJSON *emir = cJSON_GetArrayItem(emirler, i);

        char *_id = cJSON_GetObjectItem(emir, "_id")->valuestring;
        emirTest->_id[i] = _id;
        char *sembol = cJSON_GetObjectItem(emir, "Sembol")->valuestring;
        emirTest->sembol[i] = sembol;
        char *islem = cJSON_GetObjectItem(emir, "Islem")->valuestring;
        emirTest->islem[i] = islem;
        int adet = cJSON_GetObjectItem(emir, "Adet")->valueint;
        emirTest->adet[i] = adet;
    }

end:
    
    return emirTest;
}

int *returnEmirAdet(const Emir myOrder){
    return myOrder->adet;
}

char **returnEmirSembol(const Emir myOrder){
    return myOrder->sembol;
}

char **returnEmirIslem(const Emir myOrder){
    return myOrder->islem;
}

int returnEmirSize(char *jsonfile){
    cJSON *emirRoot = cJSON_Parse(jsonfile);

    cJSON *emirler = cJSON_GetObjectItem(emirRoot, "Emirler");
    int emirCount = cJSON_GetArraySize(emirler);
    
    return emirCount;
}