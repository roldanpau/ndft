# Consider the image curve sigma(I,\phi) of a torus I by the transition map.
# Let (phi, I) and (phi', I) be two points on this curve.
# We would like to check that |phi'-phi| = \pi.
# Here, we compute the difference |phi'-phi|, and compare it to pi.

# CALL WITH: 
#    awk -f symmetry.awk curve1_3_3_rng_0.res_12

function abs(v) {return v<0? -v:v}

BEGIN {pi = atan2(0,-1)}
{
	dp = abs($2-$4);
	printf("%f %f\n", $1, abs(pi-dp))
}
