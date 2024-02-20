# NOTES: Be sure to call FT before this script, to make sure that coefs ddA/ddB
# have already been computed, and file A2.res has been written.
make
./FT 2 0

# Find best fitting polynomial of degree M=2 to the first M+1=3 data points
# A_2(I=0), A_2(I=1), A_2(I=2), and extrapolate to I\in(0,7].
./interp_coef 1 2 2 > interp_poly_A2_M2
./interp_coef 0 2 2 > interp_poly_B2_M2

# Find best fitting polynomial of degree M=3 to the first M+1=4 data points
# A_2(I=0), A_2(I=1), A_2(I=2), A_2(I=3) and extrapolate to I\in(0,7].
./interp_coef 1 2 3 > interp_poly_A2_M3
./interp_coef 0 2 3 > interp_poly_B2_M3

# Find best fitting polynomial of degree M=4 to the first M+1=5 data points
# A_2(I=0), A_2(I=1), A_2(I=2), A_2(I=3), A_2(I=4) and extrapolate to I\in(0,7].
./interp_coef 1 2 4 > interp_poly_A2_M4
./interp_coef 0 2 4 > interp_poly_B2_M4

# Find best fitting polynomial of degree M=5 to the first M+1=6 data points
# A_2(I=0), A_2(I=1), A_2(I=2), A_2(I=3), A_2(I=4), A_2(I=5) and extrapolate to I\in(0,7].
./interp_coef 1 2 5 > interp_poly_A2_M5
./interp_coef 0 2 5 > interp_poly_B2_M5

gnuplot interp_poly_A2.plt
gnuplot interp_poly_B2.plt
mv interp_poly_A2.tex paper/images
mv interp_poly_B2.tex paper/images
