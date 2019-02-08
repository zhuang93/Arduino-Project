/*
Copyright (c) 2017, Rafat Hussain
*/
#ifndef WAVEMIN_H_
#define WAVEMIN_H_

#ifdef __cplusplus
extern "C" {
#endif

int data_length;

float *cA;
float *cD;

void init_dwt(int N);
void clean_dwt();
void dwt(float *input);
void get_coefficients(float *A, float *D);

void compute_variance(float *Var_A, float *Var_D);

#ifdef __cplusplus
}
#endif


#endif /* WAVEMIN_H_ */
