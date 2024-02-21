void SM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip);
void damped_SM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip, double a);
