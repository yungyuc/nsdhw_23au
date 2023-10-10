CXX = g++	# compiler
CXXFLAGS = -std=c++17 -Wall
TARGET = Line
RESULT = result.txt


$(TARGET): $(TARGET).cpp $(TARGET).hpp
	$(CXX) $(CXXFLAGS) $< -o $@
# When a source file changes, make needs to pick it up and rebuild.

.PHONY: run
run: $(TARGET)
	./$(TARGET)
# make run needs to produce the correct terminal output, without crashing.

.PHONY: check
check:
	./$(TARGET) > $(RESULT)
# make check redirects the terminal output to a file result.txt.

.PHONY: clean
clean:
	rm -rf $(TARGET) $(RESULT)
# make clean needs to remove all the built and intermediate files.
