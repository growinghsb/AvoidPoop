#include "Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(229);

    if (!Core::getInstance()->init(hInstance)) 
    {
        Core::deleteInstance();
        return 0;
    }

    int resultValue = Core::getInstance()->run();

    Core::deleteInstance();

    return resultValue;
}
