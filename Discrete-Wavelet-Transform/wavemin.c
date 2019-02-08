/*
Copyright (c) 2017, Rafat Hussain
*/
#include "wavemin.h"
#include <math.h>

static const float db1_lp[2] = {
  0.7071067811865476,
  0.7071067811865476
};

static const float db1_hp[2] = {
  -0.7071067811865476,
  0.7071067811865476
};

void init_dwt(int N) {
  int i = 0;

  // Data length
  data_length = N;

  // Initialize approximate and detail coefficient vectors
  cA = (float*)malloc(sizeof(float) * N / 2);
  cD = (float*)malloc(sizeof(float) * N / 2);
  
  for (i = 0; i < N / 2; i++) {
    cA[i] = 0;
    cD[i] = 0;
  }
}

void clean_dwt() {
  free(cA);
  free(cD);
}

void clean_coefficients() {
  int i = 0;
  
  for (i = 0; i < data_length / 2; i++) {
    cA[i] = 0;
    cD[i] = 0;
  }
}

void smoothing(float *input) {
  int i = 0;

  for (i = 2; i < data_length; i++) {
    input[i] = (input[i - 2] + input[i - 1] + input[i]) / 3;
  }
}

void dwt(float *input) {
  int n = 0;
  int k = 1;
  int k_start = 1;

  clean_coefficients();
  smoothing(input);
  
  for (n = 1; n <= data_length / 2; n++) {
    for (k = 2 * n - 1; k <= 2 * n; k++) {
      cA[n - 1] += input[k - 1] *  db1_lp[2 * n - k];
      cD[n - 1] += input[k - 1] *  db1_hp[2 * n - k];
    }
  }
}

void get_coefficients(float *A, float *D) {
  int i = 0;

  for (i = 0; i < data_length / 2; i++) {
    A[i] = cA[i];
    D[i] = cD[i];
  }
}

void compute_variance(float *Var_A, float *Var_D) {
  int i = 0;
  int len = data_length / 2;
  float cA_mean_value = 0.0;
  float cD_mean_value = 0.0;
  
  for (i = 0; i < len; i++) {
    cA_mean_value += cA[i];
    cD_mean_value += cD[i];
  }
  cA_mean_value /= len;
  cD_mean_value /= len;
  
  for (i = 0; i < len; i++) {
    *Var_A += pow(cA[i] - cA_mean_value, 2.0);
    *Var_D += pow(cD[i] - cD_mean_value, 2.0);
  }
  
  *Var_A = sqrt(*Var_A / len);
  *Var_D = sqrt(*Var_D / len);
}

