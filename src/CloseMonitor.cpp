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
int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) {
    PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    Sleep(500);
    PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    return 0;
}
