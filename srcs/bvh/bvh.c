#include "bvh.h"
#include <assert.h>
#include "../includes/MiniRT.h"

static BreakingAxis g_breaking_strategy;

void assignAABB(t_vec_fig* figures)
{
    const float C_EPSILON = 0.0001f;

    for (int i = 0; i < figures->length; ++i)
    {
        float max_x = MAX(MAX(figures->triangles[i].a.v_x, figures->triangles[i].b.v_x), figures->triangles[i].c.v_x);
        float max_y = MAX(MAX(figures->triangles[i].a.v_y, figures->triangles[i].b.v_y), figures->triangles[i].c.v_y);
        float max_z = MAX(MAX(figures->triangles[i].a.v_z, figures->triangles[i].b.v_z), figures->triangles[i].c.v_z);

        float min_x = MIN(MIN(figures->triangles[i].a.v_x, figures->triangles[i].b.v_x), figures->triangles[i].c.v_x);
        float min_y = MIN(MIN(figures->triangles[i].a.v_y, figures->triangles[i].b.v_y), figures->triangles[i].c.v_y);
        float min_z = MIN(MIN(figures->triangles[i].a.v_z, figures->triangles[i].b.v_z), figures->triangles[i].c.v_z);

        if (max_x - min_x < C_EPSILON)
        {
            min_x -= C_EPSILON;
            max_x += C_EPSILON;
        }
        if (max_y - min_y < C_EPSILON)
        {
            min_y -= C_EPSILON;
            max_y += C_EPSILON;
        }
        if (max_z - min_z < C_EPSILON)
        {
            min_z -= C_EPSILON;
            max_z += C_EPSILON;
        }

        figures->triangles[i].aabb.min = new_vector(min_x, min_y, min_z);
        figures->triangles[i].aabb.max = new_vector(max_x, max_y, max_z);
    }
}

t_AABB findNodeAABB(t_triangle* triangles, int count)
{
    t_AABB aabb;

    float max_x = -FLT_MAX;
    float max_y = -FLT_MAX;
    float max_z = -FLT_MAX;

    float min_x = FLT_MAX;
    float min_y = FLT_MAX;
    float min_z = FLT_MAX;

    for (int i = 0; i < count; ++i)
    {
        max_x = MAX(max_x, triangles[i].aabb.max.v_x);
        max_y = MAX(max_y, triangles[i].aabb.max.v_y);
        max_z = MAX(max_z, triangles[i].aabb.max.v_z);

        min_x = MIN(min_x, triangles[i].aabb.min.v_x);
        min_y = MIN(min_y, triangles[i].aabb.min.v_y);
        min_z = MIN(min_z, triangles[i].aabb.min.v_z);
    }

    aabb.min = new_vector(min_x, min_y, min_z);
    aabb.max = new_vector(max_x, max_y, max_z);

    return aabb;
}

BreakingAxis findBreakingAxis(t_BVHNode* node)
{
    float        axisXLength = node->aabb.max.v_x - node->aabb.min.v_x;
    float        axisYLength = node->aabb.max.v_y - node->aabb.min.v_y;
    float        axisZLength = node->aabb.max.v_z - node->aabb.min.v_z;
    BreakingAxis baxis       = None;
    if (axisXLength >= axisYLength && axisXLength >= axisZLength)
    {
        baxis = BreakingAxisX;
    }
    else if (axisYLength >= axisZLength && axisYLength >= axisXLength)
    {
        baxis = BreakingAxisY;
    }
    else
    {
        baxis = BreakingAxisZ;
    }
    return baxis;
}

int compareTriangles(const void* a, const void* b)
{
    t_triangle* atr                  = (t_triangle*)a;
    t_triangle* btr                  = (t_triangle*)b;
    float       comparing_centroid_a = 0.0f;
    float       comparing_centroid_b = 0.0f;
    switch (g_breaking_strategy)
    {
    case (BreakingAxisX):
        comparing_centroid_a = (atr->aabb.max.v_x + atr->aabb.min.v_x) * 0.5f;
        comparing_centroid_b = (btr->aabb.max.v_x + btr->aabb.min.v_x) * 0.5f;
        break;
    case (BreakingAxisY):
        comparing_centroid_a = (atr->aabb.max.v_y + atr->aabb.min.v_y) * 0.5f;
        comparing_centroid_b = (btr->aabb.max.v_y + btr->aabb.min.v_y) * 0.5f;
        break;
    case (BreakingAxisZ):
        comparing_centroid_a = (atr->aabb.max.v_z + atr->aabb.min.v_z) * 0.5f;
        comparing_centroid_b = (btr->aabb.max.v_z + btr->aabb.min.v_z) * 0.5f;
        break;
    default:
        assert(false);
        break;
    }
    if (comparing_centroid_a < comparing_centroid_b)
    {
        return -1;
    }
    else if (comparing_centroid_a > comparing_centroid_b)
    {
        return 1;
    }
    return 0;
}

void sortByAxis(BreakingAxis baxis, t_triangle* triangles, int count)
{
    g_breaking_strategy = baxis;
    qsort(triangles, count, sizeof(t_triangle), compareTriangles);
    g_breaking_strategy = None;
}

t_BVHNode* build_BVH_from_triangles(t_triangle* triangles, int count, t_memory_arena* arena)
{
    t_BVHNode* node = (t_BVHNode*)arena_push(arena, sizeof(t_BVHNode));
    node->left      = NULL;
    node->right     = NULL;
    node->is_leaf   = false;
    node->aabb      = findNodeAABB(triangles, count);

    if (count <= 4)
    {
        node->is_leaf = true;
        node->batch   = triangles;
        node->count   = count;
        return node;
    }

    BreakingAxis baxis = findBreakingAxis(node);
    sortByAxis(baxis, triangles, count);
    int newCount = count / 2;
    node->left   = build_BVH_from_triangles(triangles, newCount, arena);
    node->right  = build_BVH_from_triangles(triangles + newCount, count - newCount, arena);

    return node;
}

t_BVH buildBVH(t_triangle* triangles, int count, t_memory_arena* arena)
{
    t_BVH bvh;
    bvh.triangles      = triangles;
    bvh.triangle_count = count;
    bvh.root           = build_BVH_from_triangles(bvh.triangles, bvh.triangle_count, arena);
    return bvh;
}
