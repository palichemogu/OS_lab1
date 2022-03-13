#include<Windows.h>
#include "stdio.h";
#include<exception>

struct employee
{
    int num;
    char name[10];
    double hours;
};

void CallProcess(char* commandLine)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    if( !CreateProcess( NULL,
                        commandLine,
                        NULL,
                        NULL,
                        FALSE,
                        0,
                        NULL,
                        NULL,
                        &si,
                        &pi )
            )
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return;
    }

    WaitForSingleObject( pi.hProcess, INFINITE );

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

char* CreateCommandLine(const char* name, char** params, int size)
{
    char *commandLine = new char[strlen(name) + 1];
    strcpy(commandLine, name);
    for (int i = 0; i < size; i++){
        strcat(commandLine, " ");
        strcat(commandLine, params[i]);
    }
    return commandLine;
}

void outputBinaryFileDataInConsole(const char* nameOfBinFile) {
    employee s;
    FILE* in = fopen(nameOfBinFile, "rb");
    for(int i = 0; ; i++){
        fseek(in, i*sizeof(struct employee), SEEK_SET);
        if (!fread(&s, sizeof(employee), 1, in)){
            break;
        }
        printf("%02X\t\t%02X\t\t%02X\n", s.num, s.name, s.hours);
    }
}

void outputReportInConsole(const char* nameOfTxtFile) {
    int ch;
    FILE* input = fopen(nameOfTxtFile, "r");
    while (!feof(input)) {
        ch = getc(input);
        if (ch != EOF) {
            putchar(ch);
        }
    }
}

int main() {
    //--------------------Creator-------------
    char nameOfBinFile[10];
    char numberOfEmployees[10];
    printf("%s", "Enter name of bin file:");
    scanf("%s", nameOfBinFile);
    printf("%s", "Enter number of employees in file:");
    scanf("%s", numberOfEmployees);
    char** creatorParams = new char*[2];
    creatorParams[0] = nameOfBinFile;
    creatorParams[1] = numberOfEmployees;
    char* CreatorCommandLine = CreateCommandLine("Creator.exe", creatorParams, 2);
    CallProcess(CreatorCommandLine);

    outputBinaryFileDataInConsole(nameOfBinFile);
    //-----------------Reporter------------------------
    char nameOfTxtFile[10];
    char paymentPerHour[10];
    printf("%s", "Enter name of txt file:");
    scanf("%s", nameOfTxtFile);
    printf("%s", "Enter payment per hour:");
    scanf("%s", paymentPerHour);
    char** reporterParams = new char*[3];
    reporterParams[0] = nameOfBinFile;
    reporterParams[1] = nameOfTxtFile;
    reporterParams[2] = paymentPerHour;
    char* reporterCommandLine = CreateCommandLine("Reporter.exe", reporterParams, 3);
    CallProcess(reporterCommandLine);

    outputReportInConsole(nameOfTxtFile);
    return 0;
}
