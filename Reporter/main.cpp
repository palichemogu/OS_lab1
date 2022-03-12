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
    if (!(in = fopen("ggg.bin", "rb")))
    {
        printf("Opening file failed.\n");
        return 1;
    }
    printf("%s\n", "Number		Name		Hours		Salary");
    for(int i = 0; ; i++){
        fseek(in, i*sizeof(struct employee), SEEK_SET);
        if (!fread(&s, sizeof(employee), 1, in)){
            break;
        }
        printf("%d \t\t %s \t\t %lf\n", s.num, s.name, s.hours);
    }
    fclose(in);
    return 0;
}
