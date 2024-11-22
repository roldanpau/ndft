# Find interpolating polynomial to \f$\omega(I)\f$.

PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make interp_omega

# SM1 and SM2
./interp_omega 1 5 > interp_poly_omega_M5
./interp_omega 2 6 > interp_poly_omega_M6_SM2
gnuplot interp_omega.gpi
mv interp_omega.tex $IMGDIR

# SM2
#./interp_omega 2 6 > interp_poly_omega_M6_SM2
#gnuplot interp_omega_SM2.gpi
#mv interp_omega_SM2.tex $IMGDIR
