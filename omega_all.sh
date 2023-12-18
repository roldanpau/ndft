./omega 1.0 > omega.res 2> omega_all.res
./omega 2.0 > omega.res 2>> omega_all.res
./omega 3.0 > omega.res 2>> omega_all.res
./omega 4.0 > omega.res 2>> omega_all.res
./omega 5.0 > omega.res 2>> omega_all.res
./omega 6.0 > omega.res 2>> omega_all.res
./omega 7.0 > omega.res 2>> omega_all.res

gnuplot omega_all.plt
mv omega_all.eps paper/images
