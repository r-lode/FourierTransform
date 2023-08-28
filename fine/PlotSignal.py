import matplotlib.pyplot as plt
import numpy as np
import string as str




def PlotPoly():
    """
    Function designed for potting discrete time signals
    """
    fid = open('dft_data.txt', 'r')
    NumPts = 0
    while True:
        line=fid.readline()
        if not line: break
        NumPts = NumPts + 1
    fid.close()

    x= np.zeros(NumPts,dtype=float)
    y= np.zeros(NumPts, dtype=float)
    re = np.zeros(NumPts, dtype=float)
    im= np.zeros(NumPts, dtype=float)
    p = np.zeros(NumPts, dtype=float);
    fid = open('dft_data.txt', 'r')
    for k in range(0, NumPts-1):
         linestring = fid.readline()
         linelist= linestring.split()
         x[k] = float(linelist[0])
         y[k] = float(linelist[1])
         re[k] = float(linelist[2])
         im[k] = float(linelist[3])
         p[k] = float(linelist[4])
         #print(x[k], ": ", p[k])

    fid.close()

    
    ##plotting original data
    ##MUST Change n to 10000
    #plt.rc("font", size=16); 
    #plt.figure(figsize =(20, 5))
    #plt.figure(1)
    #plt.plot(x, y, linestyle="solid", linewidth=1, marker=".", color="red", markersize=6)
    #plt.xlim(0, 10000) 
    #plt.ylim(-3, 3) 
    ##x-tick dimensions
    #plt.xticks([0, 2000,4000,6000,8000])
    #ax = plt.gca(); 
    #ax.grid(True)
    ##Label Formating
    #plt.xlabel("Time", size = 15) 
    #plt.ylabel("Signal Values", size = 15)
    #plt.title("Original Signal Data", size = 20)
    #plt.show()


    #plotting real and imaginary components of DFT
    #MUST Change n to 500
    plt.rc("font", size=16); 
    plt.figure(figsize =(20, 5))
    #plt.figure(1)
    plt.plot(x, re, linestyle="solid", linewidth=1, marker=".", color="red", markersize=6)
    plt.plot(x, im, linestyle="solid", linewidth=1, marker=".", color="blue", markersize=6)
    plt.xlim(0, 500) 
    ax = plt.gca(); 
    ax.grid(True)
    ##Label Formating
    plt.xlabel("Time", size = 15) 
    plt.ylabel("Signal Values", size = 15)
    plt.title("Real component(red) vs imaginary component (blue)", size = 20)
    plt.show()


    ##plotting power spectrum of signal
    ##MUST Change n to 500
    #plt.rc("font", size=16); 
    #plt.stem(x,p)
    #plt.show()

   


if __name__ == "__main__":
    PlotPoly();