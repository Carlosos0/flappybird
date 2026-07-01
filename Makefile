#______________________Definições para o makefile______________________
# Definições principais para o make compilar
CC = g++
CFLAGS = -std=c++14 -Wall -Wextra -g
INCLUDES = -Iinclude
LDFLAGS = 

# Verificar sistema operacional para mais definições importantes
#Os 3 S.O. possuem as mesmas variáveis aqui, portanto a explicação será apenas no primeiro
ifdef MSYSTEM #Windows com MSYS2 MinGW 64/Git 
	RM = rm -f #Excluir arquivos 	
	RM_DIR = rm -rf #Excluir diretórios 
	MK_DIR = mkdir -p #Criar diretórios 
	EXE_EXT = .exe #Extensão dos arquivos executáveis
	PATH_SEP = / #Separador de path
	SHELL_TYPE = msys #Tipo de shell 
else ifdef COMSPEC #Windows com Prompt ou PowerShell
	RM = del /Q
	RM_DIR = rmdir /S /Q
	MK_DIR = mkdir
	EXE_EXT = .exe
	PATH_SEP = \\
	SHELL_TYPE = windows
else #Linux/macOS
	RM = rm -f
	RM_DIR = rm -rf
	MK_DIR = mkdir -p
	EXE_EXT =
	PATH_SEP = /
	SHELL_TYPE = unix
endif

# Diretórios, vão ser universais para todos SO
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
INCLUDE_DIR = include

# Bibliotecas do Allegro (a ordem é importante para o windows principalmente até onde entendi)
ifeq ($(SHELL_TYPE),msys)
	# Windows/MSYS2 
	LIBS = -lallegro_main -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_audio 
else
	# Linux/macOS
	LIBS = -lallegro -lallegro_main -lallegro_image -lallegro_font -lallegro_ttf -lallegro_primitives -lallegro_audio 
endif

# Verificar se existe um arquivo main.cpp em src
MAIN_FILE = $(wildcard $(SRC_DIR)/main.cpp)
ifeq ($(MAIN_FILE),)
	$(error Erro: Nenhum arquivo main.cpp encontrado em $(SRC_DIR)/)
endif

# Aqui é o diferencial desse makefile, ele descobre os arquivos automáticamente
# Não sei como usaremos a pasta tests, mas ele procura tantos em tests como os de src
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

# Nome dos arquivos objetos, para os da pasta tests também
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Nome dos arquivos de dependência, diretamente na pasta obj
DEPS = $(OBJECTS:.o=.d) $(TEST_OBJECTS:.o=.d)

# Nome do dos executaveis finais, tanto de teste quanto de main
TARGET = $(BIN_DIR)/FlappyBird$(EXE_EXT)
TEST_TARGET = $(BIN_DIR)/test$(EXE_EXT)

# Regra padrão para ignorar esses termos
.PHONY: all help rebuild clean test run

# O que será executado caso seja realizado apenas o comando "make"
all: $(TARGET)

#______________________Regras para criar arquivos ou diretórios______________________
# Regra para criar o executável principal
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	@echo "Linkando $(TARGET)..."
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@
	@echo "Compilação bem-sucedida!"

# Regra para compilar arquivos .cpp em .o (com dependências)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MF $(OBJ_DIR)/$*.d -c $< -o $@

# Regra para compilar testes (com dependências)
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	@echo "Compilando teste $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -MF $(OBJ_DIR)/$*.d -c $< -o $@

# Garantir que diretórios existam
$(OBJ_DIR):
	@$(MK_DIR) $(OBJ_DIR) 2>/dev/null || true

$(BIN_DIR):
	@$(MK_DIR) $(BIN_DIR) 2>/dev/null || true

# Incluir arquivos de dependência 
-include $(DEPS)

# Compilar e executar testes (exclui main.cpp do link)
test: $(TEST_TARGET)
	@echo "Executando testes..."
	@./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS)) | $(BIN_DIR)
	@echo "Linkando executável de teste..."
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@

#______________________Comandos para se usar no Makefile______________________
# Executar o programa principal "make run"
run: $(TARGET)
	@echo "Executando $(TARGET)..."
	@./$(TARGET)

# Limpar arquivos compilados "make clean"
clean:
	@echo "Limpando..."
	@$(RM) $(OBJ_DIR)/*.o 2>/dev/null || true
	@$(RM) $(OBJ_DIR)/*.d 2>/dev/null || true
	@$(RM) $(TARGET) $(TEST_TARGET) 2>/dev/null || true
	@echo "Limpeza concluída!"

# Recompilar tudo do zero "make rebuild"
rebuild: clean all

# Compilar apenas sem executar "make build"
build: all

# Mostrar informações do sistema "make info"
info:
	@echo "Informações da Compilação:"
	@echo "  Compilador: $(CC)"
	@echo "  Flags: $(CFLAGS)"
	@echo "  Bibliotecas: $(LIBS)"
	@echo "  Tipo de Shell: $(SHELL_TYPE)"
	@echo "  Executável: $(TARGET)"
	@echo "  Arquivo main: $(MAIN_FILE)"
	@echo "  Arquivos fonte encontrados: $(words $(SOURCES)) arquivos"
	@echo "  Arquivos de teste encontrados: $(words $(TEST_SOURCES)) arquivos"

# Para mostrar ajudas "make help"
help:
	@echo "Comandos do Makefile:"
	@echo "  all/build - Compila o executável principal (padrão)"
	@echo "  run       - Compila e executa o executável principal"
	@echo "  test      - Compila e executa os testes"
	@echo "  clean     - Remove todos os arquivos compilados"
	@echo "  rebuild   - Limpa e compila tudo novamente"
	@echo "  info      - Mostra informações da compilação"
	@echo "  help      - Mostra esta mensagem de ajuda"
	@echo ""
	@echo "Estrutura do Projeto:"
	@echo "  src/      - Arquivos fonte (.cpp)"
	@echo "  include/  - Arquivos cabeçalho (.h/.hpp)"
	@echo "  obj/      - Arquivos objeto (.o) e dependências (.d) [criado automaticamente]"
	@echo "  bin/      - Arquivos executáveis [criado automaticamente]"
	@echo "  tests/    - Arquivos de teste (.cpp)"

# Debug: para mostrar variáveis "make debug"
debug:
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
	@echo "TEST_SOURCES: $(TEST_SOURCES)"
	@echo "TEST_OBJECTS: $(TEST_OBJECTS)"
	@echo "TARGET: $(TARGET)"
	@echo "SHELL_TYPE: $(SHELL_TYPE)"
	@echo "DEPS: $(DEPS)"