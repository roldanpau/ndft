progs = lin_interp spline_interp fft fdd Fourier_coefs_given_I \
		dLstar_dI Lstar dL_dphip omega \
		FT FT_error_given_I FT_error \
		interp_coef interp_omega \
		T T_error \
		SM SM_given_I \
		explore \
		phase_port_SM \
		IM \
		diffusion diffusion_greedy diffusion_triple_greedy \
		dijkstra diffusion_shortest_path diffusion_shortest_path_TM \
		diffusion_stoch

objects = FT.o FT_module.o \
		  FT_error.o \
		  interp_coef.o interp_omega.o \
		  dLstar_dI.o \
		  Lstar.o \
		  dL_dphip.o \
		  omega.o \
		  T.o T_module.o \
		  T_error.o \
		  SM.o SM_module.o \
		  TM_module.o \
		  SM_given_I.o \
		  explore.o \
		  phase_port_SM.o \
		  IM.o IM_module.o \
		  diffusion.o diffusion_greedy.o diffusion_triple_greedy.o \
		  dijkstra.o dijkstra_module.o diffusion_shortest_path.o \
		  diffusion_shortest_path_TM.o \
		  diffusion_stoch.o

CFLAGS = -g #-O3
LDFLAGS = -g #-O3
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

fdd: fdd.c
	gcc -o fdd fdd.c -lm

Fourier_coefs_given_I: Fourier_coefs_given_I.c
	gcc -o Fourier_coefs_given_I Fourier_coefs_given_I.c -lgsl

dLstar_dI: dLstar_dI.o FT_module.o

Lstar: Lstar.o FT_module.o

dL_dphip: dL_dphip.o FT_module.o

omega: omega.o FT_module.o

FT: FT.o FT_module.o 

FT_error_given_I: FT_error_given_I.c
	gcc -o FT_error_given_I -g FT_error_given_I.c -lgsl -lm

FT_error: FT_error.o FT_module.o

interp_coef: interp_coef.o FT_module.o

interp_omega: interp_omega.o T_module.o

T: T.o T_module.o 

T_error: T_error.o T_module.o FT_module.o SM_module.o

SM: SM.o SM_module.o FT_module.o T_module.o

SM_given_I: SM_given_I.o SM_module.o FT_module.o T_module.o

explore: explore.o SM_module.o FT_module.o T_module.o

phase_port_SM: phase_port_SM.o SM_module.o FT_module.o T_module.o

IM: IM.o IM_module.o T_module.o

diffusion: diffusion.o SM_module.o FT_module.o T_module.o IM_module.o

diffusion_greedy: diffusion_greedy.o SM_module.o FT_module.o T_module.o IM_module.o

diffusion_triple_greedy: diffusion_triple_greedy.o SM_module.o FT_module.o T_module.o IM_module.o

dijkstra: dijkstra.o dijkstra_module.o

diffusion_shortest_path: diffusion_shortest_path.o SM_module.o FT_module.o \
	T_module.o IM_module.o dijkstra_module.o

diffusion_shortest_path_TM: diffusion_shortest_path_TM.o TM_module.o \
	SM_module.o FT_module.o T_module.o IM_module.o dijkstra_module.o

diffusion_stoch: diffusion_stoch.o SM_module.o FT_module.o T_module.o IM_module.o
	gcc -o diffusion_stoch -g diffusion_stoch.c SM_module.c FT_module.c \
	T_module.c IM_module.c -lgsl -lm

.PHONY : clean
clean:
	-rm $(progs) $(objects)
