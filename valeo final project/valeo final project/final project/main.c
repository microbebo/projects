

/**
 * main.c
 *
 * Bassem Rushdy, Ahmed Hesham, Ahmed Sami, Mohammed El Nahas
 *
 *
 *
 */
#include "tm4c123gh6pm.h"
void Delay(void)
{
    volatile long int loop;
    for(loop = 0; loop < 200000; loop++);

}
void delay(int n)
{
    volatile long int i,j;
    for(i = 0; i < n; i++)
        for(j = 0 ;j < 3180; j++);
}
/*void Timer0_ISR(void)
{

    static unsigned char state = 0x00;
    //static unsigned char state1 = 0x00;
    //Clear interrupt flag
    TIMER0_ICR_R |= 1 << 0;
    state ^= 0xff;
    GPIO_PORTF_DATA_BITS_R(1 << 1) = state;
    if(GPIO_PORTF_DATA_BITS_R(1 << 0) == 0x00)
    {
        //state1 ^= 0x6f;
        //GPIO_PORTF_DATA_BITS_R((1 << 1) | (1 << 3)) = state1;
       // Portf_ISR();
       // static unsigned char state1 = 0x00;
         //  TIMER0_ICR_R |= 1 << 0;
           //GPIO_PORTF_ICR_R |= (1 << 0);
           //state1 ^= 0x6f;
           GPIO_PORTF_DATA_BITS_R((1 << 1) | (1 << 3)) = 0x6f;
    }
}
/*void Portf_ISR(void)
{

    static unsigned char state = 0x00;
    TIMER0_ICR_R |= 1 << 1;
    GPIO_PORTF_ICR_R |= (1 << 0);
    state ^= 0x6f;
    GPIO_PORTF_DATA_BITS_R((1 << 1) | (1 << 3)) = state;

}*/

int main(void)
{

    int flag=0;
    SYSCTL_RCGCPWM_R |= 2;       /* enable clock to PWM1 */
    SYSCTL_RCGCGPIO_R |= 0x20;   /* enable clock to PORTF */
    SYSCTL_RCC_R &= ~0x00100000; /* no pre-divide for PWM clock */
    // enable timer clock gate
    //SYSCTL_RCGCTIMER_R |= 1 << 0;
    //select 16 bit timer
   // TIMER0_CFG_R = 0x04;
    // set timer mode to periodic mode
   // TIMER0_TAMR_R |= 0x02;
    // set maximum count in the load interval
  //  TIMER0_TAILR_R =32000;
    // set prescaler value
   // TIMER0_TAPR_R = 250;
    // enable timeout interrupt mask
   // TIMER0_IMR_R |= 1 << 0;
    // enable and start timer 0 A
    //TIMER0_CTL_R |=1 << 0;
    // enable timer interrupt at the NIVC
   // NVIC_EN0_R |= 1 << 19;
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
    /*Set interrupt sense of the switch to edge*/
   // GPIO_PORTF_IS_R &= ~(1 << 0);
    /*Set interrupt edge to single edge*/
  //  GPIO_PORTF_IBE_R &= ~(1 << 0);
    /*Set the interrupt event to falling edge*/
  //  GPIO_PORTF_IEV_R &= ~(1 << 0);
    /*unmask the GPIO pin interrupt*/
  //  GPIO_PORTF_IM_R |= (1 << 0);
    /*enable the PORTF interrupt*/
    //NVIC_EN0_R |= (1 << 30);

    while(1)
        {
                    while(GPIO_PORTF_DATA_BITS_R(1 << 0) != 0x00)
                    {

                                        // red color on/off
                                        GPIO_PORTF_DATA_BITS_R(1 << 1) = 0xff;
                                        delay(250);

                                        GPIO_PORTF_DATA_BITS_R(1 << 1) = 0x00;
                                        delay(250);
                                        if(GPIO_PORTF_DATA_BITS_R(1 << 0) == 0x00)
                                            flag = 1;
                                        if (flag == 1)
                                            break;
                    }

                    //Check if Sw1 is pressed
                    if(GPIO_PORTF_DATA_BITS_R(1 << 0) == 0x00)
                       {
                        int i,y;
                        flag=1;

                        for(i=0;i<10;i++)
                        {
                        //yellow color on/off
                        GPIO_PORTF_DATA_BITS_R((1 << 1) | (1 << 3)) = 0x6f;
                        delay(250);
                        GPIO_PORTF_DATA_BITS_R((1 << 1) | (1 << 3)) = 0x00;
                        delay(250);

                        }
                        for (y=0;y<30;y++)
                        {
                            //green color on/off
                            GPIO_PORTF_DATA_BITS_R(1 << 3) = 0xff;
                            delay(250);
                            GPIO_PORTF_DATA_BITS_R(1 << 3) = 0x00;
                            delay(250);
                        }

                       }






        }

        return 0;
    }





