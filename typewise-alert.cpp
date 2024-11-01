#include "typewise-alert.h"
#include <stdio.h>

// Define a structure for cooling type limits
static const TemperatureLimits temperatureLimits[] = {
    {0, 35}, // PASSIVE_COOLING
    {0, 45}, // HI_ACTIVE_COOLING
    {0, 40}  // MED_ACTIVE_COOLING
};

TemperatureLimits getTemperatureLimits(CoolingType coolingType) {
    // Ensure the coolingType is within bounds
    if (coolingType < 0 || coolingType >= sizeof(temperatureLimits) / sizeof(temperatureLimits[0])) {
        return {0, 0};  // Default case, should not occur
    }
    return temperatureLimits[coolingType];
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    TemperatureLimits limits = getTemperatureLimits(coolingType);
    return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

    if (alertTarget == TO_CONTROLLER) {
        sendToController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        sendToEmail(breachType);
    }
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recepient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too low\n");
    } else if (breachType == TOO_HIGH) {
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too high\n");
    }
}
