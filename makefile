CC     = gcc
SRCS   = main.c jogo.c receitas.c estruturas/pilha.c groq.c catcher.c cozinhar.c interface.c ordenacao.c
TARGET = sabores

# Detecta o sistema operacional
UNAME_S := $(shell uname -s)

# Tenta obter configurações do raylib via pkg-config
RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell pkg-config --libs raylib 2>/dev/null)

# Se pkg-config falhar, usa configuração padrão por SO
ifeq ($(RAYLIB_LIBS),)
	# Linux padrão
	CFLAGS = -I/usr/include
	LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11 -lcurl
	
	# macOS
	ifeq ($(UNAME_S),Darwin)
		CFLAGS = -I/opt/homebrew/include -I/usr/local/include
		LIBS = -L/opt/homebrew/lib -L/usr/local/lib -lraylib -lm -lpthread -lcurl
	endif
else
	# Usa pkg-config
	CFLAGS = $(RAYLIB_CFLAGS)
	LIBS = $(RAYLIB_LIBS) -lm -lpthread -lcurl
	
	# Remove flags específicas do Linux se estiver no macOS
	ifeq ($(UNAME_S),Darwin)
		LIBS := $(filter-out -ldl -lrt -lX11,$(LIBS))
	endif
endif

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)