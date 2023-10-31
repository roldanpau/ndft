# Consider the image curve sigma(I,\phi) of a torus I by the transition map.
# Let (phi, I) and (phi', I) be two points on this curve.
# We would like to check that |phi'-phi| = \pi.
# Here, we compute the difference |phi'-phi|, and compare it to pi.

TOR=7

paste curve1_${TOR}_${TOR}_rng_0.res_1 curve1_${TOR}_${TOR}_rng_0.res_2 | \
	cut -d ' ' -f 4,8,15,19 > curve1_${TOR}_${TOR}_rng_0.res_12
awk -f symmetry.awk curve1_${TOR}_${TOR}_rng_0.res_12
