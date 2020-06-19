#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DIM 100
#define INF 999

typedef struct
{
    char *nume_pc;
    char *ip_pc;
    int stare;
} pc;

typedef struct
{
    char *nume_router;
    char *ip_router;
    int nr_pc;
    pc *calc;
} rout;

typedef struct Graph
{
    int V;
    int E;
    int **a;
} graph;

rout* citire(FILE *f,int n)
{
    rout *p;
    int i,j;
    char buffer1[DIM],buffer2[DIM];
    p=malloc(sizeof(rout)*n);
    for(i=0; i<n; i++)
    {
        memset(buffer1,0,DIM);
        memset(buffer2,0,DIM);
        fscanf(f,"%s",buffer1);
        fscanf(f,"%s",buffer2);
        fscanf(f,"%d",&p[i].nr_pc);
        p[i].nume_router=malloc(sizeof(char)*(strlen(buffer1)+1));
        p[i].ip_router=malloc(sizeof(char)*(strlen(buffer2)+1));
        strcpy(p[i].nume_router,buffer1);
        strcpy(p[i].ip_router,buffer2);
        p[i].calc=malloc(sizeof(pc)*(p[i].nr_pc));
        for(j=0; j<(p[i].nr_pc); j++)
        {
            memset(buffer1,0,DIM);
            memset(buffer2,0,DIM);
            fscanf(f,"%s",buffer1);
            fscanf(f,"%s",buffer2);
            fscanf(f,"%d",&p[i].calc[j].stare);
            p[i].calc[j].nume_pc=malloc(sizeof(char)*(strlen(buffer1))+1);
            p[i].calc[j].ip_pc=malloc(sizeof(char)*(strlen(buffer2))+1);
            strcpy(p[i].calc[j].nume_pc,buffer1);
            strcpy(p[i].calc[j].ip_pc,buffer2);
        }
    }
    return p;
}
graph *create(FILE *f,int n,rout *p)
{
    int i,j,k,l;
    char *c1,*c2,buffer1[DIM],buffer2[DIM];
    graph *g;
    g=malloc(sizeof(graph));
    if(g==NULL)
    {
        printf("Nu s-a alocat memorie pentru acest graf");
        exit(1);
    }
    g->V=n;
    g->a=malloc(sizeof(int)*(g->V));
    fscanf(f,"%d",&(g->E));
    for(i=0; i<(g->V); i++)
    {
        g->a[i]=calloc(g->V,sizeof(int));
    }
    if((g->a)==NULL)
    {
        printf("Alocare esuata");
        exit(1);
    }
    for(j=0; j<(g->E); j++)
    {
        memset(buffer1,0,DIM);
        memset(buffer2,0,DIM);
        fscanf(f,"%s",buffer1);
        fscanf(f,"%s",buffer2);
        c1=malloc(sizeof(char)*(strlen(buffer1)+1));
        c2=malloc(sizeof(char)*(strlen(buffer2)+1));
        strcpy(c1,buffer1);
        strcpy(c2,buffer2);
        for(i=0; i<(g->V); i++)
        {
            if(strcmp(p[i].nume_router,c1)==0)
                k=i;
            if(strcmp(p[i].nume_router,c2)==0)
                l=i;
        }
        fscanf(f,"%d",&(g->a[k][l]));
        g->a[l][k]=g->a[k][l];
    }
    return g;

}
void sipn(FILE *f,FILE *f1,rout *p,graph *g)
{
    int i,j;
    char *ip,buffer[DIM];
    memset(buffer,0,DIM);
    fscanf(f,"%s",buffer);
    ip=malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(ip,buffer);
    for(i=0; i<g->V; i++)
    {
        if(strcmp(ip,p[i].ip_router)==0)
        {
            for(j=0; j<g->V; j++)
            {
                if(g->a[i][j]!=0)
                    fprintf(f1,"%s ",p[j].ip_router);
            }
        }
    }
    fprintf(f1,"\n");
}
void si(FILE *f,FILE *f1,rout *p,int n)
{
    int i,j;
    char *ip, buffer[DIM];
    memset(buffer,0,DIM);
    fscanf(f,"%s",buffer);
    ip=malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(ip,buffer);
    for(i=0; i<n; i++)
    {
        if(strcmp(ip,p[i].ip_router)==0)
            for(j=0; j<p[i].nr_pc; j++)
            {
                if(p[i].calc[j].stare==1)
                    fprintf(f1,"%s ",p[i].calc[j].ip_pc);
            }
    }
    fprintf(f1,"\n");
}
rout *up(FILE *f,FILE *f1,rout *p,int n)
{
    int i,j;
    char *ip, buffer[DIM];
    memset(buffer,0,DIM);
    fscanf(f,"%s",buffer);
    ip=malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(ip,buffer);
    for(i=0; i<n; i++)
        for(j=0; j<p[i].nr_pc; j++)
        {
            if(strcmp(ip,p[i].calc[j].ip_pc)==0)
                if(p[i].calc[j].stare==0)
                {
                    p[i].calc[j].stare=1;
                    break;
                }
        }
    return p;
}
rout *broke(FILE *f,FILE *f1,rout *p,int n)
{
    int i,j;
    char *ip, buffer[DIM];
    memset(buffer,0,DIM);
    fscanf(f,"%s",buffer);
    ip=malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(ip,buffer);
    for(i=0; i<n; i++)
        for(j=0; j<p[i].nr_pc; j++)
        {
            if(strcmp(ip,p[i].calc[j].ip_pc)==0)
                if(p[i].calc[j].stare==1)
                {
                    p[i].calc[j].stare=0;
                    break;
                }
        }
    return p;
}
void lc(FILE *f,FILE *f1,rout *p,graph *g)
{
    int i,k,l;
    char *ip1,*ip2,buffer1[DIM],buffer2[DIM];
    memset(buffer1,0,DIM);
    memset(buffer2,0,DIM);
    fscanf(f,"%s",buffer1);
    fscanf(f,"%s",buffer2);
    ip1=malloc(sizeof(char)*(strlen(buffer1)+1));
    ip2=malloc(sizeof(char)*(strlen(buffer2)+1));
    strcpy(ip1,buffer1);
    strcpy(ip2,buffer2);
    for(i=0; i<g->V; i++)
    {
        if(strcmp(ip1,p[i].ip_router)==0)
            k=i;
        if(strcmp(ip2,p[i].ip_router)==0)
            l=i;
    }
    g->a[k][l]=0;
    g->a[l][k]=g->a[k][l];
}
void add(FILE *f,FILE *f1,rout *p,graph *g)
{
    int i,k,l,d;
    char *ip1,*ip2,buffer1[DIM],buffer2[DIM];
    memset(buffer1,0,DIM);
    memset(buffer2,0,DIM);
    fscanf(f,"%s",buffer1);
    fscanf(f,"%s",buffer2);
    fscanf(f,"%d",&d);
    ip1=malloc(sizeof(char)*(strlen(buffer1)+1));
    ip2=malloc(sizeof(char)*(strlen(buffer2)+1));
    strcpy(ip1,buffer1);
    strcpy(ip2,buffer2);
    for(i=0; i<g->V; i++)
    {
        if(strcmp(ip1,p[i].ip_router)==0)
            k=i;
        if(strcmp(ip2,p[i].ip_router)==0)
            l=i;
    }
    g->a[k][l]=d;
    g->a[l][k]=g->a[k][l];
}


