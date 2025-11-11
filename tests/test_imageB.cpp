#include <gtest/gtest.h>
#include <vector>
#include "../src/imageB.h"

// Вспомогательная функция для создания изображения из плоского массива
static Image makeImage(int width, int height, const std::vector<int>& data)
{
    Image img;
    img.width = width;
    img.height = height;
    img.pixels.assign(height, std::vector<int>(width));
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            img.pixels[y][x] = data[y * width + x];
        }
    }
    return img;
}

TEST(ImageB_RotateClockwise, Rotates2x3Correctly)
{
    // 2x3 (width=3, height=2)
    // [ 1 2 3 ]
    // [ 4 5 6 ]
    Image img = makeImage(3, 2, {
        1, 2, 3,
        4, 5, 6
    });

    rotateClockwise(img);

    // Ожидаемый результат: 3x2
    // [ 4 1 ]
    // [ 5 2 ]
    // [ 6 3 ]
    ASSERT_EQ(img.width, 2);
    ASSERT_EQ(img.height, 3);
    std::vector<std::vector<int>> expected = {
        {4, 1},
        {5, 2},
        {6, 3}
    };
    EXPECT_EQ(img.pixels, expected);
}

TEST(ImageB_RotateCounterClockwise, Rotates2x3Correctly)
{
    // 2x3 (width=3, height=2)
    // [ 1 2 3 ]
    // [ 4 5 6 ]
    Image img = makeImage(3, 2, {
        1, 2, 3,
        4, 5, 6
    });

    rotateCounterClockwise(img);

    // Ожидаемый результат: 3x2
    // [ 3 6 ]
    // [ 2 5 ]
    // [ 1 4 ]
    ASSERT_EQ(img.width, 2);
    ASSERT_EQ(img.height, 3);
    std::vector<std::vector<int>> expected = {
        {3, 6},
        {2, 5},
        {1, 4}
    };
    EXPECT_EQ(img.pixels, expected);
}

TEST(ImageB_GaussianFilter, Smooths3x3Center)
{
    // Простое 3x3 изображение, центр должен быть сглажен к среднему
    // [ 10 20 30 ]
    // [ 40 50 60 ]
    // [ 70 80 90 ]
    Image img = makeImage(3, 3, {
        10, 20, 30,
        40, 50, 60,
        70, 80, 90
    });

    applyGaussianFilter(img);

    // Рассчитываем ожидаемое значение центра вручную с ядром из imageB.cpp (сумма весов = 80)
    // sum = 5*10 + 10*20 + 5*30 + 10*40 + 20*50 + 10*60 + 5*70 + 10*80 + 5*90
    //     = 50 + 200 + 150 + 400 + 1000 + 600 + 350 + 800 + 450 = 4000
    // center = round(4000 / 80) = 50
    ASSERT_EQ(img.pixels[1][1], 50);

    // Краевые элементы не проверяем строго, но убеждаемся, что они в допустимом диапазоне
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < img.width; ++x)
        {
            EXPECT_GE(img.pixels[y][x], 0);
            EXPECT_LE(img.pixels[y][x], 255);
        }
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
