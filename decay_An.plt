set out "decay_An.eps"
set term post eps color

set title "Decay of Fourier coeffs A_n (log-log plot)"
set xlabel "n"
set ylabel "|A_n|"

set logscale xy

plot [1:40] \
"fft_3.res" u 1:2 w lp t "I=2", \
"fft_4.res" u 1:2 w lp t "I=3", \
"fft_5.res" u 1:2 w lp t "I=4", \
"fft_6.res" u 1:2 w lp t "I=5", \
"fft_7.res" u 1:2 w lp t "I=6"
set term pop
set out 
