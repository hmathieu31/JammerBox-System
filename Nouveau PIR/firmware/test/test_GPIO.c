#include "wiringPi.h"
#include "port_config.h"
#include "failures.h"
#include "stdbool.h"


void test_Output_CRK_no_failure() {
    bool CRK_signal = false;
    Output_CRK_no_failure();
    for (int i = 0; i < 100000000000; i++)
    {
        // Wait for a while
    }
    CRK_signal = true;
    Output_CRK_no_failure();
}

void main(void)
{
    test_Output_CRK_no_failure();
}
