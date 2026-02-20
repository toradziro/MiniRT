#pragma once

#include "../lists_funcs/array.h"
#include "../includes/figures.h"
#include "aabb.h"

typedef struct s_BVHNode
{
    union
    {
        struct
        {
            struct s_BVHNode* left;
            struct s_BVHNode* right;
        };
        struct
        {
            int         count;
            t_triangle* batch;
        };
    };
    t_AABB aabb;
    bool   is_leaf;
} t_BVHNode;

typedef struct s_BVH
{
    t_BVHNode*  root;
    t_triangle* triangles;
    int         triangle_count;
} t_BVH;

typedef enum
{
    BreakingAxisX,
    BreakingAxisY,
    BreakingAxisZ,
    None
} BreakingAxis;

void         assignAABB(t_vec_fig* figures);
t_AABB       findNodeAABB(t_triangle* triangles, int count);
BreakingAxis findBreakingAxis(t_BVHNode* node);
int          compareTriangles(const void* a, const void* b);
void         sortByAxis(BreakingAxis baxis, t_triangle* triangles, int count);
t_BVHNode*   build_BVH_from_triangles(t_triangle* triangles, int count, t_memory_arena* arena);
t_BVH        buildBVH(t_triangle* triangles, int count, t_memory_arena* arena);
