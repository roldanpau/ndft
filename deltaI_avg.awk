# Given a certain torus (I=0.002), compute the average of the differences 
# \delta_\I = \I - I' over all phi.

# Run with:
#    awk -f deltaI_avg.awk I_Ip_3_3 >deltaI_avg.res

BEGIN {pi = atan2(0, -1)}
{
	dI = $1-$2; 
	sum += dI;
}
END{printf("n=%d, sum=%f, average=%f\n", NR, sum, sum/NR)}
