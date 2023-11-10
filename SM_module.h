void SM(int nfour, int ntori, double ddA[nfour][ntori], 
		double ddB[nfour][ntori], double ddOmega[ntori], double I, double phi, 
		double *Ip, double *phip);
void damped_SM(int nfour, int ntori, double ddA[nfour][ntori], 
		double ddB[nfour][ntori], double ddOmega[ntori], double I, double phi, 
		double *Ip, double *phip, double a);
