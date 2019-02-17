/*
    Created: Feb 2019
    Author: Mayur Wadhwani
*/
#include <avr/sleep.h>
#include "Arduino.h"
#include "ArduinoLog.h"

class Voltage
{

  protected:
    int __iPin;
    int __iVccPin;
    int __iReading;

  public:
    Voltage(int iPin, int iVcc)
    {
        this->__iPin = iPin;
        this->__iVccPin = iVcc;
        pinMode(this->__iVccPin, OUTPUT);
        this->__iReading = analogRead(this->__iPin);
        this->TurnOn();
    }
    inline void TakeReading()
    {
        this->__iReading = analogRead(this->__iPin);
    }
    inline int GetReading()
    {
        this->TakeReading();
        return __iReading;
    }
    inline float GetVolts()
    {
        return (this->GetReading() * 5.0 / 1024.0);
    }
    inline float GetMilliVolts()
    {
        return (this->GetVolts() * 1000.0);
    }
    inline void TurnOn()
    {
        digitalWrite(this->__iVccPin,HIGH);
    }
    inline void TurnOff()
    {
        digitalWrite(this->__iVccPin, LOW);
    }
    void PrintReading()
    {
        Log.notice(F("Reading at pin %i = %i" CR), this->__iPin, this->__iReading);
        Log.notice(F("Voltage = %F V" CR), this->GetVolts());
    }
    ~Voltage() = default;
};

class Temperature : public Voltage
{
  public:
    Temperature(int iPin, int iVccPin) : Voltage(iPin, iVccPin)
    {
    }
    inline float GetCelcius()
    {
        return (GetReading() * (5.0 / (1.1 * 10)));
    }
};

class Light : public Voltage
{

  public:
    Light(int iPin, int iVccPin) : Voltage(iPin, iVccPin)
    {
    }
    inline int GetIntensityPercent()
    {
        // Darkness = 0.04V
        // Torch = 4.73V
        return (map(GetVolts(), 4.73, 0.04, 0, 100));
    }
};

class Soil : public Voltage
{

  public:
    Soil(int iPin, int iVccPin) : Voltage(iPin, iVccPin)
    {
    }
    inline int GetMoisturePercent()
    {
        // Dry soil after 7 days of no water minimum = 2V
        // Optimum Soil voltage = 3V
        return (map(GetVolts(), 0, 3, 0, 100));
    }
};

static int BeginAppLogs(void)
{
    init();
    Serial.begin(115200);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
    Log.notice(F("------------- APP STARTED! -------------" CR));
    return 0;
}

void wakeUpNow() // here the interrupt is handled after wakeup
{
}

void sleepNow() // here we put the arduino to sleep
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    attachInterrupt(0, wakeUpNow, LOW);
    sleep_mode();
    sleep_disable();
    detachInterrupt(0);
}

int main()
{
    const int iInterruptPin = 2; // pin used for waking up
    int iTime = 0;
    Temperature cTemperature(0, 8);
    Light cLight(1, 9);
    Soil cSoil(2, 10);

    BeginAppLogs();
    pinMode(iInterruptPin, INPUT);
    attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
    while (true)
    {
        Log.notice(F("Temperature = %F C" CR), cTemperature.GetCelcius());
        Log.notice(F("Light Intensity = %i %%" CR), cLight.GetIntensityPercent());
        Log.notice(F("Soil Moisture = %i %%" CR), cSoil.GetMoisturePercent());
        delay(1000); // wait for a second
        iTime++;
        // One minute
        if (iTime > 2)
        {
            iTime = 0;
            cLight.TurnOff();
            cSoil.TurnOff();
            cTemperature.TurnOff();
            Log.notice(F("Going To Sleep" CR));
            delay(1000);
            sleepNow(); // sleep function called here
            cLight.TurnOn();
            cSoil.TurnOn();
            cTemperature.TurnOn();
        }
    }
}