void DFS(int x,int vector_vizitare[],int n,graph *g)
{
    int i;
    vector_vizitare[x]=1;
    for(i=0; i<n; i++)
        if((g->a[x][i]!=0)&&(vector_vizitare[i]==0))
            DFS(i,vector_vizitare,n,g);
}

void drum_minim(int dim,int k,int l,int vector_vizitare[],int d[],int anterior[],int c[dim][dim],graph *g)
{
    int cap;
    cap=k;
    vector_vizitare[cap]=1;
    d[cap]=0;

    int i,minim,aux,dist;
    while(vector_vizitare[l]==0)
    {
        minim=INF;
        aux=0;
        for(i=0; i<g->V; i++)
        {
            dist=d[cap]+c[cap][i];
            if(dist<d[i] && vector_vizitare[i]==0)
            {
                d[i]=dist;
                anterior[i]=cap;
            }
            if(minim>d[i] && vector_vizitare[i]==0)
            {
                minim=d[i];
                aux=i;
            }
        }
        cap=aux;
        vector_vizitare[cap]=1;
    }
}

void afisare(FILE *f1,int drum[],int anterior[],int l,rout *p)
{
    int j=0;
    int k,t;
    k=l;
    while(k!=-1)
    {
        drum[j]=k;
        j++;
        k=anterior[k];
    }

    t=j-1;
    while(t>=0)
    {
        if(t==0)
            fprintf(f1,"%s",p[drum[t]].ip_router);
        else
            fprintf(f1,"%s ",p[drum[t]].ip_router);

        t--;
    }
    
}
void Dijsktra(FILE *f1,int k, int l, graph *g,rout *p)
{

    int dim=g->V;
    int c[dim][dim];
    int i,j;
    for(i=0; i<dim; i++)
        for(j=0; j<dim; j++)
        {
            if(g->a[i][j]==0)
                c[i][j]=INF;  //un numar mare(infinit)
            else
                c[i][j]=g->a[i][j];
        }



    int *d, *anterior, *vector_vizitare, *drum;
    d=malloc(dim*sizeof(int));
    anterior=malloc(dim*sizeof(int));
    vector_vizitare=malloc(dim*sizeof(int));
    drum=malloc(dim*sizeof(int));

    for(i=0; i<dim; i++)
        vector_vizitare[i]=0;

    for(i=0; i<dim; i++)
    {
        d[i]=INF;
        anterior[i]=-1;
    }


    drum_minim(dim,k,l,vector_vizitare,d,anterior,c,g);
    afisare(f1,drum,anterior,l,p);

    free(d);
    free(anterior);
    free(vector_vizitare);
    free(drum);

}
void trace(FILE *f,FILE *f1,graph *g,rout *p)
{
    int k,l;
    int i,j;
    char *ip1, *ip2, buffer1[DIM], buffer2[DIM];
    memset(buffer1,0,DIM);
    memset(buffer2,0,DIM);
    fscanf(f,"%s",buffer1);
    fscanf(f,"%s",buffer2);
    ip1=malloc(sizeof(char)*(strlen(buffer1)+1));
    ip2=malloc(sizeof(char)*(strlen(buffer2)+1));
    strcpy(ip1,buffer1);
    strcpy(ip2,buffer2);
    for(i=0; i<g->V; i++)
        for(j=0; j<p[i].nr_pc; j++)
        {
            if(strcmp(ip1,p[i].calc[j].ip_pc)==0)
                k=i;
            if(strcmp(ip2,p[i].calc[j].ip_pc)==0)
                l=i;
        }

    int *vector_vizitare;
    vector_vizitare=malloc(g->V*sizeof(int));
    for(i=0; i<g->V; i++)
        vector_vizitare[i]=0;

    DFS(k,vector_vizitare,g->V,g);
    if(vector_vizitare[l]==1)
        Dijsktra(f1,k,l,g,p);
 
    free(ip1);
    free(ip2);
    free(vector_vizitare);
}

