#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "groq.h"

/* -------------------------------------------------------------------------
 * Constantes
 * ---------------------------------------------------------------------- */
#define GROQ_ENDPOINT   "https://api.groq.com/openai/v1/chat/completions"
#define GROQ_MODEL      "llama3-70b-8192"
#define GROQ_MAX_TOKENS 300
#define BUFFER_SIZE     8192
#define BODY_SIZE       4096

/* -------------------------------------------------------------------------
 * Buffer dinamico acumulado pelo callback do cURL
 * ---------------------------------------------------------------------- */
typedef struct {
    char  *dados;
    size_t tamanho;
} BufferResposta;

/* Callback chamado pelo cURL a cada chunk recebido; acumula em BufferResposta */
static size_t callback_escrita(void *conteudo, size_t tamanho,
                               size_t nmemb, void *userdata)
{
    size_t bytes_novos = tamanho * nmemb;
    BufferResposta *buf = (BufferResposta *)userdata;

    char *novo = realloc(buf->dados, buf->tamanho + bytes_novos + 1);
    if (!novo) return 0; /* sinaliza falha ao cURL */

    buf->dados = novo;
    memcpy(buf->dados + buf->tamanho, conteudo, bytes_novos);
    buf->tamanho += bytes_novos;
    buf->dados[buf->tamanho] = '\0';
    return bytes_novos;
}

/* -------------------------------------------------------------------------
 * Prompts de sistema — um por jurado
 *
 * Cada prompt instrui o modelo a adotar a personalidade do jurado, avaliar
 * com base nos indices numericos recebidos e responder SOMENTE em JSON.
 * ---------------------------------------------------------------------- */
static const char *PROMPT_ARIANO =
    "Voce e Ariano Suassuna, jurado simpatico de um concurso culinario nordestino. "
    "Avalie o desempenho do jogador com base em dois indices numericos fornecidos: "
    "aproveitamento (fracao de 0 a 1, indica quantos passos da receita foram acertados) e "
    "pontuacao_relativa (fracao de 0 a 1, onde 1 e perfeito e valores baixos indicam erros). "
    "Voce prioriza o aproveitamento: se o jogador completou a receita com cuidado e dedicacao, "
    "merece nota alta mesmo com alguns erros de tempo. "
    "Calcule sua nota de 0 a 10 (pode usar uma casa decimal) refletindo esses indices. "
    "Escreva um comentario em portugues, no maximo 2 frases, no seu estilo poetico e caloroso. "
    "Responda SOMENTE com JSON neste formato exato, sem nenhum outro texto: "
    "{\"nota\": 7.5, \"comentario\": \"texto aqui\"}";

static const char *PROMPT_CLARICE =
    "Voce e Clarice Lispector, jurada exigente de um concurso culinario. "
    "Avalie o desempenho do jogador com base em dois indices numericos fornecidos: "
    "aproveitamento (fracao de 0 a 1, indica quantos passos da receita foram acertados) e "
    "pontuacao_relativa (fracao de 0 a 1, onde 1 e perfeito e valores baixos indicam erros). "
    "Voce prioriza a pontuacao_relativa: erros e excesso de tempo sao imperdoaveis. "
    "Abaixo de 0.7 a nota e baixa (0-5), entre 0.7 e 0.9 e media (5-8), acima de 0.9 e excelente (8-10). "
    "Calcule sua nota de 0 a 10 (pode usar uma casa decimal) refletindo esses indices. "
    "Escreva um comentario em portugues, no maximo 2 frases, no seu estilo introspectivo e exigente. "
    "Responda SOMENTE com JSON neste formato exato, sem nenhum outro texto: "
    "{\"nota\": 7.5, \"comentario\": \"texto aqui\"}";

