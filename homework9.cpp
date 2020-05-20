#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

typedef struct BitNode

{
        char data;
        struct BitNode *lchild,*rchild;
} BitNode;

void postorder(BitNode *p)
{
    if(p->lchild){
        #pragma omp task
        postorder(p->lchild);}
    if(p->rchild){
        #pragma omp task
        postorder(p->rchild);
    }
    #pragma omp taskwait
    printf("%c ",p->data);
}
int
main (int argc, char **argv)
{
  BitNode *tree;
  BitNode a,b,c,d,e,f,eq,mi,mu,di,pl;
  a.data='A';a.lchild=0;a.rchild=0;
  b.data='B';b.lchild=0;b.rchild=0;
  c.data='C';c.lchild=0;c.rchild=0;
  d.data='D';d.lchild=0;d.rchild=0;
  e.data='E';e.lchild=0;e.rchild=0;
  f.data='F';f.lchild=0;f.rchild=0;
  eq.data='=';eq.lchild=&a;eq.rchild=&mi;
  mi.data='-';mi.lchild=&mu;mi.rchild=&f;
  mu.data='*';mu.lchild=&di;mu.rchild=&e;
  di.data='/';di.lchild=&b;di.rchild=&pl;
  pl.data='+';pl.lchild=&c;pl.rchild=&d;
  tree=&eq;
  omp_set_num_threads (4);
#pragma omp parallel
  {
#pragma omp single
        postorder(tree);
  }
  printf("\n");
}




