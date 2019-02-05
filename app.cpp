/*
    Created: Feb 2019
    Author: Mayur Wadhwani
*/

#include "voltage.h"

int main()
{
    Voltage V;

    init();
    pinMode(13, OUTPUT);

    while (true)
    {
        digitalWrite(13, HIGH); // set the LED on
        delay(1000);            // wait for a second
        digitalWrite(13, LOW);  // set the LED off
        delay(1000);            // wait for a second
    }
}