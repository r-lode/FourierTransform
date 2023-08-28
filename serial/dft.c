
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef _OPENMP
#   include <omp.h>
#endif
 

int main(int argc, char* argv[])
{


void usage(const char* prog);

if(argc != 3){usage(argv[0]);}

const int thread_count = strtol(argv[1], NULL, 10);
const int N = strtol(argv[2], NULL, 10);

//input checking
if(thread_count <= 0|| N <=0 ){
    usage(argv[0]);
}


    //define constants
    const float PI = 3.14159265359;   

    //instantiate arrays for data storage
    float t[N]; //time increment
    float o[N]; //array to store original signal
    float dft_re[N], dft_im[N]; //arrays to store real and imaginary components
    float Amp[N]; //array to store spectral values


    int amp_lim = 2; //original amplitude limit
    srand(time(0));
    t[0] = 0;
    for (int n=0 ; n<N ; ++n){
        o[n] = amp_lim* (((2.0* rand()) / RAND_MAX)- 1);
        t[n] = t[n-1] +1;
    } 

    const double time1 = omp_get_wtime();

    // main loop to calculate DFT using a bf approach
    for (int k=0 ; k<N ; ++k)
    {
        
        //calculating real part of fourier coefficient
        dft_re[k] = 0;
        for (int j=0 ; j<N ; ++j){
            int w = 2*PI *k*j;
            dft_re[k] += (o[j] * cos(w/N));
        } 
         
        // Calculating imaginary part of fourier coefficient
        dft_im[k] = 0;
        for (int j=0 ; j<N ; ++j){
           int w = 2*PI *k*j;
           dft_im[k] -= (o[j] * sin(w/ N)); 
        } 
         
        // Spectral amplitutde
        Amp[k] = sqrt(dft_re[k]*dft_re[k] + dft_im[k]*dft_im[k]);
    }

    const double time2 = omp_get_wtime();
    printf("time = %12.5e\n\n", time2- time1);
 

     FILE *f = fopen("dft_data.txt", "w");

    for (int n=0 ; n<N ; ++n){
        fprintf(f, "%f %f %f %f %f\n", t[n], o[n], dft_re[n], dft_im[n], Amp[n]);
    } 

    fclose(f);



     //  //Plotting output
    system("python3 PlotSignal.py");

    return 0;
}


/**
 * @brief Program to allow user to specify number of threads and number of intervals
 * 
 * @param prog_name 
 */
void usage(const char *prog_name)
{
    fprintf(stderr, "usage:  %s <num_threads> <num_data> \n", prog_name);
    fprintf(stderr, "   num _threads should be positive \n");
    fprintf(stderr,  "  time data should be positive \n");
    exit(1);

}