#include <windows.h>
#include <cstdio>
#include <initguid.h>
#include <dbt.h>
// #include <iostream>
#include <print>
#include <Hidclass.h>
// #include <fmt/core.h>

/**
 * <iostream> increase size of 3KB
 * <print> increase size of 241KB ???!
 * <fmt/core.h> increase size of 123KB ???!
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_DEVICECHANGE) {
        switch (wParam) {
            case DBT_DEVICEREMOVECOMPLETE: {
                auto *pDevInf = (DEV_BROADCAST_DEVICEINTERFACE *)lParam;
                if (pDevInf && pDevInf->dbcc_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
                    std::printf("Device removed: %s", pDevInf->dbcc_name);
                    // std::println("Device removed: {}", pDevInf->dbcc_name);
                    // fmt::println("Device removed: {}", pDevInf->dbcc_name);
                    // std::cout << "Device removed: " << pDevInf->dbcc_name << std::endl;

                    // Check if the device is a mouse and run your program
                    // For demonstration, we just output it.
                    // check for a HID device
                    if (strstr(pDevInf->dbcc_name, "HID#VID_046D&PID_C092&MI_00")) {
                        PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
                    }
                }
            } break;
            case DBT_DEVICEARRIVAL: {
                auto *pDevInf = (DEV_BROADCAST_DEVICEINTERFACE *)lParam;
                if (pDevInf && pDevInf->dbcc_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
                    std::printf("Device arrived: %s", pDevInf->dbcc_name);
                    // std::println("Device arrived: {}", pDevInf->dbcc_name);
                    // fmt::println("Device arrived: {}", pDevInf->dbcc_name);
                    // std::cout << "Device arrived: " << pDevInf->dbcc_name << std::endl;
                }
            } break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
int main() {
    auto wc = WNDCLASS{
        .lpfnWndProc = WindowProc,
        .hInstance = GetModuleHandle(nullptr),
        .lpszClassName = "MouseDetectClass",
    };


    if (!RegisterClass(&wc)) {
        std::printf("Failed to register window class!");
        // std::println("Failed to register window class!");
        // fmt::println("Failed to register window class!");
        // std::cerr << "Failed to register window class!" << std::endl;
        return -1;
    }

    auto hwnd = CreateWindowEx(
        0, "MouseDetectClass", "Mouse Unplug Detection", 0, 0, 0, 0, 0, nullptr, nullptr,
        wc.hInstance, nullptr
    );

    if (!hwnd) {
        std::printf("Failed to create window!");
        // std::println("Failed to create window!");
        // fmt::println("Failed to create window!");
        // std::cerr << "Failed to create window!" << std::endl;
        return -1;
    }
           
    auto dbdi = DEV_BROADCAST_DEVICEINTERFACE{
        .dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE),
        .dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE,
        .dbcc_classguid = GUID_DEVINTERFACE_HID, // For HID devices (like mice)
    };




    RegisterDeviceNotification(hwnd, &dbdi, DEVICE_NOTIFY_WINDOW_HANDLE);

    // Run a message loop to keep the window alive and listen for device events
    auto msg = MSG{};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
