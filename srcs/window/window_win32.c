#include "window.h"
#include "../includes/MiniRT.h"
#include <windows.h>
#include <assert.h>

typedef struct s_platform_window
{
    HWND hwnd;
    HDC  hdc;
} t_platform_window;

static BITMAPINFO global_bitmap_info = {};
//-- TODO: Find better solution
t_scene* glob_scene = NULL;

t_key convert_win_key_to_inner(char key)
{
    switch (key)
    {
    // case (SDL_SCANCODE_TAB):
    //     return RT_SCANCODE_TAB;
    case ('W'):
        return RT_SCANCODE_W;
    case ('S'):
        return RT_SCANCODE_S;
    case ('A'):
        return RT_SCANCODE_A;
    case ('D'):
        return RT_SCANCODE_D;
    case ('E'):
        return RT_SCANCODE_E;
    case ('Q'):
        return RT_SCANCODE_Q;
    // case (SDL_SCANCODE_ESCAPE):
    //     return RT_SCANCODE_ESCAPE;
    default:
        break;
    }
    return NONE;
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    {
        [[maybe_unused]] const bool isEsc   = (wParam == VK_ESCAPE);
        [[maybe_unused]] const bool isCtrl  = (wParam == VK_CONTROL);
        [[maybe_unused]] const bool isShift = (wParam == VK_SHIFT);

        // 30 	The previous key state. The value is 1 if the key is down before the message is sent, or it is zero if
        // the key is up.
        [[maybe_unused]] bool prevStateIsDown = !!((1 << 30) & lParam);
        // 31 	The transition state. The value is always 0 for a WM_KEYDOWN message.
        [[maybe_unused]] bool currStateIsDown = !((1 << 31) & lParam);

        press_key(convert_win_key_to_inner(wParam), glob_scene);

        return 0;
    }

    case WM_CLOSE:
    {
        exit_rt(glob_scene);
        return 0;
    }

    case WM_SIZE:
    {
    }
        return 0;
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

t_window create_window(const char* name, i32 width, i32 height, t_memory_arena* arena)
{
    t_platform_window* pl_win = arena_push(arena, sizeof(t_platform_window));
    t_window           res;

    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASS  wc        = {};

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = name;

    RegisterClassA(&wc);
    // Create the window.

    pl_win->hwnd = CreateWindowExA(0,                   // Optional window styles.
                                   name,                // Window class
                                   name,                // Window text
                                   WS_OVERLAPPEDWINDOW, // Window style

                                   // Size and position
                                   CW_USEDEFAULT, CW_USEDEFAULT, width, height,

                                   NULL,      // Parent window
                                   NULL,      // Menu
                                   hInstance, // Instance handle
                                   NULL       // Additional application data
    );
    assert(pl_win->hwnd != NULL);
    ShowWindow(pl_win->hwnd, SW_SHOW);
    pl_win->hdc = GetDC(pl_win->hwnd);

    global_bitmap_info.bmiHeader.biSize  = sizeof(BITMAPINFOHEADER);
    global_bitmap_info.bmiHeader.biWidth = width;
    //-- Negative to move coordinates origin in a left-up corner
    global_bitmap_info.bmiHeader.biHeight = -height;
    global_bitmap_info.bmiHeader.biPlanes = 1;
    //-- Specifies the number of bits per pixel
    global_bitmap_info.bmiHeader.biBitCount    = 32;
    global_bitmap_info.bmiHeader.biCompression = BI_RGB;

    res.width  = width;
    res.height = height;
    res.window = (void*)pl_win;

    return res;
}

void process_events(t_window* window, t_scene* scene)
{
    glob_scene                = scene;
    t_platform_window* pl_win = (t_platform_window*)window->window;

    MSG msg = {};
    while (PeekMessageA(&msg, pl_win->hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

void present_buffer_in_window(t_window* window)
{
    t_platform_window* pl_win = (t_platform_window*)window->window;
    StretchDIBits(pl_win->hdc, 0, 0, window->width, window->height, 0, 0, window->width, window->height, window->buffer,
                  &global_bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}

void destroy_window(t_window* window)
{
    t_platform_window* pl_win = (t_platform_window*)window->window;
    ReleaseDC(pl_win->hwnd, pl_win->hdc);
}
