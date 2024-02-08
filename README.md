# NDFT

Approximate Transition Map

## Description

The *approximate transition map* $\tilde{\sigma}(I,\phi)$ consists in the
Fourier-Taylor approximation of the semi-analytical transition map. The
approximate map is derived from the semi-analytical map in
Section~\ref{Sec:GeneratingFunction} of the accompanying paper, so it is not as
precise. However, the approximate map has the advantage that it can be
evaluated at any desired point $(I,\phi)$.

## Getting Started

### Dependencies

* You will most likely need a linux OS with the usual C/C++ developing
environment (compiler, libraries). 
* You will need GNU Awk (not just the Ubuntu default mawk) for some of the BASH
  scripts to work (e.g. for fft.sh).
* Moreover, you will need to install the GNU Scientific Library (GSL).

### Installing

* Download code to any directory and type `make`.
* `make clean` to clean up objects and binaries.

### Executing program

* This project consists of several different programs, e.g. `spline_interp`,
`fft`, `FT`, `omega`, etc. They are run from the command line. They usually
accept arguments on the command line, and output results to stdout, e.g.
```
./lin_interp curve > curve_interp
```

## Help

Please read source code for a detailed description of each program, including
arguments and results. Usually, running the program without arguments will
complain and explain the right usage, e.g.
```
./FT
Num of args incorrect. Usage: ./FT scaled_I phip
```

## Authors

Contributors names and contact info

Pablo Roldan
[@roldanpau](https://www.linkedin.com/in/pauroldan/)

## Version History

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the COPYING file for details

## Acknowledgments

<!---
Inspiration, code snippets, etc.
* [awesome-readme](https://github.com/matiassingers/awesome-readme)
* [PurpleBooth](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
* [dbader](https://github.com/dbader/readme-template)
* [zenorocha](https://gist.github.com/zenorocha/4526327)
* [fvcproductions](https://gist.github.com/fvcproductions/1bfc2d4aecb01a834b46)
-->
