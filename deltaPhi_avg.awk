# Given a certain torus (I=0.002), compute the average of the differences 
# \delta_\phi = \phi - phi' over all phi.

# Run with:
#    awk -f deltaPhi_avg.awk phi_phip_3_3 >deltaPhi_avg.res

BEGIN {pi = atan2(0, -1)}
{
	
	dp = $1-$2; 
	if(dp<0) dp += 2*pi;
	sum += dp;
}
END{printf("n=%d, sum=%f, average=%f\n", NR, sum, sum/NR)}
