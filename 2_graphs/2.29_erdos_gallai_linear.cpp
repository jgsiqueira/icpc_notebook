#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <deque>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <sstream>
#define INF 0x3f3f3f3f
#define MAX 100000

using namespace std;


/*

    ERDOS GALLAI LINEAR

    Aplicacoes:

        Determinar se um conjunto b de n elementos pode
        representar o grau dos vertices de um grafo de n
        elementos, ou seja, b[1] == grau do vertice 1,
        b[2] == grau do vertice[2], ...

    Como chamar a funcao:

        1) Armazenar o tamanho (quantidade de elementos)
           do vetor b na variavel n.

        2) Preencher o vetor b partindo da posicao 1
           ate a posicao n (inclusive)

        3) Chamar a funcao EGH()

    Resultado da funcao:

        A funcao EGL retorna:

            true -> se b pode representar o grau dos
                    n vertices de um grafo

            false -> caso contrario

    Complexidade do algoritmo:

        O(n)

    Problemas resolvidos:

        URI 1462
        UVA 10720

    Adicionado por:

        Jorge Gabriel Siqueira

*/

long long b[MAX], n;
long long dmax,dmin,dsum,num_degs[MAX];

bool basic_graphical_tests() //Sort and perform some simple tests on the sequence
{
    int p = n;

    memset(num_degs, 0, (n+1)*sizeof(long long));

    dmax = dsum = n = 0;
    dmin = p;

    for(int d=1; d<=p; d++)
    {
        if(b[d] < 0 || b[d] >= p)
        {
            return false;
        }
        else if(b[d] > 0)
        {
            if(dmax < b[d]) dmax = b[d];
            if(dmin > b[d]) dmin = b[d];
            dsum = dsum+b[d];
            n++;
            num_degs[b[d]]++;
        }
    }

    if(dsum%2 || dsum > n*(n-1)) return false;
    return true;
}

bool EGL()
{
    if(basic_graphical_tests() == false) return false;

    if(n == 0 || 4*dmin*n >= (dmax+dmin+1)*(dmax+dmin+1)) return true;

    long long k,sum_deg,sum_nj,sum_jnj,run_size;

    k = sum_deg = sum_nj = sum_jnj = 0;

    for(int dk = dmax; dk >= dmin; dk--)
    {
        if(dk < k+1) return true;

        if(num_degs[dk] > 0)
        {
            run_size = num_degs[dk];
            if(dk < k+run_size)
            {
                run_size = dk-k;
            }
            sum_deg += run_size * dk;

            for(int v=0; v<run_size; v++)
            {
                sum_nj += num_degs[k+v];
                sum_jnj += (k+v) * num_degs[k+v];
            }

            k += run_size;

            if(sum_deg > k*(n-1) - k*sum_nj + sum_jnj)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    n = 3;
    b[1] = 1; b[2] = 1; b[3] = 1;
    assert(EGL() == false);

    n = 3;
    b[1] = 2; b[2] = 2; b[3] = 2;
    assert(EGL() == true);

    n = 4;
    b[1] = 1; b[2] = 1; b[3] = 1; b[4] = 1;
    assert(EGL() == true);

    n = 4;
    b[1] = 3; b[2] = 2; b[3] = 2; b[4] = 1;
    assert(EGL() == true);

    n = 4;
    b[1] = 3; b[2] = 3; b[3] = 2; b[4] = 2;
    assert(EGL() == true);

    n = 4;
    b[1] = 3; b[2] = 3; b[3] = 1; b[4] = 1;
    assert(EGL() == false);
    return 0;
}

