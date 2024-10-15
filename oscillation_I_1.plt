#set term png
#set out "oscillation_I_1.png"

set xrange [0:pi]

I = 1
a1 = 0.18
b1 = -0.1
plot b1*sin(2*x) + a1*cos(2*x)

#set out
#set term pop
