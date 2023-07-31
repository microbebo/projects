

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
    /*Unlock PortF0*/
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 1 << 0;
    /*Set the Led Direction pin to output*/
    GPIO_PORTF_DIR_R |= 1 << 2;
    /*Set the switches direction to input*/
    GPIO_PORTF_DIR_R &= ~((1 << 0) | (1 << 4));
    /*Set Led Pin mode to GPIO*/
    GPIO_PORTF_AFSEL_R &= ~(1 << 2);
    /*set switches mode to GPTIO*/
    GPIO_PORTF_AFSEL_R &= ~((1 << 0) | (1 << 4));
    /*Set maximum output current for the LED pin to 2 mA*/
    GPIO_PORTF_DR2R_R |= 1 << 2;
    /*Enable to the Pull down resistor of the LED pin*/
    GPIO_PORTF_PDR_R |= 1 << 2;
    /*Enable pull up resistor for the Switches pin*/
    GPIO_PORTF_PUR_R |= (1 << 0) | (1 << 4);
    /*Enable the Digital functionality of the LED pin*/
    GPIO_PORTF_DEN_R |= 1 << 2;
    /*Enable the digital functionality of Switches*/
    GPIO_PORTF_DEN_R |= (1 << 0) | (1 << 4);

    while(1)
    {
        /*Check if Sw1 is pressed*/
        if(GPIO_PORTF_DATA_BITS_R(1 << 0) == 0x00)
        {
            /*Turn on LED*/
            GPIO_PORTF_DATA_BITS_R(1 << 2) = 0xff;
        }
        /*Check if Sw2 is pressed*/
        if(GPIO_PORTF_DATA_BITS_R(1 << 4) == 0x00)
        {
            /*Turn off LED*/
            GPIO_PORTF_DATA_BITS_R(1 << 2) = 0x00;
        }
    }

    return 0;
}
