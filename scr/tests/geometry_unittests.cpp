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

