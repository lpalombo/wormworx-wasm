CC = emcc
CXX = em++
CFLAGS = -Wall -I./cpp/sundials-2.3.0/include -I./cpp/sundials-2.3.0/src
CXXFLAGS = -std=c++11 $(CFLAGS)
LDFLAGS = -s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME="createWormWorxModule" --bind

CPP_SOURCES = cpp/wormworx.cpp cpp/wormsim.cpp
C_SOURCES = cpp/sundials-2.3.0/src/ida/ida.c \
            cpp/sundials-2.3.0/src/ida/ida_band.c \
            cpp/sundials-2.3.0/src/ida/ida_bbdpre.c \
            cpp/sundials-2.3.0/src/ida/ida_dense.c \
            cpp/sundials-2.3.0/src/ida/ida_ic.c \
            cpp/sundials-2.3.0/src/ida/ida_io.c \
            cpp/sundials-2.3.0/src/ida/ida_spbcgs.c \
            cpp/sundials-2.3.0/src/ida/ida_spgmr.c \
            cpp/sundials-2.3.0/src/ida/ida_spils.c \
            cpp/sundials-2.3.0/src/ida/ida_sptfqmr.c \
            cpp/sundials-2.3.0/src/nvec_ser/fnvector_serial.c \
            cpp/sundials-2.3.0/src/nvec_ser/nvector_serial.c \
            cpp/sundials-2.3.0/src/sundials/sundials_band.c \
            cpp/sundials-2.3.0/src/sundials/sundials_dense.c \
            cpp/sundials-2.3.0/src/sundials/sundials_iterative.c \
            cpp/sundials-2.3.0/src/sundials/sundials_math.c \
            cpp/sundials-2.3.0/src/sundials/sundials_nvector.c \
            cpp/sundials-2.3.0/src/sundials/sundials_smalldense.c \
            cpp/sundials-2.3.0/src/sundials/sundials_spbcgs.c \
            cpp/sundials-2.3.0/src/sundials/sundials_spgmr.c \
            cpp/sundials-2.3.0/src/sundials/sundials_sptfqmr.c

CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)
C_OBJECTS = $(C_SOURCES:.c=.o)
OBJECTS = $(CPP_OBJECTS) $(C_OBJECTS)

TARGET = output/wormworx.js

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	cp index.html output/index.html
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)