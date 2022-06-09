#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>

/*

    https://stackoverflow.com/questions/7956519/how-to-kill-processes-by-name-win32-api
*/

void killProcessByName(const char *filename)
{

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

    PROCESSENTRY32 pEntry;

    pEntry.dwSize = sizeof (pEntry);

    BOOL hRes = Process32First(hSnapShot, &pEntry);

    while (hRes)
    {
        if (strcmp(pEntry.szExeFile, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }

    CloseHandle(hSnapShot);
}

int main()
{
    killProcessByName("notepad++.exe");
    return 0;
}
