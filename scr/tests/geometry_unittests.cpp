#include <string>

#include "gtest/gtest.h"
#include "../geometryLib/geometry.cpp"

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

//      intersect

TEST(intersect, random_segments_1)
{
    Segment3D segment1(Vector3D(1, 1, 0), Vector3D(3, 3, 0));
    Segment3D segment2(Vector3D(1, 3, 0), Vector3D(3, 1, 0));

    auto res = intersect(segment1, segment2, 1e-5);

    EXPECT_EQ(Vector3D(2, 2, 0),
              intersect(segment1, segment2, 1e-5));
}

TEST(intersect, random_segments_2)
{
    Segment3D segment1(Vector3D(3, 3, 3), Vector3D(-3, -3, -3));
    Segment3D segment2(Vector3D(-3, 3, -3), Vector3D(3, -3, 3));

    EXPECT_EQ(Vector3D(0, 0, 0),
              intersect(segment1, segment2, 1e-5));
}

TEST(intersect, perpendicular_angle)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(1, 0, 0));
    Segment3D segment2(Vector3D(0, 1, 0), Vector3D(0, 0, 0));

    EXPECT_EQ(Vector3D(0, 0, 0),
              intersect(segment1, segment2, 1e-5));
}

TEST(intersect, not_coplanar_vectors)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 0, 0));
    Segment3D segment2(Vector3D(0, 0, 3), Vector3D(0, 1, 3));

    EXPECT_ANY_THROW(intersect(segment1, segment2));
}

TEST(intersect, do_not_intersect)
{
    Segment3D segment1(Vector3D(1, 1, 0), Vector3D(3, 3, 0));
    Segment3D segment2(Vector3D(1.5, 1.5, 1.5), Vector3D(2, 0, 0));

    EXPECT_ANY_THROW(intersect(segment1, segment2));
}

TEST(intersect, point_and_segment_intersect)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(2, 2, 2), Vector3D(2, 2, 2));

    EXPECT_EQ(Vector3D(2, 2, 2),
              intersect(segment1, segment2));
}

TEST(intersect, point_and_point_intersect)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(0, 0, 0));

    EXPECT_EQ(Vector3D(0, 0, 0),
              intersect(segment1, segment1));
}

TEST(intersect, point_and_segment_do_not_intersect)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(3.1, 3.1, 3.1), Vector3D(3.1, 3.1, 3.1));

    EXPECT_ANY_THROW(intersect(segment1, segment2));
}

TEST(intersect, point_and_point_do_not_intersect)
{
    Segment3D segment1(Vector3D(3, 3, 3), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(3.1, 3.1, 3.1), Vector3D(3.1, 3.1, 3.1));

    EXPECT_ANY_THROW(intersect(segment1, segment2));
}

TEST(intersect, paralel_segments)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(0, 0, 3), Vector3D(3, 3, 6));

    EXPECT_ANY_THROW(intersect(segment1, segment2));
}

TEST(intersect, point_on_segment)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(2, 2, 2), Vector3D(2, 2, 2));

    EXPECT_EQ(Vector3D(2, 2, 2), intersect(segment1, segment2));
}

TEST(intersect, continuing)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(3, 3, 3), Vector3D(10, 10, 10));

    EXPECT_EQ(Vector3D(3, 3, 3),
              intersect(segment1, segment2));
}

TEST(intersect, gap)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(3.1, 3.1, 3.1), Vector3D(5, 5, 5));

    EXPECT_ANY_THROW(intersect(segment1, segment2));
}

TEST(intersect, contains)
{
    Segment3D segment1(Vector3D(0, 0, 0), Vector3D(3, 3, 3));
    Segment3D segment2(Vector3D(1, 1, 1), Vector3D(2, 2, 2));

    Vector3D answer = intersect(segment1, segment2);
    EXPECT_EQ((answer == Vector3D(1, 1, 1)) || (answer == Vector3D(2, 2, 2)),
              true);
}

TEST(intersect, revers_arguments)
{
    Segment3D segment1(Vector3D(1, 1, 0), Vector3D(3, 3, 0));
    Segment3D segment2(Vector3D(1, 3, 0), Vector3D(3, 1, 0));

    Vector3D answer1 = intersect(segment1, segment2);
    Vector3D answer2 = intersect(segment2, segment1);

    EXPECT_EQ(answer1 == Vector3D(2, 2, 0),
              answer2 == Vector3D(2, 2, 0));
}