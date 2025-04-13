PROGRAM=SimpleApp
CC=x86_64-w64-mingw32-gcc
CXX=x86_64-w64-mingw32-g++
WX_PREFIX=/usr/local/wxwidgets-mingw64

CXXFLAGS=`$(WX_PREFIX)/bin/wx-config --cxxflags --libs`

objects=SimpleApp.o

all: $(PROGRAM)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(PROGRAM): $(objects)
	$(CXX) $^ $(CXXFLAGS) -static -static-libgcc -static-libstdc++ `$(WX_PREFIX)/bin/wx-config --libs` -o $@.exe 

clean:
	rm -f $(PROGRAM).exe $(objects)
