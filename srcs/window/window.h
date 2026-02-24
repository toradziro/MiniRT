#pragma once

#include "../string/rt_string.h"
#include "../includes/scene.h"

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
    NONE
} t_key;

int      press_key(t_key key, t_scene* scene);
t_window create_window(const char* name, i32 width, i32 height, t_memory_arena* arena);
void     process_events(t_window* window, t_scene* scene);
void     present_buffer_in_window(t_window* window);
void     destroy_window(t_window* window);
