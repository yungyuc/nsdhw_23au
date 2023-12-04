CXX = g++
MKL_INCLUDE_DIR = /usr/include/mkl
CXXFLAGS = -O2 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags` 
LDFLAGS = -lmkl_rt
LIBS = ./_matrix$(shell python3-config --extension-suffix)

all: $(LIBS)

$(LIBS): matrix.cpp mod.cpp
	$(CXX) $(CXXFLAGS) -I$(MKL_INCLUDE_DIR) $^ -o $@ $(LDFLAGS)

test: $(LIBS)
	python3 -m pytest -v

clean:
	rm -rf *.o *.so .pytest_cache __pycache__
