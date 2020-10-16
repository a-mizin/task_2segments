#include <string>

#include "gtest/gtest.h"
#include "../geomlib/geometry.h"

//      compDeterminant3D

TEST(compDeterminant3D, null_vectors)
{
    Vector3D vector(0, 0, 0);

    EXPECT_EQ(0, compDeterminant3D(vector, vector, vector));
}

TEST(compDeterminant3D, linearly_dependent)
{
    Vector3D v1(1, 2, 3);
    Vector3D v2(3, 7, 11);

    EXPECT_EQ(0, compDeterminant3D(v1, v2, v1));
}

TEST(compDeterminant3D, random_vectors)
{
    Vector3D v1(1, 2, 3);
    Vector3D v2(3, 7, 11);
    Vector3D v3(-13, 17, -23);

    EXPECT_EQ(-70, compDeterminant3D(v1, v2, v3));
}

//      solveLinearSystem2D

TEST(solveLinearSystem2D, null_system)
{
    Vector3D vec(0,0,0);

    std::string what("Infinite number of solutions.");

    double  u, v;

    try {
        std::tie(u, v) = solveLinearSystem2D(vec, vec, vec);
    }
    catch (std::exception& exception) {
        EXPECT_EQ(std::strcmp(what.c_str(), exception.what()),0);
    }
}

TEST(solveLinearSystem2D, linearly_dependent_system)
{
    Vector3D vec1(1,2,3);
    Vector3D vec2(2,4,6);
    Vector3D vec3(-1,-1,-1);

    std::string what("Infinite number of solutions.");

    double  u, v;

    try {
        std::tie(u, v) = solveLinearSystem2D(vec1, vec2, vec3);
    }
    catch (std::exception& exception) {
        EXPECT_EQ(std::strcmp(what.c_str(), exception.what()),0);
    }
}

TEST(solveLinearSystem2D, random_system)
{
    Vector3D vec1(1,2,3);
    Vector3D vec2(-3,4,23);
    Vector3D vec3(-1,5,-1);

    EXPECT_EQ(std::make_tuple(1.1, 0.7),
              solveLinearSystem2D(vec1, vec2, vec3));
}

//      intersect

TEST(intersect, random_segments_1)
{
    Segment3D segment1(Vector3D(1, 1, 0), Vector3D(3, 3, 0));
    Segment3D segment2(Vector3D(1, 3, 0), Vector3D(3, 1, 0));

    EXPECT_EQ(Vector3D(2, 2, 0),
              intersect(segment1, segment2));
}

TEST(intersect, random_segments_2)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 1, 0));
    Segment3D segment2(Vector3D(1, 0, 0), Vector3D(0, 0, 0));

    EXPECT_EQ(Vector3D(0, 0, 0),
              intersect(segment1, segment2));
}

TEST(intersect, random_segments_3)
{
    Segment3D segment1(Vector3D(1, 1, 1), Vector3D(2, 2, 2));
    Segment3D segment2(Vector3D(2, 2, 2), Vector3D(3, 3, 3));

    EXPECT_EQ(Vector3D(2, 2, 2),
              intersect(segment1, segment2));
}
