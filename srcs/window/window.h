#pragma once

#include "../application/application.h"
#include "../string/rt_string.h"

typedef struct s_window
{
    void* window;
    void* buffer;
    i32   width;
    i32   height;
} t_window;

typedef enum
{
    RT_SCANCODE_TAB,
    RT_SCANCODE_W,
    RT_SCANCODE_S,
    RT_SCANCODE_A,
    RT_SCANCODE_D,
    RT_SCANCODE_E,
    RT_SCANCODE_Q,
    RT_SCANCODE_ARROW_UP,
    RT_SCANCODE_ARROW_DOWN,
    RT_SCANCODE_ARROW_LEFT,
    RT_SCANCODE_ARROW_RIGHT,
    RT_SCANCODE_ESCAPE,
    RT_SCANCODE_ENTER,
    NONE
} t_key;

int      press_key(t_key key, t_application* application);
t_window create_window(const char* name, i32 width, i32 height, t_memory_arena* arena);
void     process_events(t_window* window, t_application* application);
void     present_buffer_in_window(t_window* window);
void     destroy_window(t_window* window);
