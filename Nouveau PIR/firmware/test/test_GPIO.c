#include "stdbool.h"
#include <wiringPi.h>
#include <stdio.h>

bool CRK_signal = false;

// *****************************************************************************
// ************ Configuration and testing of Output_CRK_no_failure *************
// *****************************************************************************

void GPIOs_config(void)
{
    pinMode(6, OUTPUT);
}

//## Output_CRK no Failure Function
/**
 * @brief This function outputs the CRK signal in its normal state (no failure).
 * This simply consists in reproducing the CRK signal as is.
 *
 */
void Output_CRK_no_failure(void)
{
    if (CRK_signal == true)
    {
        digitalWrite(6, HIGH);
        printf("CRK signal is ON\n");
    }
    else
    {
        digitalWrite(6, LOW);
        printf("CRK signal is ON\n");
    }
}

void test_Output_CRK_no_failure()
{
    GPIOs_config();
    Output_CRK_no_failure();
    delay(1000);
    CRK_signal = true;
    Output_CRK_no_failure();
}

int main(void)
{
    wiringPiSetup();

    printf("Testing Output_CRK_no_failure\n");
    test_Output_CRK_no_failure();
    return 0;
}
