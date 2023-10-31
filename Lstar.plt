set out "Lstar.eps"
set term post eps color

#set view map
#unset key

set dgrid3d 100,100 qnorm 2

#unset surface

set contour base

set cntrparam levels 15

set xlabel "I"
set ylabel "phi\'"

splot "Lstar.res" u 2:1:3 with lines

set term pop
set out
