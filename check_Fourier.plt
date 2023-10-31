#set out "check_Fourier.eps"
#set term post eps color

N = 128

A0 = 1.998141
A1 = -.005451797
A2 = .3144631
A3 = .002467017
A4 = .01378835

B0 = 0
B1 = .001753320
B2 = -.2036542
B3 = -.002333679
B4 = -.02883811

f1(x) = A0 + A2*cos(2*x) + B2*sin(2*x) 
f2(x) = A0 + A2*cos(2*x) + B2*sin(2*x) + A4*cos(4*x) + B4*sin(4*x)
plot "curve_3" w p, \
f1(x) with lines lt 1 t "Fourier coefs A2,B2", \
f2(x) with lines lt 2 t "Fourier coefs A2,B2,A4,B4"

set term pop
set out
