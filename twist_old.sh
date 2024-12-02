PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make max_d2Ltilde_dI

# SM1
./max_d2Ltilde_dI 1 > max_d2Ltilde_dI.res
# Put domega(I) and max d2L_dI(I) into one single results file
paste -d ' ' <(cat interp_poly_domega_M5) \
	<(cut -d ' ' -f 2 max_d2Ltilde_dI.res) >twist.res

# SM2
./max_d2Ltilde_dI 2 > max_d2Ltilde_dI_SM2.res
# Put domega(I) and max d2L_dI(I) into one single results file
paste -d ' ' <(cat interp_poly_domega_M6_SM2) \
	<(cut -d ' ' -f 2 max_d2Ltilde_dI_SM2.res) >twist_SM2.res

gnuplot twist.gpi
mv twist.tex twist_SM2.tex $IMGDIR
