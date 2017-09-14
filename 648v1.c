/* @JUDGE_ID:  3677NT  648  C  */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int process(void);

int main(void)
{
        processa();

        return 0;
}

#define MAX_SELOS 25

unsigned int selos[MAX_SELOS] = {0};
unsigned int nselos = 0;
unsigned int indice[4] = {0,0,0,0};

unsigned int resposta[4] = {0,0,0,0};
unsigned int resposta_nselos = 0;
unsigned int resposta_ndifs = 0;
unsigned int resposta_empate = 0;

unsigned int requisicao=0;

#ifdef DEBUG
void mostra_vetor(char *nome, unsigned int vetor[], unsigned int tam)
{
        unsigned int i;
        printf("%s: ",nome);
        for(i=0;i<tam;i++) printf("%d ",vetor[i]);
        printf("\n");
}
#endif

unsigned int leselos(void)
{
        unsigned int numero;

        for(nselos=0; nselos<=MAX_SELOS; nselos++) {
                if(scanf("%d", &numero)!=1) return nselos;
                if (numero==0)
                        return nselos;
                selos[nselos]=numero;
        }
#ifdef DEBUG
        printf("erro lendo selos");
#endif
        exit(1);
        return nselos;
}

unsigned int diferentes(unsigned int vetor[], unsigned int n)
{
        unsigned int a,b,c,d;
        a=b=c=d=1;

        switch(n) {
                case 1: return 1;
                case 2:
                        {
                                if(vetor[0]==vetor[1]) return 1;
                                return 2;
                        }
                case 3:
                        {
                                if(vetor[0]==vetor[1]) a++;
                                if(vetor[0]==vetor[2]) a++;
                                if(a==3) return 1;
                                if(vetor[1]==vetor[2]) b++;
                                if(a+b==3) return 2;
                                if(a+b+c==3) return 3;
                        }

                case 4:
                        {
                                if(vetor[0]==vetor[1]) a++;
                                if(vetor[0]==vetor[2]) a++;
                                if(vetor[0]==vetor[3]) a++;
                                if(a==4) return 1;
                                if(vetor[1]==vetor[2]) b++;
                                if(vetor[1]==vetor[3]) b++;
                                if(a+b==4) return 2;
                                if(vetor[2]==vetor[3]) c++;
                                if(a+c==4) return 2;
                                if(a+b+c==4) return 3;
                                if(a+b+c+d==4) return 4;
                        }
        }
        return 0;
}

unsigned int soma_selos_indice(unsigned int n)
{
        unsigned int i,s=0;
        for(i=0;i<n;i++) s+=selos[indice[i]];
        return s;
}

void guarda_resposta(unsigned int n, unsigned int difs)
{
        resposta_nselos=n;
        resposta_ndifs=difs;

        resposta[0]=indice[0];
        resposta[1]=indice[1];
        resposta[2]=indice[2];
        resposta[3]=indice[3];

}

unsigned int maior_selo(unsigned int vetor[], unsigned int tam)
{
        unsigned int i,m=0;
        for(i=0;i<tam;i++)
                if(m<selos[vetor[i]])
                        m=selos[vetor[i]];
        return m;
}

int verifica_resposta (unsigned int n)
{
        unsigned int difs, soma, m1,m2;

        /* primeiro criterio */
        soma = soma_selos_indice(n);
#ifdef DEBUG
        mostra_vetor("indice",indice,n);
        printf("soma: %d\n",soma);
#endif
        if(soma!=requisicao)
                return -1;

        /* segundo criterio nro de selos diferentes */
        difs = diferentes(indice,n);
#ifdef DEBUG
        printf("difs: %d\n",difs);
#endif
        if (difs<resposta_ndifs)
                return -2;
        if (difs>resposta_ndifs) {
                /* resposta eh melhor */
                guarda_resposta(n,difs);
                resposta_empate=0;
                return 1;
        }
        /* empatou nro de selos diferentes */

        /* primeiro desempate: menor qtde de selos */
        if(resposta_nselos<n) return -3;
        if(resposta_nselos>n) {
                /* nova tem menor nro de selos */
                guarda_resposta(n,difs);
                resposta_empate=0;
                return 2;
        }
        /* empatou em nro de selos */

        /* segundo desempate: conjunto com maior valor individual */
        m1=maior_selo(indice,n);
        m2=maior_selo(resposta,resposta_nselos);
#ifdef DEBUG
        printf("maior selo indice [%d] resposta [%d]\n", m1, m2);
#endif
        if (m1>m2) {
                /* nova resposta tem o elemento de maior valor */
                guarda_resposta(n,difs);
                resposta_empate=0;
                return 3;
        }
        if (m1<m2) {
                /* resposta ja tem o elemento de maior valor */
                return -5;
        }
        /* realmente empatou! */
#ifdef DEBUG
        printf("empate\n");
#endif
        resposta_empate=1;
        return 6;
}

void encontra_resposta()
{
        for(indice[0]=0;indice[0]<nselos;indice[0]++) {
                if(resposta_ndifs < 2) verifica_resposta(1);
                for(indice[1]=indice[0];indice[1]<nselos;indice[1]++){
                        if(resposta_ndifs < 3) verifica_resposta(2);
                        for(indice[2]=indice[1];indice[2]<nselos;indice[2]++){
                                if(resposta_ndifs < 4) verifica_resposta(3);
                                for(indice[3]=indice[2];indice[3]<nselos;indice[3]++){
                                        verifica_resposta(4);
                                }
                        }
                }
        }

        if(resposta_nselos==0) {
                printf("%d ---- none\n", requisicao);
        } else if (resposta_empate) {
                printf("%d (%d): tie\n", requisicao, resposta_ndifs);
        } else {
                unsigned int i;
                printf("%d (%d):", requisicao, resposta_ndifs);
                for(i=0;(i<resposta_nselos)&&(selos[resposta[i]]!=0);i++)
                        printf(" %d", selos[resposta[i]]);
                printf("\n");
        }
}

void zera_resposta(void)
{
        memset(resposta,0,sizeof(resposta));
        resposta_nselos = 0;
        resposta_ndifs = 0;
        resposta_empate = 0;
}

int processa(void)
{

        while(1) {
                leselos();
                if (nselos==0) return 0;
#ifdef DEBUG
                printf("nselos=%d\n",nselos);
                mostra_vetor("selos",selos,nselos);
#endif
                do {
                        zera_resposta();
                        if(scanf("%d", &requisicao)!=1) return 0;
#ifdef DEBUG
                        printf("requisicao=%d\n",requisicao);
#endif
                        if (requisicao>0)
                                encontra_resposta();
                } while(requisicao);
        }
}
