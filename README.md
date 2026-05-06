# Jogo AED 🎮

# Receitas de Mainha

Jogo interativo em linguagem **C** sobre as comidas típicas do Recife. O jogador entra na pele de um aprendiz de cozinheiro que, com a ajuda de sua mainha, se prepara para uma competição gastronômica regional cuja final acontece no **Marco Zero**.

Inspirado em *Cooking Mama*, o jogo desafia o jogador a preparar pratos como **Bolo de Rolo**, **Tapioca** e **Sururu** seguindo a ordem correta dos passos e respeitando o tempo de cada etapa.

---

## Vibe recifense

A ambientação celebra a culinária pernambucana e a cultura popular de Recife. A fase final se passa no **Marco Zero**, ponto turístico mais simbólico da cidade, onde os jurados avaliam o desempenho do jogador na grande final.

---

## Sobre o jogo

**Público-alvo:** jogadores iniciantes e casuais.

**Narrativa:** o personagem principal decide entrar em uma competição de comidas típicas e treina com a ajuda de sua mainha. A cada fase, uma nova receita regional precisa ser dominada; ao final, figuras icônicas avaliam os pratos numa etapa decisiva no Marco Zero.

**Objetivo:** aprender todas as receitas, acumular boa pontuação e vencer a competição final (desempenho mínimo de 70%).

---

## Mecânica principal

O coração da jogabilidade é uma **pilha (LIFO)**. Cada receita é representada como uma sequência de passos empilhados; o jogador deve sempre executar o passo que está **no topo** da pilha. Acertou? `pop` — o próximo passo aparece. Errou ou estourou o tempo? Penalidade na pontuação.

Quando a pilha esvazia, o prato está pronto e a fase termina.

---

## Estruturas de dados

### Pilha (estrutura central)

A pilha é a estrutura **principal** do jogo, responsável por organizar os passos das receitas. O jogador "navega pela pilha" enquanto cozinha: cada execução correta de um passo dispara um `pop`, e o jogo só avança quando toda a pilha é consumida na ordem certa. Essa escolha se justifica porque o preparo de uma receita tem ordem rígida (LIFO casa naturalmente com o conceito de "última etapa empilhada é a próxima a ser feita" quando as receitas são carregadas de trás para frente).

### Lista encadeada

Duas listas encadeadas dão suporte ao jogo:

- **Lista de receitas disponíveis** — o jogador percorre essa lista para escolher qual prato vai preparar.
- **Lista de ingredientes** — cada receita possui sua própria lista de ingredientes coletados antes do preparo.

## Algoritmos de ordenação

- **Insertion Sort** (principal) — organiza os ingredientes coletados pelo jogador, que entram desordenados e precisam ser arrumados antes do preparo.
- **Bubble Sort** (auxiliar) — ordena as receitas pelo nível de dificuldade, ajudando o jogador a escolher por onde começar. A escolha se justifica pela simplicidade e por ser adequado a conjuntos pequenos de dados.

---
  

## Inteligência Artificial na dinâmica

O jogo utiliza a **API da OpenAI** para simular os jurados da competição final. A IA avalia o desempenho do jogador considerando a ordem dos passos executados, o tempo gasto em cada etapa e a quantidade de erros, retornando uma **nota** e um **feedback textual** personalizado para cada partida.

---
## Como compilar e executar


## Equipe

- Marília Liz Alves
- Victor Martins
- Louise Pessoa
- Pedro David Oliveira
- Mateus Lins



---

*Projeto desenvolvido como atividade prática da disciplina de Estruturas de Dados.*
