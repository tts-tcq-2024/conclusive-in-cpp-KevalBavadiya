#include <gtest/gtest.h>
#include "typewise-alert.h"

// Test inferBreach function with boundary cases
TEST(TypeWiseAlertTestSuite, InferBreach_LowBoundary) {
    EXPECT_EQ(inferBreach(-1, 0, 35), TOO_LOW);
}

TEST(TypeWiseAlertTestSuite, InferBreach_HighBoundary) {
    EXPECT_EQ(inferBreach(36, 0, 35), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, InferBreach_NormalBoundary) {
    EXPECT_EQ(inferBreach(20, 0, 35), NORMAL);
}

// Test classifyTemperatureBreach function with different cooling types
TEST(TypeWiseAlertTestSuite, ClassifyTemperatureBreach_PassiveCooling) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 10), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW);
}

TEST(TypeWiseAlertTestSuite, ClassifyTemperatureBreach_HiActiveCooling) {
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 30), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1), TOO_LOW);
}

TEST(TypeWiseAlertTestSuite, ClassifyTemperatureBreach_MedActiveCooling) {
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 25), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
}

// Test checkAndAlert with different alert targets
TEST(TypeWiseAlertTestSuite, CheckAndAlert_ToController) {
    BatteryCharacter battery = {PASSIVE_COOLING, "BrandX"};
    checkAndAlert(TO_CONTROLLER, battery, 40);  // Expect output simulating a controller alert
}

TEST(TypeWiseAlertTestSuite, CheckAndAlert_ToEmail) {
    BatteryCharacter battery = {HI_ACTIVE_COOLING, "BrandY"};
    checkAndAlert(TO_EMAIL, battery, 50);  // Expect output simulating an email alert
}
