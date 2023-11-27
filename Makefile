# Definição do diretório de build
BUILD_DIR = ./build

.PHONY: all setup build clean run

# Alvo padrão
all: setup build

# Configurar o projeto
setup:
	rm -rf $(BUILD_DIR)
	conan install .. --output-folder=$(BUILD_DIR) --build=missing

# Construir o projeto
build:
	cd $(BUILD_DIR) && \
	cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release && \
	cmake --build .

# Executar a aplicação
run:
	$(BUILD_DIR)/brasil-api

# Limpar arquivos de build
clean:
	rm -rf $(BUILD_DIR)
