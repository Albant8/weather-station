
 /* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "bluenrg_x_device.h"
#include "BlueNRG1_conf.h"
#include "SDK_EVAL_Config.h"
#include "clock.h"

 
/*-----/!\---TO CHANGE ACCORDING TO YOUR SETUP---/!\-----*/





#define HS_STARTUP_TIME 328 // 800 us
#if (LS_SOURCE == LS_SOURCE_INTERNAL_RO)

/* Calibration must be done */
#define INITIAL_CALIBRATION         TRUE

#define CALIBRATION_INTERVAL        1000

#else

/* No Calibration */
#define INITIAL_CALIBRATION         FALSE
#define CALIBRATION_INTERVAL        0

#endif
