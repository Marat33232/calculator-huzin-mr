CC = gcc
CXX = g++
CFLAGS = -Wall -Werror -std=c99
CXXFLAGS = -Wall -Werror -std=c++11
LDFLAGS = -lgtest -lgtest_main -pthread

# Исходные файлы
SRC = src/main.c
TEST_SRC = tests/unit/test_main.cpp

# Исходные объектные файлы
OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Артефакты
APP = build/app.exe
UNIT_TESTS = build/unit-tests.exe

# Правило для форматирования кода
clang-format:
	@echo "Running clang-format..."
	find . -regex '.*\.\(h\|c\|cpp\)$$' -exec clang-format -i {} +

# Правило для клонирования Google Test
clone-gtest:
	@if [ ! -d "googletest" ]; then \
		echo "Cloning googletest..."; \
		git clone https://github.com/google/googletest; \
	fi

# Правило для сборки Google Test
build-gtest: clone-gtest
	mkdir -p googletest/build && cd googletest/build && cmake .. && make

# Сборка программы
$(APP): $(OBJ)
	mkdir -p build
	$(CC) $(OBJ) -o $@

# Сборка юнит-тестов
$(UNIT_TESTS): $(TEST_OBJ) $(OBJ) build-gtest
	mkdir -p build
	$(CXX) $(TEST_OBJ) $(OBJ) -I googletest/googletest/include -L googletest/build/lib -lgtest -lgtest_main $(LDFLAGS) -o $@

# Компиляция C-файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция C++-файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка артефактов
clean:
	rm -rf build/ googletest/ *.o venv/

# Запуск программы
run-int:
	./$(APP)

run-float:
	./$(APP) --float

# Запуск юнит-тестов
run-unit-test:
	./$(UNIT_TESTS)

# Создание виртуального окружения Python
venv:
	python3 -m venv venv && . venv/bin/activate && pip install pytest

# Запуск интеграционных тестов
run-integration-tests:
	venv/bin/python -m pytest tests/integration/

# Сборка всех артефактов
all: $(APP) $(UNIT_TESTS)	clang-format

# Фиктивные цели
.PHONY:	all clean run-int run-float run-unit-test venv run-integration-tests clang-format build-gtest
