.PHONY: all build clean test examples format lint help

# Цель по умолчанию
all: build

# Сборка проекта
build:
	@echo "Building project..."
	@mkdir -p build && cd build && \
	 cmake .. && \
	 cmake --build .

# Очистка
clean:
	@echo "Cleaning..."
	@rm -rf build/
	@rm -rf install/

# Запуск тестов
test: build
	@echo "Running tests..."
	@cd build && ctest --output-on-failure

# Запуск примеров
examples: build
	@echo "Running examples..."
	@for ex in build/examples/*; do \
		if [ -x "$$ex" ]; then \
			echo "Running $$ex..."; \
			"$$ex"; \
		fi \
	done

# Справка
help:
	@echo "Available targets:"
	@echo "  all      - Build everything (default)"
	@echo "  build    - Build the project"
	@echo "  clean    - Remove build artifacts"
	@echo "  test     - Run tests"
	@echo "  examples - Run examples"
	@echo "  help     - Show this help"