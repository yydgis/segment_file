
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

static int segment_file(const char* fname)
{
    int ret = 0;
    FILE* fLOG = fopen(fname, "rb");
    FILE* fOUT = nullptr;
    int seg = 0;
    size_t bytesRead = 0;
    size_t count = 0;
    size_t count_total = 0;
    char filename[255] = { 0 };
    char buffer[1024] = { 0 };
    strcpy(filename, fname);
    char* temp = strrchr(filename, '.');
    if (temp) temp[0] = '\0';
    sprintf(buffer, "%s.%03i", filename, seg);
    fOUT = fopen(buffer, "wb");
    while (fLOG && !feof(fLOG) && (bytesRead = fread(buffer, 1, sizeof(buffer) - 1, fLOG)) > 0)
    {
        if (fOUT) fwrite(buffer, sizeof(char), bytesRead, fOUT);
        count += bytesRead;
        count_total += bytesRead;
        /* 1,073,741,824 = 1G*/
        if (count > 1073741824)
        {
            seg++;
            if (fOUT) fclose(fOUT);
            sprintf(buffer, "%s.%03i", filename, seg);
            fOUT = fopen(buffer, "wb");
            count = 0;
            printf("%s %i, %ul\n", buffer, seg, count_total);
        }
    }
    if (fLOG) fclose(fLOG);
    if (fOUT) fclose(fOUT);
    printf("%s %i, %ul\n", buffer, seg, count_total);
    return ret;
}

int main(int argc, const char* argv[])
{
    if (argc > 2)
    {
        segment_file(argv[1]);
    }
    return 0;
}