static const char *PROMPT_CHICO =
    "Voce e Chico Science, jurado criativo e inovador de um concurso culinario. "
    "Avalie o desempenho do jogador com base em dois indices numericos fornecidos: "
    "aproveitamento (fracao de 0 a 1, indica quantos passos da receita foram acertados) e "
    "pontuacao_relativa (fracao de 0 a 1, onde 1 e perfeito e valores baixos indicam erros). "
    "Voce prioriza criatividade e ousadia: se pontuacao_relativa >= 0.9 E aproveitamento >= 0.8, "
    "o jogador foi alem do basico e merece nota maxima (9-10). "
    "Se apenas um criterio for alto, a nota fica entre 6-8. Se ambos forem baixos, cai para 0-5. "
    "Calcule sua nota de 0 a 10 (pode usar uma casa decimal) refletindo esses indices. "
    "Escreva um comentario em portugues, no maximo 2 frases, no seu estilo mangue beat energico. "
    "Responda SOMENTE com JSON neste formato exato, sem nenhum outro texto: "
    "{\"nota\": 7.5, \"comentario\": \"texto aqui\"}";

/* -------------------------------------------------------------------------
 * chamar_groq()
 *
 * Faz POST para a API do Groq com o prompt do jurado e a mensagem do usuario.
 * Extrai o campo "content" da resposta e grava em `saida`.
 * Retorna 0 em sucesso, -1 em falha.
 * ---------------------------------------------------------------------- */
static int chamar_groq(const char *chave_api,
                       const char *prompt_sistema,
                       const char *mensagem_usuario,
                       char *saida, size_t tamanho_saida)
{
    CURL *curl;
    CURLcode res;
    int sucesso = -1;

    BufferResposta buf;
    buf.dados   = malloc(1);
    buf.tamanho = 0;
    if (!buf.dados) return -1;
    buf.dados[0] = '\0';

    curl = curl_easy_init();
    if (!curl) {
        free(buf.dados);
        return -1;
    }

    /* Monta o corpo JSON da requisicao */
    char corpo[BODY_SIZE];
    snprintf(corpo, sizeof(corpo),
        "{"
          "\"model\":\"%s\","
          "\"max_tokens\":%d,"
          "\"messages\":["
            "{\"role\":\"system\",\"content\":\"%s\"},"
            "{\"role\":\"user\",\"content\":\"%s\"}"
          "]"
        "}",
        GROQ_MODEL, GROQ_MAX_TOKENS,
        prompt_sistema,
        mensagem_usuario);

    /* Headers obrigatorios para a API do Groq (formato OpenAI) */
    struct curl_slist *headers = NULL;
    char auth_header[512];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", chave_api);
    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL,          GROQ_ENDPOINT);
    curl_easy_setopt(curl, CURLOPT_POST,          1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,    corpo);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER,    headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_escrita);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &buf);
    /* Timeout para nao travar o jogo em caso de rede lenta */
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,       30L);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "[groq] curl falhou: %s\n", curl_easy_strerror(res));
        goto cleanup;
    }

    /* A API retorna JSON no padrao OpenAI:
     *   {"choices":[{"message":{"content":"...JSON do jurado..."}}]}
     * Localizamos "content" e extraimos o valor entre aspas. */
    {
        const char *marca = "\"content\":";
        char *ptr = strstr(buf.dados, marca);
        if (!ptr) {
            fprintf(stderr, "[groq] 'content' nao encontrado na resposta\n");
            goto cleanup;
        }
        ptr += strlen(marca);

        /* Pula espacos e a aspas de abertura */
        while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') ptr++;
        if (*ptr != '"') goto cleanup;
        ptr++;

        /* Copia o valor respeitando aspas escapadas (\") */
        size_t i = 0;
        while (*ptr && i < tamanho_saida - 1) {
            if (*ptr == '\\' && *(ptr + 1) == '"') {
                saida[i++] = '"';
                ptr += 2;
            } else if (*ptr == '"') {
                break;
            } else {
                saida[i++] = *ptr++;
            }
        }
        saida[i] = '\0';
        sucesso = 0;
    }

cleanup:
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(buf.dados);
    return sucesso;
}

/* -------------------------------------------------------------------------
 * extrair_nota_comentario()
 *
 * Parseia {"nota": X.X, "comentario": "texto"} sem biblioteca JSON externa.
 * Retorna 0 em sucesso, -1 se o formato for invalido.
 * ---------------------------------------------------------------------- */
