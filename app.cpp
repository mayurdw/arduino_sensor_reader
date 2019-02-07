/*
    Created: Feb 2019
    Author: Mayur Wadhwani
*/

#include "Arduino.h"
#include "ArduinoLog.h"

class Voltage
{
  protected:
    int __iPin;
    int __iReading;

  public:
    Voltage(int iPin)
    {
        this->__iPin = iPin;
        this->__iReading = analogRead(this->__iPin);
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
    Temperature(int iPin) : Voltage(iPin)
    {
    }
    inline float GetCelcius()
    {
        TakeReading();
        PrintReading();
        return ( GetReading() * ( 5.0 / ( 1.1 * 10 ) ) );
    }
};

static const int s_iVccPin = 7;

static int BeginAppLogs(void)
{
    init();
    pinMode(s_iVccPin, OUTPUT);
    Serial.begin(115200);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
    Log.notice(F("------------- HELLO WORLD! -------------" CR));
    return 0;
}

// Darkness = 0.04V
// Torch = 4.73V
int main()
{
    Temperature cSensor1(0);
    Voltage cLight(1), cSoil(2);

    BeginAppLogs();
    digitalWrite(s_iVccPin, HIGH);

    while (true)
    {
        Log.notice(F("Temperature = %F C" CR), (cSensor1.GetCelcius()));
        Log.notice(F("Light Intensity = %i %%" CR), map(cLight.GetVolts(), 0.04, 4.73, 0, 100) );
        Log.notice(F("Soil Moisture = %i %%" CR), map(cSoil.GetReading(), 0, 1023, 0, 100) );
        delay(1000); // wait for a second
    }
}
