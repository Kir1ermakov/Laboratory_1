CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
LDFLAGS = -lstdc++

SRC_DIR = src
OBJ_DIR = src
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(filter-out main.h, $(SRC:.cpp=.h))

OBJS_SEQ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.seq.o, $(SRCS))
TARGET_SEQ = run_seq

OBJS_PAR = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.par.o, $(SRCS))
TARGET_PAR = run_par
OPENMP_FLAGS = -fopenmp

IMAGEB_OBJ_SEQ = $(OBJ_DIR)/imageB.seq.o
IMAGEB_OBJ_PAR = $(OBJ_DIR)/imageB.par.o
BENCHMARK_SEQ = benchmark_seq

TESTS_SEQ = tests_seq
TESTS_PAR = tests_par
GTEST_LIBS = -lgtest -lpthread

all: $(TARGET_SEQ) $(TARGET_PAR) benchmark

# Последовательная версия
$(TARGET_SEQ): $(OBJS_SEQ)
	$(CXX) $(CXXFLAGS) $(OBJS_SEQ) -o $(TARGET_SEQ) $(LDFLAGS)

$(OBJ_DIR)/%.seq.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_PAR): $(OBJS_PAR)
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) $(OBJS_PAR) -o $(TARGET_PAR) $(LDFLAGS) $(OPENMP_FLAGS)

$(OBJ_DIR)/%.par.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) -DUSE_OPENMP -c $< -o $@

$(IMAGEB_OBJ_SEQ): $(SRC_DIR)/imageB.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/imageB.cpp -o $(IMAGEB_OBJ_SEQ)

$(IMAGEB_OBJ_PAR): $(SRC_DIR)/imageB.cpp
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) -DUSE_OPENMP -c $(SRC_DIR)/imageB.cpp -o $(IMAGEB_OBJ_PAR)

$(BENCHMARK_SEQ): benchmark.cpp $(IMAGEB_OBJ_SEQ)
	$(CXX) $(CXXFLAGS) benchmark.cpp $(IMAGEB_OBJ_SEQ) -o $(BENCHMARK_SEQ) $(LDFLAGS)

$(BENCHMARK_PAR): benchmark.cpp $(IMAGEB_OBJ_PAR)
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) -DUSE_OPENMP benchmark.cpp $(IMAGEB_OBJ_PAR) -o $(BENCHMARK_PAR) $(LDFLAGS) $(OPENMP_FLAGS)

benchmark: $(BENCHMARK_SEQ) $(BENCHMARK_PAR)

$(TESTS_SEQ): $(TEST_DIR)/test_imageB.cpp $(IMAGEB_OBJ_SEQ)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_imageB.cpp $(IMAGEB_OBJ_SEQ) -o $(TESTS_SEQ) $(GTEST_LIBS)

$(TESTS_PAR): $(TEST_DIR)/test_imageB.cpp $(IMAGEB_OBJ_PAR)
	$(CXX) $(CXXFLAGS) $(OPENMP_FLAGS) -DUSE_OPENMP $(TEST_DIR)/test_imageB.cpp $(IMAGEB_OBJ_PAR) -o $(TESTS_PAR) $(GTEST_LIBS) $(OPENMP_FLAGS)

.PHONY: test
test: $(TESTS_SEQ) $(TESTS_PAR)
	./$(TESTS_SEQ)
	./$(TESTS_PAR)

format:
	astyle -A1 -s4 $(SRCS) $(HEADERS)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET_SEQ) $(TARGET_PAR) $(BENCHMARK_SEQ) $(BENCHMARK_PAR) $(TESTS_SEQ) $(TESTS_PAR) $(OBJ_DIR)/*.orig

.PHONY: all clean format benchmark
