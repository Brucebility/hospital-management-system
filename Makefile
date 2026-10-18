# 医院病人管理系统 - MinGW/GCC 构建脚本
# 用法：mingw32-make        编译
#       mingw32-make run    编译并运行
#       mingw32-make clean  清理

CC      = gcc
CFLAGS  = -O2 -Wall
TARGET  = build/hospital.exe
SRC     = src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	@if not exist build mkdir build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	$(TARGET)

clean:
	@if exist build rmdir /s /q build

.PHONY: all run clean
