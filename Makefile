# Makefile for Conway's Game of Life

# 設定編譯器
CXX = mpic++
# 設定編譯選項
CXXFLAGS = -Wall -std=c++11

# 目標執行文件名稱
TARGET = test

# 來源文件
SOURCES = test.cpp

# 預設目標
all: $(TARGET)

# 編譯規則
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# 清理目標
clean:
	rm -f $(TARGET)

# phony目標，不與文件名衝突
.PHONY: all clean
