#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
 

int main(int argc, char* argv[])
{

    //MPI initialization
    int comm_sz, my_rank;
	MPI_Init(NULL,NULL); 
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);   
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);   

void usage(const char* prog);

if(argc != 3){usage(argv[0]);}

//set num processors and data points
const int num_processors = strtol(argv[0], NULL, 10);
const int N = strtol(argv[2], NULL, 10);

//input checking
if(num_processors <= 0|| N <=0 || N % num_processors != 0){
    usage(argv[0]);
    MPI_Finalize();
    return 0;
}

    //define constants
    const float PI = 3.14159265359;   

    //instantiate arrays for data storage
    float t[N]; //time increment
    float o[N]; //array to store original signal
    float dft_re[N], dft_im[N]; //arrays to store real and imaginary components
    float Amp[N]; //array to store spectral values


    //instantiate sub-arrays

    float o_sub[N/comm_sz];
    float re_sub[N/comm_sz];
    float im_sub[N/comm_sz];


    int amp_lim = 2; //original amplitude limit
    srand(time(0));
    t[0] = 0;
    //loop to instantiate random signal
    for (int n=0 ; n<N ; ++n){
        o[n] = amp_lim* (((2.0* rand()) / RAND_MAX)- 1);
        t[n] = t[n-1] +1;
    } 

    double time1;
    double time2;
    //get start time
    if (my_rank==0)
        {  
            time1 = MPI_Wtime();  
        }

    int local_n = (N / comm_sz); 

    //attempt to distrubute sub arrays to different processors
	MPI_Scatter(o,local_n,MPI_DOUBLE,o_sub,local_n,MPI_DOUBLE,0,MPI_COMM_WORLD); 
    MPI_Scatter(dft_re,local_n,MPI_DOUBLE,re_sub,local_n,MPI_DOUBLE,0,MPI_COMM_WORLD); 
    MPI_Scatter(dft_im,local_n,MPI_DOUBLE,im_sub,local_n,MPI_DOUBLE,0,MPI_COMM_WORLD); 

    //main loop to compute DFT
    for (int k=0 ; k<N ; ++k)
    {

        
        //calculating real part of fourier coefficient
        re_sub[k] = 0;
        for (int j=0 ; j<local_n ; ++j){
            int w = 2*PI *k*j;
            re_sub[k] += (o_sub[j] * cos(w/N));
        } 
         
        // Calculating imaginary part of fourier coefficient
        im_sub[k] = 0;
        for (int j=0 ; j<local_n; ++j){
           int w = 2*PI *k*j;
           im_sub[k] -= (o_sub[j] * sin(w/ N)); 
        } 
         
       
    }

    //gathering subarrays into larger arrays
    MPI_Gather(o_sub,local_n,MPI_DOUBLE_COMPLEX,o,local_n, MPI_DOUBLE_COMPLEX,0,MPI_COMM_WORLD);
    MPI_Gather(re_sub,local_n,MPI_DOUBLE_COMPLEX,dft_re,local_n, MPI_DOUBLE_COMPLEX,0,MPI_COMM_WORLD);
    MPI_Gather(im_sub,local_n,MPI_DOUBLE_COMPLEX,dft_im,local_n, MPI_DOUBLE_COMPLEX,0,MPI_COMM_WORLD);

    
    if (my_rank==0)
        {  
            time2 = MPI_Wtime();  
        }

   

 for (int k=0 ; k<N ; ++k)
    {
         // Spectral amplitutde
        Amp[k] = sqrt(dft_re[k]*dft_re[k] + dft_im[k]*dft_im[k]);

    }
    

    //const double time2 = omp_get_wtime();
    printf("time = %12.5e\n\n", time2- time1);
 

     FILE *f = fopen("dft_data.txt", "w");

    for (int n=0 ; n<N ; ++n){
        fprintf(f, "%f %f %f %f %f\n", t[n], o[n], dft_re[n], dft_im[n], Amp[n]);
    } 

    fclose(f);


     //  //Plotting output
    //system("python3 PlotSignal.py");
    MPI_Finalize();
    return 0;
}


/**
 * @brief Program to allow user to specify number of threads and number of processors
 * 
 * @param prog_name 
 */
void usage(const char *prog_name)
{
    fprintf(stderr, "Number of input arguments must be 3 \n");
    fprintf(stderr, " Number of data points must be greater than 0 \n");
    fprintf(stderr,  " Number of data points must be exactly divisible by the number of processors  \n");
    exit(1);

}