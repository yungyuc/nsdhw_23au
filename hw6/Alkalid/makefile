CXX = g++
CXXFLAGS = -O3 -m64 -Wall --shared -std=c++17 -fPIC \
		   `python3 -m pybind11 --includes` `python3-config --includes` \
		   -I/usr/include/mkl
LIBS = -L/usr/lib/x86_64-linux-gnu/mkl -lblas
TARGET = _matrix
TEST_FILE = test_matrix
DEFINE = -D PYBIND

all: %.so

%.so: $(TARGET).cpp
	$(CXX) $(CXXFLAGS) $(DEFINE) $^ -o $(TARGET)`python3-config --extension-suffix` $(LIBS)

test: %.so $(TEST_FILE).py
	python3 -m pytest -v

clean:
	rm -rf *.so __pycache__ .pytest* $(TARGET) performance.txt