#include <fstream>
#include <iostream>
using namespace std;

struct nod{
    int info;
    nod *s,*d, *tata;
};
nod *creare(int x){
    nod *aux;
    aux = new(nod);
    aux->info=x;
    aux->s = NULL;
    aux->d = NULL;
    aux->tata = NULL;
    return aux;
}

nod *zig(nod *a){
    nod *b = a->s;
    a->s = b->d;
    b->d = a;
    return b;

}
nod *zag(nod *a){
    nod *b = a->d;
    a->d = b->s;
    b->s = a;
    return b;

}
nod *splay(nod *&rad, nod *&aux){
    while(aux->tata != NULL){
        if(aux->tata == rad){
            if(aux->info > rad->info){
                rad = zag(rad);
                rad->tata = NULL;
            }
            else{
                rad = zig(rad);
                rad->tata = NULL;
            }
        }
        else{
            nod *tata, *bunic;
            tata = aux->tata;
            bunic = tata->tata;
            if(tata->info > aux->info){
                if(bunic->info > tata->info){
                    aux->tata = zig(bunic);
                    aux = zig(tata);
                    if(bunic->tata != NULL){
                        aux->tata = bunic->tata;
                        if(bunic->tata == rad){
                            aux->tata = rad;
                            rad->s = aux;
                        }
                    }
                    else
                        aux->tata = NULL;
                }
                else{
                    bunic->d = zig(tata);
                    if(bunic->tata != NULL){
                        bunic->tata->s = zag(bunic);
                        aux->tata = bunic->tata;
                    }
                    else{
                        rad = zag(bunic);
                        rad->tata = NULL;
                    }

                }
            }
            else if(tata->info < aux->info){
                if(bunic->info < tata->info){
                    aux->tata = zag(bunic);
                    aux = zag(tata);
                    if(bunic->tata != NULL){
                        aux->tata = bunic->tata;
                        if(bunic->tata == rad){
                            aux->tata = rad;
                            rad->d = aux;
                        }
                    }
                    else
                        aux->tata = NULL;
                }
                else{
                    bunic->s = zag(tata);
                    if(bunic->tata != NULL){
                        bunic->tata->d = zig(bunic);
                        aux->tata = bunic->tata;
                    }
                    else{
                        rad = zig(bunic);
                        rad->tata = NULL;
                    }
                }
            }
        }
    }
    rad = aux;
}

bool cautare(nod *&rad, int x){
    if(rad == NULL)
        return 0;
    if(x == rad->info)
        return 1;
    nod *tata;
    nod *aux = rad;
    while(aux != NULL && aux->info != x){
        tata = aux;
        if(x > aux->info)
            aux = aux->d;
        else
            aux = aux->s;
        if(aux != NULL)
            aux->tata = tata;
    }
    if(aux == NULL){
        splay(rad, tata);
        return 0;
    }
    else{
        splay(rad, aux);
        return 1;
    }
}
nod *inserare(nod *&rad, int x, nod *&aux){
    nod *tata, *fiu;
    aux = creare(x);
    if(rad == NULL){
        rad = aux;
        return 0;
    }
    tata = fiu = rad;
    while(fiu != NULL){
        tata = fiu;
        if(fiu->info > aux->info)
            fiu = fiu->s;
        else
            fiu = fiu->d;
        if(fiu != NULL)
            fiu->tata = tata;
    }
    if(tata->info > aux->info)
        tata->s = aux;
    else{
        tata->d = aux;
    }
    aux->tata = tata;
    splay(rad, aux);
}
nod *topdown(nod *&rad, int x){
    int a = cautare(rad, x);
    if(a == 0)
        return 0;
    else{
        if(rad->d == NULL)
            rad = rad->s;
        else
            if(rad->s == NULL)
            rad = rad->d;
            else{
                nod *aux = rad->d;
                rad = rad->s;
                cautare(rad, x);
                rad->d = aux;
            }
    }
}
nod *maremic(nod *&rad, int x){
    cautare(rad, x);
    if(rad->s == NULL){
        cout<<rad->info<<"\n";
        return 0;
    }
    nod *aux = rad->s;
    while(aux->s != NULL)
        aux = aux->s;
    cautare(rad, aux->info);
    cout<<rad->info<<"\n";
}
nod *micmare(nod *&rad, int x){
    cautare(rad, 5);
    if(rad->d == NULL){
        cout<<rad->info<<"\n";
        return 0;
    }

    nod *aux = rad->d;
    while(aux->s != NULL)
        aux = aux->s;
    cautare(rad, aux->info);
    cout<<rad->info<<"\n";
}
void sortare(nod *&rad, int &x, int z){
    nod *aux = rad;
    if(aux->info == x){
        cout<<aux->info<<" ";
        x++;
    }
    if(aux->info < x){
        while(aux->d != NULL){
            aux = aux->d;
            while(aux->s != NULL)
                aux = aux->s;
            if(aux != NULL && aux->info > x && aux->info <= z)
                cautare(rad, aux->info);
            break;
        }
    }
    else{
        while(aux->s != NULL){
            aux = aux->s;
        }
        if(aux != NULL && aux->info >= x && aux->info <= z)
            cautare(rad, aux->info);
    }
    if(rad->info >= x && rad->info <= z){
        cout<<rad->info<<" ";
        x = rad->info+1;
        sortare(rad, x, z);
    }
}

int main()
{
    ifstream fin("C:\\Users\\Ciprian\\Documents\\GitHub\\Splay-tree\\date.in");
    nod *rad, *aux;
    int y, x, n;
    rad = NULL;
    fin>>n;
    for(int i = 0; i<n; i++){
        fin>>y>>x;
        if(y == 1)
            inserare(rad, x, aux);
        if(y == 2)
            topdown(rad, x);
        if(y == 3)
            cout<<cautare(rad, x)<<"\n";
        if(y == 4)
            maremic(rad, x);
        if(y == 5)
            micmare(rad, x);
        if(y == 6){
            int z;
            fin>>z;
            sortare(rad, x, z);
            cout<<"\n";
        }

    }
    fin.close();
    return 0;
}