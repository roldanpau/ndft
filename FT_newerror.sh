# Compute global FT error over the global domain I\in[0,7]

PAPERDIR=~/research/ndft-paper
IMGDIR=$PAPERDIR/images
TBLDIR=$PAPERDIR/tables

make FT_newerror

# SM1
./FT_newerror 1 7 > FT_newerror.res
#gnuplot FT_error.plt
#mv FT_error.tex $IMGDIR
mv FT_newerror.tex $TBLDIR

# SM2
./FT_newerror 2 7 > FT_newerror_SM2.res
#gnuplot FT_error_SM2.plt
#mv FT_error_SM2.tex $IMGDIR