void ping(FILE *f,FILE *f1,graph *g, rout *p)
{
    int k,l;
    int i,j;
    char *ip1, *ip2, buffer1[DIM], buffer2[DIM];
    memset(buffer1,0,DIM);
    memset(buffer2,0,DIM);
    fscanf(f,"%s",buffer1);
    fscanf(f,"%s",buffer2);
    ip1=malloc(sizeof(char)*(strlen(buffer1)+1));
    ip2=malloc(sizeof(char)*(strlen(buffer2)+1));
    strcpy(ip1,buffer1);
    strcpy(ip2,buffer2);

    int *vector_vizitare;
    vector_vizitare=malloc(g->V*sizeof(int));
    for(i=0; i<g->V; i++)
        vector_vizitare[i]=0;

    int stare1,stare2;
    for(i=0; i<g->V; i++)
    {
        for(j=0; j<p[i].nr_pc; j++)
        {
            if(strcmp(ip1,p[i].calc[j].ip_pc)==0)
            {
                k=i;
                stare1=p[i].calc[j].stare;
            }
            if(strcmp(ip2,p[i].calc[j].ip_pc)==0)
            {
                l=i;
                stare2=p[i].calc[j].stare;
            }
        }
    }

    DFS(k,vector_vizitare,g->V,g);
    if(stare1==0 || stare2==0)
        fprintf(f1,"NO");
    else
    {
        if(vector_vizitare[l]==0)
            fprintf(f1,"NO");
        else
            fprintf(f1,"OK");
    }

    free(ip1);
    free(ip2);
    free(vector_vizitare);

}

int main(int argc, char *argv[])
{
    int n,nr_op,i;
    char buffer[DIM];
    rout *p;
    FILE *f,*f1;
    graph *g;
    if((f=fopen(argv[1],"rt"))==NULL)
    {
        printf("Fisierul nu s-a deschis");
        exit(1);
    }
    fscanf(f,"%d",&n);
    p=citire(f,n);
    g=create(f,n,p);
    if((f1=fopen(argv[2],"wt"))==NULL)
    {
        printf("Fisierul argv[2] nu s-a deschis");
        exit(1);
    }

    fscanf(f,"%d",&nr_op);
    for(i=0; i<nr_op; i++)
    {
        memset(buffer,0,DIM);
        fscanf(f,"%s",buffer);
        if(strcmp(buffer,"sipn")==0)
        {
            sipn(f,f1,p,g);
        }
        if(strcmp(buffer,"si")==0)
        {
            si(f,f1,p,n);
        }
        if(strcmp(buffer,"up")==0)
        {
            p=up(f,f1,p,n);
        }
        if(strcmp(buffer,"broke")==0)
        {
            p=broke(f,f1,p,n);
        }
        if(strcmp(buffer,"lc")==0)
        {
            lc(f,f1,p,g);
        }
        if(strcmp(buffer,"add")==0)
        {
            add(f,f1,p,g);
        }
        if(strcmp(buffer,"trace")==0)
        {
            trace(f,f1,g,p);
	    fprintf(f1,"\n");
        }
        if(strcmp(buffer,"ping")==0)
        {
            ping(f,f1,g,p);
	    fprintf(f1,"\n");
        }
    }

    return 0;
}
