CXX=g++
CXXFLAGS=-std=c++17 -Og -mtune=native -march=native -flto -pipe -fPIC
LDFLAGS=

all: main CP866enc
	$(CXX) $(CXXFLAGS) ./build/*.o -o main.run $(LDFLAGS)
	strip ./main.run
	./main.run
CP866enc:
	$(CXX) $(CXXFLAGS) -I./src/CP866enc \
			   -c src/CP866enc/CP866enc.cpp \
			   -o build/CP866enc.o
main:
	$(CXX) $(CXXFLAGS) -I./src/CP866enc \
			   -c main.cpp \
			   -o build/main.o
clean:
	rm -rf ./build/*.o main.run log.log report.tasks strace_out
