#pragma once

#include "../color/color.h"
#include "../lists_funcs/lists.h"
#include "../lists_funcs/array.h"
#include "../bvh/bvh.h"
#include "../vectors_funcs/matrix.h"
#include "../application/thread_pool.h"
#include "figures.h"
#include "my_types.h"

typedef struct s_accum_data
{
    t_color med_color;
    u64     count;
} t_accum_data;

typedef struct s_scene
{
    t_cam_to_w    mtrx;
    t_BVH         bvh;
    t_thread_pool thread_pool;
    t_memory_arena scene_arena;
    t_cameras*    cams;
    t_cameras*    first_cam;
    t_vec_fig*    figures;
    t_lights*     lights;
    t_ab_light*   ab_light;
    void*         pixels;
    t_accum_data* pixels_avg;
    float         projection_coeff;
    float         roughness_val;
    float         dt;
    int           is_save;
    int           width;
    int           height;
    int           mouse_x;
    int           mouse_y;
    bool          is_running;
    bool          roughness_and_multisample;
    bool          need_update_mtx;
} t_scene;
