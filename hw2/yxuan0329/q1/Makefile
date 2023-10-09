CXX = g++
CFLAG = -std=c++17


run: *.cpp
	$(CXX) *.cpp $(CFLAG) && ./a.out

check: *.cpp
	$(CXX) *.cpp $(CFLAG) && ./a.out > result.txt

clean:
	rm -rf *.o *.out *.txt
