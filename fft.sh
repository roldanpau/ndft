PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images_SM2

make
for k in {2..8}
do
	# swap columns 1 and 2, and sort curve points according to phi_+
	awk -f swap.awk curve2_${k}_${k}_rng_0.res | LC_ALL=C sort -g -k 1,1 > curve_${k}

	# to perform DFT, interpolate curve on just 128 points
	./spline_interp curve_$k > curve_${k}_interp

	# perform DFT
	./fft curve_${k}_interp >coeffs_${k}.res 2> fft_${k}.res
done

gnuplot curves.plt
gnuplot decay_An.plt
gnuplot decay_Bn.plt

mv curves.tex $IMGDIR
mv decay_An.eps $IMGDIR
mv decay_Bn.eps $IMGDIR
