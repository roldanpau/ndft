extern const int SUCCESS;
extern const int ERR_IC_OUTSIDE_DOM;

int SM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip);
int damped_SM(int nfour, int ntori, double ddA[nfour][ntori], 
        double ddB[nfour][ntori], double ddOmega[ntori-1], int N, int M, double
        I, double phi, double *Ip, double *phip, double a);
