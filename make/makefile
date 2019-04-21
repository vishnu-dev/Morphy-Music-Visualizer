SRC=./../src/
KISS_FFT_PATH=./../kissfft/
LODE_PNG_PATH=./../lodepng/
BIN=./../bin/
OBJ=./../obj/
INCLUDE=./../include/
DATA=./../dat/
LOG=./../log/
LIB=./../lib/
CC=g++
CFLAG=-g -c -Wall
IFLAG=-I
OFLAG=-o
LFLAG=	-lGL -lGLU -lglut 	\
		-lsfml-graphics 	\
		-lsfml-window 		\
		-lsfml-system 		\
		-lsfml-audio 		\
		-lpthread

all: $(BIN)morphy

# link object files
$(BIN)morphy: $(OBJ)kiss_fft.o $(OBJ)lodepng.o $(OBJ)effects.o $(OBJ)main.o
	$(CC) $(OFLAG) $(BIN)morphy \
	$(OBJ)kiss_fft.o 			\
	$(OBJ)lodepng.o 			\
	$(OBJ)effects.o 			\
	$(OBJ)main.o 				\
	$(LFLAG)

# create object file for kiss_fft
$(OBJ)kiss_fft.o: $(KISS_FFT_PATH)src/kiss_fft.c 	\
$(KISS_FFT_PATH)include/_kiss_fft_guts.h 			\
$(KISS_FFT_PATH)include/kiss_fft.h 
	$(CC) $(CFLAG) $(KISS_FFT_PATH)src/kiss_fft.c 	\
	$(IFLAG) $(KISS_FFT_PATH)include/
	mv kiss_fft.o $(OBJ)

# create object file for lode_png
$(OBJ)lodepng.o: $(LODE_PNG_PATH)src/lodepng.cpp 	\
$(LODE_PNG_PATH)include/lodepng.h
	$(CC) $(CFLAG) $(LODE_PNG_PATH)src/lodepng.cpp 	\
	$(IFLAG) $(LODE_PNG_PATH)include/
	mv lodepng.o $(OBJ)

# create object file for effects
$(OBJ)effects.o: $(SRC)effects.cpp 		\
$(KISS_FFT_PATH)include/kiss_fft.h  	\
$(INCLUDE)headers.h
	$(CC) $(LFLAG) $(CFLAG) $(SRC)effects.cpp 	\
	$(IFLAG) $(KISS_FFT_PATH)include/ 			\
	$(IFLAG) $(INCLUDE)
	mv effects.o $(OBJ)

# create object file for main
$(OBJ)main.o: $(SRC)main.cpp 		\
$(LODE_PNG_PATH)include/lodepng.h 	\
$(KISS_FFT_PATH)include/kiss_fft.h 	\
$(INCLUDE)headers.h
	$(CC) $(LFLAG) $(CFLAG) $(SRC)main.cpp 	\
	$(IFLAG) $(LODE_PNG_PATH)include/ 		\
	$(IFLAG) $(KISS_FFT_PATH)include/ 		\
	$(IFLAG) $(INCLUDE)
	mv main.o $(OBJ)

# remove object and binary files 
clean:
	rm -f $(OBJ)*.o $(BIN)morphy

# install requirements
install: $(BIN)morphy
	apt-get install freeglut3-dev
	apt-get install libsfml-dev