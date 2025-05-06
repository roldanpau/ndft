PAPERDIR=~/research/ndft-paper
IMGDIR=$PAPERDIR/images

make spline_interp

# SM1
for k in {2..8}
do
	# swap columns 1 and 2, and sort curve points according to phi_+
	awk -f swap.awk newcurve1_${k}_${k}_rng_0.res | LC_ALL=C sort -g -k 1,1 > newcurve_${k}

	# interpolate curve on just 128 points
	./spline_interp newcurve_${k} > newcurve_${k}_interp

	rm newcurve_${k}

	# perform DFT
	#./fft curve_${k}_interp >coeffs_${k}.res 2> fft_${k}.res
done

#gnuplot curves.plt
#gnuplot decay_An.plt
#gnuplot decay_Bn.plt

#mv curves.tex $IMGDIR
#mv decay_An.eps $IMGDIR
#mv decay_Bn.eps $IMGDIR

# SM2
for k in {2..8}
do
	# swap columns 1 and 2, and sort curve points according to phi_+
	awk -f swap.awk newcurve2_${k}_${k}_rng_0.res | LC_ALL=C sort -g -k 1,1 > \
	newcurve_${k}_SM2

	# interpolate curve on just 128 points
	./spline_interp newcurve_${k}_SM2 > newcurve_${k}_interp_SM2

	rm newcurve_${k}_SM2

	# perform DFT
	#./fft curve_${k}_interp_SM2 >coeffs_${k}_SM2.res 2> fft_${k}_SM2.res
done

