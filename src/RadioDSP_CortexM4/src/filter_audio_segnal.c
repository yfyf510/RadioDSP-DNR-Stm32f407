/**
  ******************************************************************************
  * @file    filter_audio_segnal.c
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V2.0.0
  * @date    25-09-2018
  * @brief   IO Routine
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  * Platform: CortexM4
  ******************************************************************************/

#include "stm32f4xx_conf.h"
#include "filter_audio_segnal.h"
/*  Calculator used: https://www.arc.id.au/FilterDesign.html */

//WIDE FIR 16khz LPF (passthrough)
const float32_t firCoeffs32_3[NUM_TAPS_3] = {
0.000803,
-0.002771,
0.002753,
0.005922,
-0.030437,
0.072367,
-0.123064,
0.165313,
0.818182,
0.165313,
-0.123064,
0.072367,
-0.030437,
0.005922,
0.002753,
-0.002771,
0.000803};

//LARGE FIR > 6khz LPF

const float32_t firCoeffs32_4[NUM_TAPS_4] = {
0.000738,
-0.001982,
-0.007386,
0.015886,
0.021774,
-0.066504,
-0.038116,
0.302661,
0.545455,
0.302661,
-0.038116,
-0.066504,
0.021774,
0.015886,
-0.007386,
-0.001982,
0.000738};


// MEDIUM FIR 3.5 khz lpf
const float32_t firCoeffs32[NUM_TAPS] = {-0.000400,
0.000035,
0.002694,
0.006432,
0.005821,
-0.005180,
-0.024551,
-0.036263,
-0.016296,
0.049204,
0.146726,
0.235915,
0.272109,
0.235915,
0.146726,
0.049204,
-0.016296,
-0.036263,
-0.024551,
-0.005180,
0.005821,
0.006432,
0.002694,
0.000035,
-0.000400
};


// NARROW CW FIR 300 1000 BPF
const float32_t firCoeffs32_2[NUM_TAPS_2] ={-0.000073,
-0.000063,
-0.000046,
-0.000025,
-0.000007,
-0.000000,
-0.000016,
-0.000065,
-0.000158,
-0.000307,
-0.000516,
-0.000789,
-0.001124,
-0.001509,
-0.001930,
-0.002364,
-0.002781,
-0.003150,
-0.003437,
-0.003609,
-0.003639,
-0.003507,
-0.003206,
-0.002740,
-0.002135,
-0.001427,
-0.000675,
0.000052,
0.000673,
0.001100,
0.001250,
0.001042,
0.000416,
-0.000667,
-0.002218,
-0.004211,
-0.006582,
-0.009229,
-0.012013,
-0.014761,
-0.017278,
-0.019351,
-0.020767,
-0.021321,
-0.020836,
-0.019171,
-0.016234,
-0.011994,
-0.006488,
0.000180,
0.007835,
0.016242,
0.025110,
0.034108,
0.042883,
0.051073,
0.058331,
0.064341,
0.068838,
0.071621,
0.072562,
0.071621,
0.068838,
0.064341,
0.058331,
0.051073,
0.042883,
0.034108,
0.025110,
0.016242,
0.007835,
0.000180,
-0.006488,
-0.011994,
-0.016234,
-0.019171,
-0.020836,
-0.021321,
-0.020767,
-0.019351,
-0.017278,
-0.014761,
-0.012013,
-0.009229,
-0.006582,
-0.004211,
-0.002218,
-0.000667,
0.000416,
0.001042,
0.001250,
0.001100,
0.000673,
0.000052,
-0.000675,
-0.001427,
-0.002135,
-0.002740,
-0.003206,
-0.003507,
-0.003639,
-0.003609,
-0.003437,
-0.003150,
-0.002781,
-0.002364,
-0.001930,
-0.001509,
-0.001124,
-0.000789,
-0.000516,
-0.000307,
-0.000158,
-0.000065,
-0.000016,
-0.000000,
-0.000007,
-0.000025,
-0.000046,
-0.000063,
-0.000073};

#ifdef EXP_SMOOTING
// Variable noise filter (Exponential Smooting Moving Filter) : n: 3 (max) - 1 (min)
void smootingFilter(float* smotStatusBuffer, float* bufferIn, float* bufferOut, uint8_t n,int blockSize){

    float coeff;
    if (n==1) coeff = 0.8;
	if (n==2) coeff = 0.7;
	if (n==3) coeff = 0.6;
	if (n==4) coeff = 0.5;
	if (n==5) coeff = 0.3;
	if (n==6) coeff = 0.1;

    for (int i = 0; i<blockSize; i++){
     smotStatusBuffer[i]+= (bufferIn[i] - smotStatusBuffer[i]) * coeff;
     bufferOut[i]= smotStatusBuffer[i];
    }
}
#endif

/**************************************END OF FILE****/
