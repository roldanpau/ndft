# Compute the difference \phi - phi' for all phi in a certain torus I=0.002

# Run with:
#    awk -f phi_minus_phip.awk phi_phip_3_3 >phi_minus_phip.res

BEGIN {pi = atan2(0, -1)}
{
	
	dp=$1-$2; 
	if(dp<0) dp += 2*pi;
	printf("%f %f\n", $2, dp)
}
