#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../includes/figures.h"
#include "../includes/MiniRT.h"
#include "../arena/arena.h"

t_triangle create_triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    t_triangle tri;
    tri.a = new_vector(x1, y1, z1);
    tri.b = new_vector(x2, y2, z2);
    tri.c = new_vector(x3, y3, z3);
    return tri;
}

int count_nodes(t_BVHNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->is_leaf)
    {
        return 1;
    }
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}

int count_leaves(t_BVHNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->is_leaf)
    {
        return 1;
    }
    return count_leaves(node->left) + count_leaves(node->right);
}

int max_depth(t_BVHNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->is_leaf)
    {
        return 1;
    }
    int left_depth  = max_depth(node->left);
    int right_depth = max_depth(node->right);
    return 1 + MAX(left_depth, right_depth);
}

int count_triangles_in_leaves(t_BVHNode* node)
{
    if (node == NULL)
    {
        return 0;
    }
    if (node->is_leaf)
    {
        return node->count;
    }
    return count_triangles_in_leaves(node->left) + count_triangles_in_leaves(node->right);
}

bool validate_aabb_hierarchy(t_BVHNode* node)
{
    if (node == NULL || node->is_leaf)
    {
        return true;
    }

    if (node->left != NULL)
    {
        if (node->left->aabb.min.v_x < node->aabb.min.v_x - 0.001f ||
            node->left->aabb.min.v_y < node->aabb.min.v_y - 0.001f ||
            node->left->aabb.min.v_z < node->aabb.min.v_z - 0.001f ||
            node->left->aabb.max.v_x > node->aabb.max.v_x + 0.001f ||
            node->left->aabb.max.v_y > node->aabb.max.v_y + 0.001f ||
            node->left->aabb.max.v_z > node->aabb.max.v_z + 0.001f)
        {
            return false;
        }
    }

    if (node->right != NULL)
    {
        if (node->right->aabb.min.v_x < node->aabb.min.v_x - 0.001f ||
            node->right->aabb.min.v_y < node->aabb.min.v_y - 0.001f ||
            node->right->aabb.min.v_z < node->aabb.min.v_z - 0.001f ||
            node->right->aabb.max.v_x > node->aabb.max.v_x + 0.001f ||
            node->right->aabb.max.v_y > node->aabb.max.v_y + 0.001f ||
            node->right->aabb.max.v_z > node->aabb.max.v_z + 0.001f)
        {
            return false;
        }
    }

    return validate_aabb_hierarchy(node->left) && validate_aabb_hierarchy(node->right);
}

bool validate_leaf_sizes(t_BVHNode* node, int max_triangles)
{
    if (node == NULL)
    {
        return true;
    }
    if (node->is_leaf)
    {
        return node->count <= max_triangles;
    }
    return validate_leaf_sizes(node->left, max_triangles) && validate_leaf_sizes(node->right, max_triangles);
}

bool test_single_triangle()
{
    printf("TEST 2: Single triangle... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle triangles[1];
    triangles[0] = create_triangle(0, 0, 0, 1, 0, 0, 0, 1, 0);

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 1;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 1, &arena);

    bool passed = (root != NULL && root->is_leaf && root->count == 1);
    printf("%s\n", passed ? "PASSED" : "FAILED");

    destroy_arena(&arena);
    return passed;
}

bool test_four_triangles()
{
    printf("TEST 3: Four triangles (leaf boundary)... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle triangles[4];
    triangles[0] = create_triangle(0, 0, 0, 1, 0, 0, 0, 1, 0);
    triangles[1] = create_triangle(2, 0, 0, 3, 0, 0, 2, 1, 0);
    triangles[2] = create_triangle(4, 0, 0, 5, 0, 0, 4, 1, 0);
    triangles[3] = create_triangle(6, 0, 0, 7, 0, 0, 6, 1, 0);

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 4;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 4, &arena);

    bool passed = (root != NULL && root->is_leaf && root->count == 4);
    printf("%s\n", passed ? "PASSED" : "FAILED");

    destroy_arena(&arena);
    return passed;
}

