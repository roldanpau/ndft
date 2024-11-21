PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make max_dLtilde_dI

# SM1
./max_dLtilde_dI 1 > max_dLtilde_dI.res
# Put omega(I) and max dL_dI(I) into one single results file
paste -d ' ' <(cat omega_all.res) <(cut -d ' ' -f 2 max_dLtilde_dI.res) >phase_shift.res

# SM2
./max_dLtilde_dI 2 > max_dLtilde_dI_SM2.res
# Put omega(I) and max dL_dI(I) into one single results file
paste -d ' ' <(cat omega_all_SM2.res) <(cut -d ' ' -f 2 max_dLtilde_dI_SM2.res) >phase_shift_SM2.res

gnuplot phase_shift.gpi
#mv max_dLtilde_dI.tex max_dLtilde_dI_SM2.tex $IMGDIR
