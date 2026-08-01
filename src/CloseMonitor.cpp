#include <windows.h>
/**
 * 做大死
 * 雖然不知道為什麼,但是main
 * 和WinMain一起會導致無限死循環,這個app無限黑屏,只能按住alt+f4然後開始祈禱
 * 但是用WinMain確實會快很多,因為不用啟動terminal
 */
// int main() {
//     PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
//     return 0;
// }


/* vibe, LGTM */
auto waitForInputRelease(DWORD timeoutMs = 2000) {
    auto IsAnyInputButtonDown = []() -> bool {
        // Includes keyboard keys and virtual mouse buttons.
        for (int vk = 1; vk < 256; ++vk) {
            if (GetAsyncKeyState(vk) & 0x8000) {
                return true;
            }
        }
        return false;
    };
    const auto deadline = GetTickCount64() + timeoutMs;
    while (IsAnyInputButtonDown() && GetTickCount64() < deadline) {
        Sleep(10);
    }
    // Small guard period after the final key-up event.
    // Sleep(50);
}

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
    // PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    // Sleep(500);
    // PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);


    waitForInputRelease();
    /* 這個理論上不會broadcast影響很多了 */
    DefWindowProc(GetDesktopWindow(), WM_SYSCOMMAND, SC_MONITORPOWER, 2); // power off
    // Sleep(500);
    // DefWindowProc(GetDesktopWindow(), WM_SYSCOMMAND, SC_MONITORPOWER, 2); // power off
    return 0;
}
