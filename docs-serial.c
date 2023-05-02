#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_DOCUMENTO 10000
#define MAX_ASSUNTO 50
#define MAX_ARMARIO 100

double documentos[MAX_DOCUMENTO][MAX_ASSUNTO];
int documentos_armarios[MAX_DOCUMENTO];
double media_armarios[MAX_ARMARIO][MAX_ASSUNTO];

double distancia(double *doc, double *armarios, int s)
{
    double dist = 0;
    for (int i = 0; i < s; i++)
    {
        dist += (doc[i] - armarios[i]) * (doc[i] - armarios[i]);
    }
    return dist;
}

void atribuicao_inicial(int d, int c)
{
    for (int i = 0; i < d; i++)
    {
        documentos_armarios[i] = i % c;
    }
}

void recalcula_media_armarios(int d, int c, int s)
{
    memset(media_armarios, 0, sizeof(media_armarios));
    int contagem[MAX_ARMARIO];
    memset(contagem, 0, sizeof(contagem));
    for (int i = 0; i < d; i++)
    {
        int armarios = documentos_armarios[i];
        contagem[armarios]++;
        for (int j = 0; j < s; j++)
        {
            media_armarios[armarios][j] += documentos[i][j];
        }
    }
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < s; j++)
        {
            media_armarios[i][j] /= contagem[i];
        }
    }
}

int recalcula_atribuicao(int d, int c, int s)
{
    int mudancas = 0;
    for (int i = 0; i < d; i++)
    {
        double *doc = documentos[i];
        double dist_min = INFINITY;
        int nova_armarios = -1;
        for (int j = 0; j < c; j++)
        {
            double dist = distancia(doc, media_armarios[j], s);
            if (dist < dist_min)
            {
                dist_min = dist;
                nova_armarios = j;
            }
        }
        if (documentos_armarios[i] != nova_armarios)
        {
            documentos_armarios[i] = nova_armarios;
            mudancas++;
        }
    }
    return mudancas;
}

int main()
{
    int armarios, docs, assuntos;
    scanf("%d %d %d", &armarios, &docs, &assuntos);

    for (int i = 0; i < docs; i++)
    {
        int id;
        scanf("%d", &id);
        for (int j = 0; j < assuntos; j++)
        {
            scanf("%lf", &documentos[id][j]);
        }
    }

    atribuicao_inicial(docs, armarios);
    int mudancas = 1;
    while (mudancas > 0)
    {
        recalcula_media_armarios(docs, armarios, assuntos);
        mudancas = recalcula_atribuicao(docs, armarios, assuntos);
    }

    for (int i = 0; i < docs; i++)
    {
        printf("%d %d\n", i, documentos_armarios[i]);
    }

   

    return 0;
}
