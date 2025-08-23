# Ім'я програми
TARGET = main

# Файли з кодом
SRC = main.cpp

# Компилятор
CC = gcc

# Опції компілятора
CFLAGS = -I/opt/homebrew/include -std=c++17
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit

# Правило для збірки
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Очистка (видалення скомпільованих файлів)
clean:
	rm -f $(TARGET)
