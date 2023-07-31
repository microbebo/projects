

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
    int x = 15999;
    SYSCTL_RCGCPWM_R |= 2;       /* enable clock to PWM1 */
    SYSCTL_RCGCGPIO_R |= 0x20;   /* enable clock to PORTF */
    SYSCTL_RCC_R &= ~0x00100000; /* no pre-divide for PWM clock */

    /*Enable for PORTF Clock gate*/
    SYSCTL_RCGCGPIO_R |= 1 << 5;
    /*Unlock PortF0*/
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 1 << 0;
    /*Set the Led Direction pin to output*/
    GPIO_PORTF_DIR_R |= 1 << 1;
    GPIO_PORTF_DIR_R |= 1 << 2;
    GPIO_PORTF_DIR_R |= 1 << 3;
    /*Set the switches direction to input*/
    GPIO_PORTF_DIR_R &= ~((1 << 0) | (1 << 4));
    /*Set Led Pin mode to GPIO*/
    GPIO_PORTF_AFSEL_R &= ~(1 << 1);
    GPIO_PORTF_AFSEL_R &= ~(1 << 2);
    GPIO_PORTF_AFSEL_R &= ~(1 << 3);
    /*set switches mode to GPTIO*/
    GPIO_PORTF_AFSEL_R &= ~((1 << 0) | (1 << 4));
    /*Set maximum output current for the LED pin to 2 mA*/
    GPIO_PORTF_DR2R_R |= 1 << 1;
    GPIO_PORTF_DR2R_R |= 1 << 2;
    GPIO_PORTF_DR2R_R |= 1 << 3;
    /*Enable to the Pull down resistor of the LED pin*/
    GPIO_PORTF_PDR_R |= 1 << 1;
    GPIO_PORTF_PDR_R |= 1 << 2;
    GPIO_PORTF_PDR_R |= 1 << 3;
    /*Enable pull up resistor for the Switches pin*/
    GPIO_PORTF_PUR_R |= (1 << 0) | (1 << 4);
    /*Enable the Digital functionality of the LED pin*/
    GPIO_PORTF_DEN_R |= 1 << 1;
    GPIO_PORTF_DEN_R |= 1 << 2;
    GPIO_PORTF_DEN_R |= 1 << 3;
    /*Enable the digital functionality of Switches*/
    GPIO_PORTF_DEN_R |= (1 << 0) | (1 << 4);

    while(1)
    {
        /*Check if Sw1 is pressed*/
        if(GPIO_PORTF_DATA_BITS_R(1 << 0) == 0x00)
        {
            while(1)
                {
                    GPIO_PORTF_DATA_BITS_R(1 << 1) = 0xFF,0x00,0x00;
                    Delay();

                    GPIO_PORTF_DATA_BITS_R(1 << 1) = 0x00;
                    Delay();
                    /*Turn on LED*/
                    GPIO_PORTF_DATA_BITS_R(1 << 2) = 0xff;
                    Delay();
                    /*Turn off LED*/
                    GPIO_PORTF_DATA_BITS_R(1 << 2) = 0x00;
                    Delay();
                    GPIO_PORTF_DATA_BITS_R(1 << 3) = 0xFF,0x00,0x00;
                    Delay();
                    /*Turn off LED*/
                    GPIO_PORTF_DATA_BITS_R(1 << 3) = 0x00;
                    Delay();

                }

        }
        /*Check if Sw2 is pressed*/
        if(GPIO_PORTF_DATA_BITS_R(1 << 4) == 0x00)
        {
            /*Turn off LED*/
            //GPIO_PORTF_DATA_BITS_R(1 << 1) = 0x00;
            GPIO_PORTF_DATA_BITS_R(1 << 2) = 0xff;
            GPIO_PORTF_AFSEL_R = 8;      /* PF3 uses alternate function */
                GPIO_PORTF_PCTL_R &= ~0x0000F000; /* make PF3 PWM output pin */
                GPIO_PORTF_PCTL_R |= 0x00005000;
                GPIO_PORTF_DEN_R |= 8;       /* pin digital */

                PWM1_3_CTL_R = 0;            /* stop counter */
                PWM1_3_GENB_R = 0x0000008C;  /* M1PWM7 output set when reload, */
                                             /* clear when match PWMCMPA */
                PWM1_3_LOAD_R = 16000;       /* set load value for 1kHz (16MHz/16000) */
                PWM1_3_CMPA_R = 15999;       /* set duty cycle to min */
                PWM1_3_CTL_R = 1;            /* start timer */
                PWM1_ENABLE_R = 0x80;        /* start PWM1 ch7 */

                for(;;) {
                    x = x - 100;

                    if (x <= 0)
                        x = 16000;

                    PWM1_3_CMPA_R = x;

                    Delay();
                }
        }
    }

    return 0;
}
