#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000  // max items

// minimal heap state
static int heap[MAXSIZE];
static int size_ = 0;

// tiny swap
static inline void swap(int *a, int *b){ int t = *a; *a = *b; *b = t; }

// bubble up while child is bigger than parent
static void reHeapUp(int i){
    while(i > 0){
        int p = (i - 1) / 2;
        if(heap[i] > heap[p]){ swap(&heap[i], &heap[p]); i = p; }
        else break;
    }
}

// push down until heap order holds
void reHeapDown(int i){
    for(;;){
        int l = 2*i + 1, r = 2*i + 2, m = i;
        if(l < size_ && heap[l] > heap[m]) m = l;
        if(r < size_ && heap[r] > heap[m]) m = r;
        if(m != i){ swap(&heap[i], &heap[m]); i = m; }
        else break;
    }
}

// insert at end and fix upward
void insert(int x){
    if(size_ >= MAXSIZE){ fprintf(stderr, "Heap lleno.\n"); return; }
    heap[size_] = x;
    reHeapUp(size_);
    size_++;
}

// remove root and fix downward
int removeMax(void){
    if(size_ == 0){ fprintf(stderr, "Heap vacio.\n"); return -2147483648; }
    int mx = heap[0];
    heap[0] = heap[--size_];
    reHeapDown(0);
    return mx;
}

// show array view
void showHeap(void){
    printf("Heap tam=%d: [", size_);
    for(int i=0;i<size_;++i) printf("%s%d", i? ", ":"", heap[i]);
    puts("]");
}

// list node with left and right indices
void showAsTree(void){
    puts("i:valor  L[2*i+1]  R[2*i+2]");
    for(int i=0;i<size_;++i){
        int l = 2*i + 1, r = 2*i + 2;
        printf("%d:%d  L[%d]=", i, heap[i], l);
        if(l < size_) printf("%d  ", heap[l]); else printf("NA  ");
        printf("R[%d]=", r);
        if(r < size_) printf("%d\n", heap[r]); else puts("NA");
    }
}

int main(void){
    int N;

    printf("Cuantos enteros vas a insertar N? ");
    fflush(stdout);
    if(scanf("%d", &N) != 1 || N < 0){ fprintf(stderr, "Entrada invalida para N.\n"); return 0; }

    printf("Introduce los %d enteros uno por uno y presiona Enter en cada uno.\n", N);
    for(int i=0;i<N;++i){
        int x;
        printf("Elemento %d: ", i+1);
        fflush(stdout);
        if(scanf("%d", &x) != 1){ fprintf(stderr, "Entrada invalida.\n"); return 0; }
        insert(x);
        showHeap();    // print after each insertion as required
    }

    int K = 0;
    printf("Cuantas veces eliminar el maximo K? ");
    fflush(stdout);
    if(scanf("%d", &K) != 1 || K < 0){ K = 0; }

    for(int j=0;j<K && size_>0;++j){
        int mx = removeMax();
        printf("Se elimino el maximo: %d\n", mx);
        showHeap();
        showAsTree();
    }

    return 0;
}
