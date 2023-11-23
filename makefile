progs = lin_interp spline_interp fft interp_coef fdd Fourier_coefs_given_I \
		dLstar_dI Lstar omega \
		SM_given_I FT FT_error_given_I FT_error \
		T T_error \
		SM \
		explore \
		phase_port_SM

objects = FT.o FT_module.o \
		  FT_error.o \
		  dLstar_dI.o \
		  Lstar.o \
		  omega.o \
		  T.o T_module.o \
		  T_error.o \
		  SM.o SM_module.o \
		  explore.o \
		  phase_port_SM.o

CFLAGS = -g
LDFLAGS = -g
LDLIBS = -lm -lgsl -lgslcblas

all: $(progs)

#	gcc -o lin_interp -ggdb lin_interp.c -lgsl
lin_interp: lin_interp.c
	gcc -o lin_interp lin_interp.c -lgsl

spline_interp: spline_interp.c
	gcc -o spline_interp spline_interp.c -lgsl

#ndft: ndft.c
#	gcc -o ndft ndft.c -lnfft3

fft: fft.c
	gcc -o fft fft.c -lgsl -lm

interp_coef: interp_coef.c
	gcc -o interp_coef interp_coef.c -lgsl

fdd: fdd.c
	gcc -o fdd fdd.c -lm

Fourier_coefs_given_I: Fourier_coefs_given_I.c
	gcc -o Fourier_coefs_given_I Fourier_coefs_given_I.c -lgsl

dLstar_dI: dLstar_dI.o FT_module.o

Lstar: Lstar.o FT_module.o

omega: omega.o FT_module.o

SM_given_I: SM_given_I.c
	gcc -o SM_given_I SM_given_I.c -lgsl -lm

FT: FT.o FT_module.o 

FT_error_given_I: FT_error_given_I.c
	gcc -o FT_error_given_I -g FT_error_given_I.c -lgsl -lm

FT_error: FT_error.o FT_module.o

T: T.o T_module.o 

T_error: T_error.o T_module.o FT_module.o

SM: SM.o SM_module.o FT_module.o T_module.o

explore: explore.o SM_module.o FT_module.o T_module.o

phase_port_SM: phase_port_SM.o SM_module.o FT_module.o T_module.o

.PHONY : clean
clean:
	-rm $(progs) $(objects)
