# Instalação - Receitas de Mainha

Guia pra rodar o jogo no Linux/WSL.

## 1. Instalar dependências do sistema

```bash
sudo apt update
sudo apt install build-essential git pkgconf \
  libasound2-dev libx11-dev libxrandr-dev libxi-dev \
  libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \
  libxinerama-dev libwayland-dev libxkbcommon-dev
```

## 2. Baixar e compilar o Raylib

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
sudo ldconfig
```

## 3. Verificar instalação

```bash
ls /usr/local/include/raylib.h
ls /usr/local/lib/libraylib*
```

Se os dois comandos listarem os arquivos, o Raylib está instalado.

## 4. Compilar o jogo

Dentro da pasta do projeto:

```bash
gcc main.c jogo.c receitas.c estruturas/pilha.c -o jogo.exe \
    -lraylib -lm -lpthread -ldl -lrt -lX11
```

## 5. Executar

```bash
./jogo.exe
```

## Aviso pra usuários de WSL

Se você está no **Windows 11 com WSL2**, a janela do jogo abre automaticamente (WSLg).

Se está no **Windows 10 com WSL2**, precisa instalar um servidor gráfico tipo VcXsrv antes do jogo abrir a janela.