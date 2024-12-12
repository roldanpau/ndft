PAPERDIR=~/research/ndft-paper
IMGDIR=$PAPERDIR/images

make max_dLtilde_dI

# SM1
./max_dLtilde_dI 1 > max_dLtilde_dI.res
# Put omega(I) and max dL_dI(I) into one single results file
paste -d ' ' <(cat interp_poly_omega_M5) <(cut -d ' ' -f 2 max_dLtilde_dI.res) >phase_shift.res

# SM2
./max_dLtilde_dI 2 > max_dLtilde_dI_SM2.res
# Put omega(I) and max dL_dI(I) into one single results file
paste -d ' ' <(cat interp_poly_omega_M6_SM2) <(cut -d ' ' -f 2 max_dLtilde_dI_SM2.res) >phase_shift_SM2.res

gnuplot phase_shift.gpi
mv phase_shift.tex phase_shift_SM2.tex $IMGDIR
