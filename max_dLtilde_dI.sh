PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make max_dLtilde_dI

# SM1
./max_dLtilde_dI 1 > max_dLtilde_dI.res

# SM2
./max_dLtilde_dI 2 > max_dLtilde_dI_SM2.res

gnuplot max_dLtilde_dI.plt
mv max_dLtilde_dI.tex max_dLtilde_dI_SM2.tex $IMGDIR
