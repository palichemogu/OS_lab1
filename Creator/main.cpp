#include <iostream>
using namespace std;

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main() {
    int i, n;
    FILE* out;
    struct employee s;
    char filename[10];
    printf("Input a name of bin file: ");
    scanf("%s", filename);
    out = fopen(filename, "wb");
    printf("Input a number of records to write: ");
    scanf("%d", &n);
    if (n < 0)
        return 0;
    printf("Input num, name and hours.\n");
    for (i = 0; i < n; ++i)
    {
        printf("%d> ", i + 1);
        scanf("%d%s%lf", &s.num, &s.name, &s.hours);
        fwrite(&s, sizeof(struct employee), 1, out);
    }
    fclose(out);

    return 0;
}
