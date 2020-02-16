#include <avr/io.h>
#include <util/delay.h>
#include <time.h>
#include <assert.h>
enum RegisterD
{
    digital_0_RX = 0b00000001,
    digital_1_TX = 0b00000010,
    digital_2 = 0b00000100,
    digital_3 = 0b00001000,
    digital_4 = 0b00010000,
    digital_5 = 0b00100000,
    digital_6 = 0b01000000,
    digital_7 = 0b10000000
} registerD;

enum RegisterB
{
    digital_8 = 0b00000001,
    digital_9 = 0b00000010,
    digital_10 = 0b00000100,
    digital_11 = 0b00001000,
    digital_12 = 0b00010000,
    digital_13 = 0b00100000
} registerB;

void setPinDDRxForHours(unsigned hour)
{
    DDRD = hour << 2 & (digital_2 | digital_3 | digital_4 | digital_5);
    PORTD = hour << 2 & (digital_2 | digital_3 | digital_4 | digital_5);
}

void setPinDDRxForMinuts(unsigned minute)
{
    DDRB = minute & (digital_8 | digital_9 | digital_10 | digital_11 | digital_12 | digital_13);
    PORTB = minute & (digital_8 | digital_9 | digital_10 | digital_11 | digital_12 | digital_13);
}

static unsigned hours = 0;
static unsigned minuts = 0;
unsigned getHour()
{
    if (minuts == 59)
        hours++;
    if (hours >= 24)
        hours = 0;
    return hours;
}

unsigned getMinut()
{
    _delay_ms(60000);
    minuts++;
    if (minuts == 60)
        minuts = 0;
    return minuts;
}

unsigned To12hTime(unsigned hour)
{
    return hour % 12;
}

void after12pm()
{
    if (getHour() % 24 > 12)
    {
        DDRB &= ~digital_6;
        PORTB &= ~digital_6;
    }
    else
    {
        DDRB |= digital_6;
        PORTB |= digital_6;
    }
}

int main(void)
{
    while (1)
    {
        after12pm();
        setPinDDRxForHours(To12hTime(getHour()));
        setPinDDRxForMinuts(getMinut());
    }

    return 0;
}