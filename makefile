CC     = gcc
SRCS   = main.c jogo.c receitas.c estruturas/pilha.c groq.c
TARGET = sabores
LIBS   = -lraylib -lm -lpthread -ldl -lrt -lX11 -lcurl

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)