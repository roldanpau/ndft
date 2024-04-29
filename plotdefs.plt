# My style definitions for plots

PO = 100 # Style for PseudoOrbit
IM = 101 # Style for Inner Map iterates
SM1 = 102 # Style for Scattering Map 1 iterates
SM2 = 103 # Style for Scattering Map 2 iterates
PPSM1 = 104 # Style for Phase Portrait Scattering Map 1
PPSM2 = 105 # Style for Phase Portrait Scattering Map 2

paleviolet = "#BF9FDF"
paleorange= "#CF9F70"

set style line PO lc rgb "black" 
set style line IM pt 5 lc rgb "green"
set style line SM1 pt 5 lc rgb "blue"
set style line SM2 pt 5 lc rgb "red"
set style line PPSM1 pt 7 ps 0.1 lc rgb paleviolet
set style line PPSM2 pt 7 ps 0.1 lc rgb paleorange 

