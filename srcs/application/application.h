#pragma once

#include "../string/rt_string.h"
#include "../includes/my_types.h"
#include "../includes/scene.h"

typedef enum
{
    Menu,
    Scene
} ApplicationState;

typedef struct s_menu_items_list
{
    str8                      filename;
    str8                      full_path;
    struct s_menu_items_list* next;
} t_menu_items_list;

typedef struct
{
    t_menu_items_list* items;
    void*              menu_background;
    i32                selected_item;
} t_menu_state;

typedef struct
{
    t_scene          curr_scene;
    t_menu_state     menu_state;
    ApplicationState curr_app_state;
    bool             is_running;
    bool             scene_loading_triggered;
    bool             switch_to_menu_triggered;
} t_application;
