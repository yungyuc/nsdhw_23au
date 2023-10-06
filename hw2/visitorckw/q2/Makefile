CXX = g++
CXXFLAGS = -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` `python3-config --includes --ldflags`
LIBS = ./_vector$(shell python3-config --extension-suffix)

all: $(LIBS)

$(LIBS): main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(LIBS)
	python3 -m pytest -v

clean:
	rm -f _vector
	rm -f *.so
	rm -rf __pycache__
	rm -rf .hypothesis
	rm -rf .pytest_cache
