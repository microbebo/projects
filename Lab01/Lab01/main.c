

/**
 * main.c
 */
#include "tm4c123gh6pm.h"
void Delay(void)
{
    volatile long int loop;
    for(loop = 0; loop < 200000; loop++);

}
int main(void)
{
    /*Enable for PORTF Clock gate*/
    SYSCTL_RCGCGPIO_R |= 1 << 5;
    /*Set the Led Direction pin to output*/
    GPIO_PORTF_DIR_R |= 1 << 2;
    /*Set Led Pin mode to GPIO*/
    GPIO_PORTF_AFSEL_R &= ~(1 << 2);
    /*Set maximum output current for the LED pin to 2 mA*/
    GPIO_PORTF_DR2R_R |= 1 << 2;
    /*Enable to the Pull down resistor of the LED pin*/
    GPIO_PORTF_PDR_R |= 1 << 2;
    /*Enable the Digital functionality of the LED pin*/
    GPIO_PORTF_DEN_R |= 1 << 2;

    while(1)
    {
        /*Turn on LED*/
        GPIO_PORTF_DATA_BITS_R(1 << 2) = 0xff;
        Delay();
        /*Turn off LED*/
        GPIO_PORTF_DATA_BITS_R(1 << 2) = 0x00;
        Delay();

    }

	return 0;
}
