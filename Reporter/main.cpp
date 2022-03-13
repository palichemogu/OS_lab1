#include "stdio.h"

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main() {
    FILE* in;
    FILE* out;
    employee s;
    char nameOfBinFile[10];
    char nameOfTxtFile[10];
    double paymentPerHour;
    printf("%s","Enter bin file name:");
    scanf("%s", nameOfBinFile);
    printf("%s","Enter txt file name:");
    scanf("%s", nameOfTxtFile);
    printf("%s", "Enter payment per hour:");
    scanf("%lf", &paymentPerHour);
    if (!(in = fopen(nameOfBinFile, "rb")))
    {
        printf("Opening bin file failed.\n");
        return 1;
    }
    if (!(out = fopen(nameOfTxtFile,"w"))) {
        printf("Opening txt file failed.\n");
        return 1;
    }
    fprintf(out, "%s: %s\n", "Report of file", nameOfBinFile);
    fprintf(out,"%s", "Number        Name           Hours        Salary\n");
    for(int i = 0; ; i++){
        fseek(in, i*sizeof(struct employee), SEEK_SET);
        if (!fread(&s, sizeof(employee), 1, in)){
            break;
        }
        fprintf(out,"%d\t\t%s\t\t%lf\t\t%lf\n", s.num, s.name, s.hours, s.hours * paymentPerHour);
    }
    fclose(in);
    return 0;
}
