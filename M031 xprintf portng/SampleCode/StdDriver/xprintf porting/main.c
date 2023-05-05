/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Show how to set GPIO pin mode and use pin data input/output control.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"
#include "xprintf.h"




int xprintf_out(int ch)
{
uint8_t c=ch;
 while(UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);
    UART0->DAT = c;
return ch;
}





int xprintf_in(void)
{
    while(1)
    {
        if((DEBUG_PORT->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk) == 0)
        {
            return (DEBUG_PORT->DAT);
        }
    }
}
void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HIRC */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Waiting for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Switch HCLK clock source to HIRC */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Switch UART0 clock source to HIRC */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*----------------------------------------------------------------------*/
    /* Init I/O Multi-function                                              */
    /*----------------------------------------------------------------------*/
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk)) |
                    (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

/*----------------------------------------------------------------------*/
/* Init UART0                                                           */
/*----------------------------------------------------------------------*/
void UART0_Init(void)
{
    /* Reset UART0 */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{

    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();
xdev_out(xprintf_out);
//xdev_in(xprintf_in);
	#if 1  ////total 2432 byte
		xprintf("%d\n", 1234);             /* "1234" */	
    xprintf("%6d,%3d%%\n", -200, 5);   /* "  -200,  5%" */
    xprintf("%-6u\n", 100);            /* "100   " */
    xprintf("%ld\n", 12345678);        /* "12345678" */
    xprintf("%llu\n", 0x100000000);    /* "4294967296"   <XF_USE_LLI> */
    xprintf("%lld\n", -1LL);           /* "-1"           <XF_USE_LLI> */
    xprintf("%04x\n", 0xA3);           /* "00a3" */
    xprintf("%08lX\n", 0x123ABC);      /* "00123ABC" */
    xprintf("%016b\n", 0x550F);        /* "0101010100001111" */
    xprintf("%*d\n", 6, 100);          /* "   100" */
    xprintf("%s\n", "abcdefg");        /* "abcdefg" */
    xprintf("%5s\n", "abc");           /* "  abc" */
    xprintf("%-5s\n", "abc");          /* "abc  " */
    xprintf("%.5s\n", "abcdefg");      /* "abcde" */
    xprintf("%-5.2s\n", "abcdefg");    /* "ab   " */
    xprintf("%c\n", 'a');              /* "a" */
    xprintf("%12f\n", 10.0);           /* "   10.000000" <XF_USE_FP> */
		xprintf("%.4E\n", 123.45678);      /* "1.2346E+02"   <XF_USE_FP> */
		#endif 
		#if 0  //total 5480 byte
		printf("%d\n", 1234);          
		printf("%6d,%3d%%\n", -200, 5);
		printf("%-6u\n", 100);         
		printf("%ld\n", 12345678);     
		printf("%llu\n", 0x100000000); 
		printf("%lld\n", -1LL);        
		printf("%04x\n", 0xA3);        
		printf("%08lX\n", 0x123ABC);   
		printf("%016b\n", 0x550F);     
		printf("%*d\n", 6, 100);       
		printf("%s\n", "abcdefg");     
		printf("%5s\n", "abc");        
		printf("%-5s\n", "abc");       
		printf("%.5s\n", "abcdefg");   
		printf("%-5.2s\n", "abcdefg"); 
		printf("%c\n", 'a');           
		printf("%12f\n", 10.0);        
		printf("%.4E\n", 123.45678);   
		#endif
		while(1);
		
#if 0
char buffer[64];
long a;
long b;
char* p;

while(1)
{
xprintf("please input a int:\n");
xgets(buffer,sizeof(buffer));
p = buffer;
xatoi(&p,&a);
xprintf("please input a int:\n");
xgets(buffer,sizeof(buffer));
p = buffer;
xatoi(&p,&b);
xprintf("%d+%d=%d\n",a,b,a+b);
}
  #endif
}
