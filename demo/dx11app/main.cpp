#include "stable.h"

#include "./src/basicdrawapp.h"
#include "./src/basiclightingapp.h"
#include "./src/basictextureapp.h"
#include "./src/basictextureapp2.h"
#include "./src/basicstencilapp.h"

#pragma comment(lib, "imm32.lib")

#include <ShellScalingApi.h>
// Link against Shcore.lib
#pragma comment(lib, "Shcore.lib")

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE , _In_ LPSTR , _In_ int )
{
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    BasicTextureApp2 app;

    bool ok = app.Init(hInstance);

    ImmAssociateContext(app.window(), NULL);

    app.RunLoop();

    return 0;
}