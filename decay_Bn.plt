set out "decay_Bn.eps"
set term post eps color

set title "Decay of Fourier coeffs B_n (log-log plot)"
set xlabel "n"
set ylabel "|B_n|"

set logscale xy

plot [1:40] \
"fft_2.res" u 1:3 w lp t "I=1", \
"fft_3.res" u 1:3 w lp t "I=2", \
"fft_4.res" u 1:3 w lp t "I=3", \
"fft_5.res" u 1:3 w lp t "I=4", \
"fft_6.res" u 1:3 w lp t "I=5", \
"fft_7.res" u 1:3 w lp t "I=6", \
"fft_8.res" u 1:3 w lp t "I=7"
set term pop
set out 
