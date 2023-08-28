CC := gcc
DBFLAGS := -Wall -g3

# Diretórios de saída
OUTDIR := bin
OBJDIR := $(OUTDIR)/obj

CFLAGS := -march=native -O3

# Define as flags com base no sistema operacional
ifeq ($(OS), Windows_NT)
	CFLAGS += -lglfw3.dll -lglew32 -lopengl32

	# Nome do arquivo de saída para windows
	OUTFILE := $(SRC)
else
	UNAME := $(shell uname)
	ifeq ($(UNAME), Linux)
		CFLAGS += -lglfw -lGLEW -lGL -lm

		# Nome do arquivo de saída para linux
		OUTFILE := $(SRC)_linux
	endif
endif

# Nomes dos arquivos-fonte
SOURCES := $(SRC).c

# Criação dos nomes dos objetos com base no sistema operacional
ifeq ($(OS), Windows_NT)
	OBJFILES := $(patsubst %.c,$(OBJDIR)/win_%.o,$(SOURCES))
else
	UNAME := $(shell uname)
	ifeq ($(UNAME), Linux)
		OBJFILES := $(patsubst %.c,$(OBJDIR)/linux_%.o,$(SOURCES))
	endif
endif

run: $(OUTDIR)/$(OUTFILE)
	$(OUTDIR)/$(OUTFILE)

run_dbg: $(OUTDIR)/$(OUTFILE)_dbg
	$(OUTDIR)/$(OUTFILE)_dbg

# Alvo de compilação normal
release: $(OUTDIR) $(OBJDIR) $(OUTDIR)/$(OUTFILE)

# Alvo de compilação para depuração
debug: CFLAGS += $(DBFLAGS)
debug: $(OUTDIR) $(OBJDIR) $(OUTDIR)/$(OUTFILE)_dbg

# Cria diretório de saída se não existir
$(OUTDIR):
	mkdir -p $(OUTDIR)

# Cria diretório de objetos se não existir
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Regra de compilação de objetos para Windows
$(OBJDIR)/win_%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Regra de compilação de objetos para Linux
$(OBJDIR)/linux_%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Regra para compilar o executável final
$(OUTDIR)/$(OUTFILE): $(OBJFILES)
	$(CC) $^ -o $@ $(CFLAGS)

# Regra para compilar o executável de depuração
$(OUTDIR)/$(OUTFILE)_dbg: $(OBJFILES)
	$(CC) $^ -o $@ $(CFLAGS)

# Comando para limpar arquivos
clean:
	rm -rf $(OUTDIR)

.PHONY: release debug clean
