# Compute local FT error over the domain I\in[0,3]

make FT_error
./FT_error 1 3 > FT_error_local.res
#gnuplot FT_error_local.plt
#mv FT_error_local.tex paper/images
cp FT_error_local.res paper/tables
