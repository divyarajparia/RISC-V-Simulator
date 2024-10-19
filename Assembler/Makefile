CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = riscv_asm

SRC = ES22BTECH11013_LabAssgn3_Src.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
