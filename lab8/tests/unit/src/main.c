#include <zephyr/ztest.h>

#define TEMP_HIGH_THRESHOLD 28.0f
#define TEMP_LOW_THRESHOLD 22.0f

static const char *check_temperature(float temp)
{
    if (temp > TEMP_HIGH_THRESHOLD) 
    {
        return "HIGH";
    }
    else if (temp < TEMP_LOW_THRESHOLD)
    {
        return "LOW";
    }
    return "NORMAL";
}

ZTEST_SUITE(skywatch_temp, NULL, NULL, NULL, NULL, NULL);
ZTEST(skywatch_temp, test_normal_temperature)
{
    zassert_str_equal(check_temperature(25.0f), "NORMAL", "25 C should be normal");
}

ZTEST(skywatch_temp, test_high_temperature)
{
    zassert_str_equal(check_temperature(30.0f), "HIGH", "30 C should be HIGH alert");
}
ZTEST(skywatch_temp, test_low_temperature)
{
    zassert_str_equal(check_temperature(20.0f), "LOW", "20 C should be LOW alert");
}

ZTEST(skywatch_temp, test_boundary_high)
{
    zassert_str_equal(check_temperature(28.0f), "NORMAL", "Exactly 28 C should be normal (not > threshold)");
}

ZTEST(skywatch_temp, test_boundary_low)
{
    zassert_str_equal(check_temperature(22.0f), "NORMAL", "Exactly 22 C should be normal (not < threshold)");
}
ZTEST(skywatch_temp, test_just_above_high)
{
    zassert_str_equal(check_temperature(28.1f), "HIGH", "28.1 C should trigger HIGH");
}

ZTEST(skywatch_temp, test_just_below_low)
{
    zassert_str_equal(check_temperature(21.9f), "LOW", "21.9 C should trigger LOW");
}