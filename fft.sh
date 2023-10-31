for k in {3..7}
do
	# swap columns 1 and 2, and sort curve points according to phi_+
	awk -f swap.awk curve1_${k}_${k}_rng_0.res | sort -g -k 1,1 > curve_${k}

	# to perform DFT, interpolate curve on just 128 points
	./spline_interp curve_$k > curve_${k}_interp

	# perform DFT
	./fft curve_${k}_interp >coeffs_${k}.res 2> fft_${k}.res
done

