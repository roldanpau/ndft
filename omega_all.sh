PAPERDIR=~/mat-nuvol/research/ndft-paper
IMGDIR=$PAPERDIR/images

make omega

# SM1
./omega 1 1.0 > omega.res 2> omega_all.res
./omega 1 2.0 > omega.res 2>> omega_all.res
./omega 1 3.0 > omega.res 2>> omega_all.res
./omega 1 4.0 > omega.res 2>> omega_all.res
./omega 1 5.0 > omega.res 2>> omega_all.res
./omega 1 6.0 > omega.res 2>> omega_all.res
./omega 1 7.0 > omega.res 2>> omega_all.res

# SM2
./omega 2 1.0 > omega_SM2.res 2> omega_all_SM2.res
./omega 2 2.0 > omega_SM2.res 2>> omega_all_SM2.res
./omega 2 3.0 > omega_SM2.res 2>> omega_all_SM2.res
./omega 2 4.0 > omega_SM2.res 2>> omega_all_SM2.res
./omega 2 5.0 > omega_SM2.res 2>> omega_all_SM2.res
./omega 2 6.0 > omega_SM2.res 2>> omega_all_SM2.res
./omega 2 7.0 > omega_SM2.res 2>> omega_all_SM2.res

gnuplot omega_all.plt
mv omega_all.tex $IMGDIR