bool test_five_triangles()
{
    printf("TEST 4: Five triangles (should split)... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle triangles[5];
    for (int i = 0; i < 5; i++)
    {
        triangles[i] = create_triangle(i * 2, 0, 0, i * 2 + 1, 0, 0, i * 2, 1, 0);
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 5;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 5, &arena);

    bool passed = (root != NULL && !root->is_leaf && root->left != NULL && root->right != NULL);
    printf("%s\n", passed ? "PASSED" : "FAILED");

    if (passed)
    {
        printf("  - Left: %d triangles, Right: %d triangles\n", count_triangles_in_leaves(root->left),
               count_triangles_in_leaves(root->right));
    }

    destroy_arena(&arena);
    return passed;
}

bool test_nine_triangles()
{
    printf("TEST 5: Nine triangles (odd split test)... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle triangles[9];
    for (int i = 0; i < 9; i++)
    {
        triangles[i] = create_triangle(i * 2, 0, 0, i * 2 + 1, 0, 0, i * 2, 1, 0);
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 9;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 9, &arena);

    int  total_triangles = count_triangles_in_leaves(root);
    bool passed          = (root != NULL && total_triangles == 9);

    printf("%s\n", passed ? "PASSED" : "FAILED");

    if (!passed)
    {
        printf("  - Expected 9 triangles, got %d\n", total_triangles);
    }

    destroy_arena(&arena);
    return passed;
}

bool test_hundred_triangles()
{
    printf("TEST 6: Hundred triangles... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle* triangles = (t_triangle*)malloc(100 * sizeof(t_triangle));
    for (int i = 0; i < 100; i++)
    {
        triangles[i] = create_triangle(i * 2, 0, 0, i * 2 + 1, 0, 0, i * 2, 1, 0);
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 100;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 100, &arena);

    int  total_triangles = count_triangles_in_leaves(root);
    int  depth           = max_depth(root);
    bool passed          = (root != NULL && total_triangles == 100 && depth > 1);

    printf("%s\n", passed ? "PASSED" : "FAILED");
    printf("  - Depth: %d, Nodes: %d, Leaves: %d\n", depth, count_nodes(root), count_leaves(root));

    free(triangles);
    destroy_arena(&arena);
    return passed;
}

bool test_coincident_triangles()
{
    printf("TEST 7: Coincident triangles... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle triangles[10];
    for (int i = 0; i < 10; i++)
    {
        triangles[i] = create_triangle(0, 0, 0, 0.1f, 0, 0, 0, 0.1f, 0);
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 10;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 10, &arena);

    bool passed = (root != NULL && count_triangles_in_leaves(root) == 10);
    printf("%s\n", passed ? "PASSED" : "FAILED");

    destroy_arena(&arena);
    return passed;
}

bool test_linear_arrangement()
{
    printf("TEST 8: Linear arrangement (along X-axis)... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle triangles[20];
    for (int i = 0; i < 20; i++)
    {
        triangles[i] = create_triangle(i * 10, 0, 0, i * 10 + 1, 0, 0, i * 10, 1, 0);
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 20;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 20, &arena);

    BreakingAxis axis   = findBreakingAxis(root);
    bool         passed = (root != NULL && axis == BreakingAxisX && count_triangles_in_leaves(root) == 20);

    printf("%s\n", passed ? "PASSED" : "FAILED");
    printf("  - Breaking axis: %s\n", axis == BreakingAxisX ? "X" : axis == BreakingAxisY ? "Y" : "Z");

    destroy_arena(&arena);
    return passed;
}

bool test_cubic_distribution()
{
    printf("TEST 9: Cubic distribution (3D grid)... ");

    t_memory_arena arena = create_arena(MB(1));

    int         grid_size = 5;
    int         count     = grid_size * grid_size * grid_size;
    t_triangle* triangles = (t_triangle*)malloc(count * sizeof(t_triangle));

    int idx = 0;
    for (int x = 0; x < grid_size; x++)
    {
        for (int y = 0; y < grid_size; y++)
        {
            for (int z = 0; z < grid_size; z++)
            {
                triangles[idx++] = create_triangle(x, y, z, x + 0.5f, y, z, x, y + 0.5f, z);
            }
        }
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = count;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, count, &arena);

    bool hierarchy_valid = validate_aabb_hierarchy(root);
    bool passed          = (root != NULL && count_triangles_in_leaves(root) == count && hierarchy_valid);

    printf("%s\n", passed ? "PASSED" : "FAILED");
    printf("  - Hierarchy valid: %s\n", hierarchy_valid ? "YES" : "NO");

    free(triangles);
    destroy_arena(&arena);
    return passed;
}

bool test_large_array()
{
    printf("TEST 10: Large array (1000 triangles)... ");

    t_memory_arena arena = create_arena(MB(10));

    int         count     = 1000;
    t_triangle* triangles = (t_triangle*)malloc(count * sizeof(t_triangle));

    for (int i = 0; i < count; i++)
    {
        float x      = (float)(i % 100);
        float y      = (float)((i / 100) % 10);
        float z      = (float)(i / 1000);
        triangles[i] = create_triangle(x, y, z, x + 0.5f, y, z, x, y + 0.5f, z);
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = count;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, count, &arena);

    int  total        = count_triangles_in_leaves(root);
    int  depth        = max_depth(root);
    bool leaves_valid = validate_leaf_sizes(root, 4);
    bool passed       = (root != NULL && total == count && leaves_valid);

    printf("%s\n", passed ? "PASSED" : "FAILED");
    printf("  - Total triangles: %d, Depth: %d, Leaves valid: %s\n", total, depth, leaves_valid ? "YES" : "NO");

    free(triangles);
    destroy_arena(&arena);
    return passed;
}

bool test_aabb_containment()
{
    printf("TEST 11: AABB hierarchy containment... ");

    t_memory_arena arena = create_arena(MB(1));

    t_triangle triangles[30];
    for (int i = 0; i < 30; i++)
    {
        float x      = (float)(i % 10) * 2.0f;
        float y      = (float)(i / 10) * 2.0f;
        triangles[i] = create_triangle(x, y, 0, x + 1, y, 0, x, y + 1, 0);
    }

    t_vec_fig figures;
    figures.triangles = triangles;
    figures.length    = 30;
    assignAABB(&figures);

    t_BVHNode* root = build_BVH_from_triangles(triangles, 30, &arena);

    bool hierarchy_valid = validate_aabb_hierarchy(root);
    bool passed          = (root != NULL && hierarchy_valid);

    printf("%s\n", passed ? "PASSED" : "FAILED");

    if (!passed)
    {
        printf("  - AABB hierarchy validation FAILED!\n");
    }

    destroy_arena(&arena);
    return passed;
}

bool test_power_of_two_sizes()
{
    printf("TEST 12: Power-of-two sizes (8, 16, 32, 64)... ");

    int  sizes[]    = {8, 16, 32, 64};
    bool all_passed = true;

    for (int s = 0; s < 4; s++)
    {
        t_memory_arena arena = create_arena(MB(1));

        int         size      = sizes[s];
        t_triangle* triangles = (t_triangle*)malloc(size * sizeof(t_triangle));

        for (int i = 0; i < size; i++)
        {
            triangles[i] = create_triangle(i, 0, 0, i + 0.5f, 0, 0, i, 0.5f, 0);
        }

        t_vec_fig figures;
        figures.triangles = triangles;
        figures.length    = size;
        assignAABB(&figures);

        t_BVHNode* root = build_BVH_from_triangles(triangles, size, &arena);

        int total = count_triangles_in_leaves(root);
        if (total != size)
        {
            all_passed = false;
            printf("\n  - Size %d FAILED (expected %d, got %d)", size, size, total);
        }

        free(triangles);
        destroy_arena(&arena);
    }

    printf("%s\n", all_passed ? "PASSED" : "FAILED");
    return all_passed;
}

void run_all_bvh_tests()
{
    printf("\n");
    printf("==============================================\n");
    printf("       BVH CONSTRUCTION TEST SUITE\n");
    printf("==============================================\n\n");

    int total_tests  = 11;
    int passed_tests = 0;

    passed_tests += test_single_triangle();
    passed_tests += test_four_triangles();
    passed_tests += test_five_triangles();
    passed_tests += test_nine_triangles();
    passed_tests += test_hundred_triangles();
    passed_tests += test_coincident_triangles();
    passed_tests += test_linear_arrangement();
    passed_tests += test_cubic_distribution();
    passed_tests += test_large_array();
    passed_tests += test_aabb_containment();
    passed_tests += test_power_of_two_sizes();

    printf("\n==============================================\n");
    printf("RESULTS: %d/%d tests passed (%.1f%%)\n", passed_tests, total_tests,
           (float)passed_tests / total_tests * 100.0f);
    printf("==============================================\n\n");
}
