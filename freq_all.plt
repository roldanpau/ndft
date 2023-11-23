set out "freq_all.eps"
set term post eps color

pi=3.14159265358979323844
set xlabel "I"
set ylabel "nu"
plot 'freq_all.res' u ($1):(2*pi*$4/$3) w lp not

set term pop
set out
