#include "typewise-alert.h"
#include <stdio.h>

TemperatureLimits getTemperatureLimits(CoolingType coolingType) {
  switch(coolingType) {
    case PASSIVE_COOLING: return {0, 35};
    case HI_ACTIVE_COOLING: return {0, 45};
    case MED_ACTIVE_COOLING: return {0, 40};
  }
  return {0, 0};  // Default case, should not occur
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
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
