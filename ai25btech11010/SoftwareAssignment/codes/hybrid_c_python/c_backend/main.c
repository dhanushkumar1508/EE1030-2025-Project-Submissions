#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//for accessing the i,j element of A
#define A(i, j) A_flat[(i) * n + (j)]

//for finding matrix A_flat * vector X
void mat_vec_mult(int m, int n, const double *A_flat, const double *x, double *y) {
    for (int i = 0; i < m; i++) {
        y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            y[i] += A(i, j) * x[j];
        }
    }
}

//for finding transpose of matrix A* vector x
void mat_t_vec_mult(int m, int n, const double *A_flat, const double *x, double *y) {
    for (int j = 0; j < n; j++) {
        y[j] = 0.0;
        for (int i = 0; i < m; i++) {
            y[j] += A(i, j) * x[i];
        }
    }
}

//to find norm of a vector v
double vec_norm(int len, const double *v) {
    double sum_sq = 0.0;
    for (int i = 0; i < len; i++) {
        sum_sq += v[i] * v[i];
    }
    return sqrt(sum_sq);
}

//to find normalized vector of a vector v
void vec_normalize(int len, double *v) {
    double norm = vec_norm(len, v);
    if (norm > 1e-12) {
        for (int i = 0; i < len; i++) {
            v[i] /= norm;
        }
    }
}

//funtion to perform power iteration
void power_iteration(int m, int n, const double *A_flat_in, double *u, double *sigma, double *v) {
    const int MAX_ITER = 100;
    const double TOLERANCE = 1e-6;

    for(int i = 0; i < n; i++) {
        v[i] = (double)rand() / RAND_MAX;//creates a random vector
    }
    vec_normalize(n, v);
     
    //allocate memory vector Av and ATAv
    double *Av = (double*)malloc(m * sizeof(double));
    double *ATAv = (double*)malloc(n * sizeof(double));

    for (int k = 0; k < MAX_ITER; k++) {
        double v_old_norm = vec_norm(n, v);
          

        mat_vec_mult(m, n, A_flat_in, v, Av);  //mutiples A_flat and v   
        mat_t_vec_mult(m, n, A_flat_in, Av, ATAv); 

        for(int i = 0; i < n; i++) {
            v[i] = ATAv[i];// copy ATAv to v
        }
        vec_normalize(n, v);

        if (v_old_norm > 1e-12) {
            double diff_norm = 0.0;
            
            double ATAv_norm = vec_norm(n, ATAv);
            if (ATAv_norm > 1e-12) {
                for(int i = 0; i < n; i++) {
                    double diff = v[i] - (ATAv[i] / ATAv_norm);//here it will becomes zero when it coverges
                    diff_norm += diff * diff;
                }
            }
            
            if (sqrt(diff_norm) < TOLERANCE) {
                break;//break when it coverges
            }
        }
    }
    
    mat_vec_mult(m, n, A_flat_in, v, Av);
    
    *sigma = vec_norm(m, Av);

    if (*sigma > 1e-12) {
        for (int i = 0; i < m; i++) {
            u[i] = Av[i] / *sigma;
        }
    } else {
        for (int i = 0; i < m; i++) {
            u[i] = 0.0;
        }
    }

    free(Av);
    free(ATAv);
}

void svd_reconstruct(int m, int n, const double *A_orig_flat, int k, double *A_k_flat, double *frobenius_error_out) {
    
    double *A_current_flat = (double*)malloc(m * n * sizeof(double));
    for (int i = 0; i < m * n; i++) {
        A_current_flat[i] = A_orig_flat[i]; 
        A_k_flat[i] = 0.0;                  
    }
    
    double sigma = 0.0;
    double *u = (double*)malloc(m * sizeof(double));
    double *v = (double*)malloc(n * sizeof(double));


    for (int i = 0; i < k; i++) {

        power_iteration(m, n, A_current_flat, u, &sigma, v);// to find u , v ,sigma

        if (sigma < 1e-4) {
            break;// if sigma is zero no point of adding it A_k
        }

        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                A_k_flat[r * n + c] += sigma * u[r] * v[c];
            }
        }
        
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                A_current_flat[r * n + c] -= sigma * u[r] * v[c];// remove the top k 
            }
        }
    }
    
    free(A_current_flat);
    free(u);
    free(v);

    double sum_sq_error = 0.0;
    for (int i = 0; i < m * n; i++) {
        double error = A_orig_flat[i] - A_k_flat[i];
        sum_sq_error += error * error;
    }

    
    *frobenius_error_out = sqrt(sum_sq_error);
}