static int extrair_nota_comentario(const char *json,
                                   float *nota,
                                   char  *comentario,
                                   size_t tam)
{
    if (!json || !*json) return -1;

    /* Extrai nota: localiza a chave e le o float apos o ':' */
    const char *ptr = strstr(json, "\"nota\"");
    if (!ptr) return -1;
    ptr += strlen("\"nota\"");
    while (*ptr && *ptr != ':') ptr++;
    if (!*ptr) return -1;
    ptr++;
    if (sscanf(ptr, " %f", nota) != 1) return -1;

    /* Extrai comentario: localiza a chave, avanca ate o valor entre aspas */
    ptr = strstr(json, "\"comentario\"");
    if (!ptr) { comentario[0] = '\0'; return 0; }
    ptr += strlen("\"comentario\"");
    while (*ptr && *ptr != ':') ptr++;
    if (!*ptr) { comentario[0] = '\0'; return 0; }
    ptr++;

    while (*ptr == ' ' || *ptr == '\t') ptr++;
    if (*ptr != '"') { comentario[0] = '\0'; return 0; }
    ptr++;

    size_t i = 0;
    while (*ptr && i < tam - 1) {
        if (*ptr == '\\' && *(ptr + 1) == '"') {
            comentario[i++] = '"';
            ptr += 2;
        } else if (*ptr == '"') {
            break;
        } else {
            comentario[i++] = *ptr++;
        }
    }
    comentario[i] = '\0';
    return 0;
}

/* -------------------------------------------------------------------------
 * avaliar_com_jurados()
 *
 * Funcao publica. Chama os 3 jurados em sequencia, coleta as respostas,
 * parseia os JSONs e retorna a struct ResultadoJurados preenchida.
 * ---------------------------------------------------------------------- */
ResultadoJurados avaliar_com_jurados(EstadoJogo estado)
{
    ResultadoJurados resultado;
    memset(&resultado, 0, sizeof(resultado));

    const char *chave = getenv("GROQ_API_KEY");
    if (!chave || chave[0] == '\0') {
        fprintf(stderr, "[groq] GROQ_API_KEY nao definida — jurados indisponiveis\n");
        return resultado;
    }

    /* Calcula os indices de desempenho uma unica vez */
    float aproveitamento = (estado.passos_total > 0)
                           ? (float)estado.passos_acertados / (float)estado.passos_total
                           : 0.0f;
    float pontuacao_rel  = (float)estado.pontuacao / 100.0f;

    /* Mensagem enviada para todos os jurados com os indices numericos */
    char mensagem[512];
    snprintf(mensagem, sizeof(mensagem),
        "Aproveitamento: %.2f (%.0f%% dos passos corretos). "
        "Pontuacao relativa: %.2f (pontuacao bruta=%d de 100).",
        aproveitamento, aproveitamento * 100.0f,
        pontuacao_rel, estado.pontuacao);

    char resposta[BUFFER_SIZE];

    /* --- Ariano Suassuna --- */
    memset(resposta, 0, sizeof(resposta));
    if (chamar_groq(chave, PROMPT_ARIANO, mensagem, resposta, sizeof(resposta)) == 0)
        extrair_nota_comentario(resposta, &resultado.nota_ariano,
                                resultado.comentario_ariano, 256);

    /* --- Clarice Lispector --- */
    memset(resposta, 0, sizeof(resposta));
    if (chamar_groq(chave, PROMPT_CLARICE, mensagem, resposta, sizeof(resposta)) == 0)
        extrair_nota_comentario(resposta, &resultado.nota_clarice,
                                resultado.comentario_clarice, 256);

    /* --- Chico Science --- */
    memset(resposta, 0, sizeof(resposta));
    if (chamar_groq(chave, PROMPT_CHICO, mensagem, resposta, sizeof(resposta)) == 0)
        extrair_nota_comentario(resposta, &resultado.nota_chico,
                                resultado.comentario_chico, 256);

    resultado.media_final = (resultado.nota_ariano +
                             resultado.nota_clarice +
                             resultado.nota_chico) / 3.0f;
    return resultado;
}