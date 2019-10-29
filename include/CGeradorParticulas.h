#include "CParticula.h"

#define LIMITE_PARTICULAS 1000

class CGeradorParticulas{

private:
Particula parts[LIMITE_PARTICULAS];
int px,py,dx,dy;
int alt_tela;
SDL_Renderer* renderer;
int hp;
int maxParticulas;
char nome[50];

public:
    int ativas;
    CGeradorParticulas(int maximoParticulas,int altura_tela, SDL_Renderer* renderizador, char *nomeArq){
        maxParticulas = maximoParticulas;
        strcpy(nome,nomeArq);
        for (int i=0;i<maxParticulas;i++)
            parts[i] = NULL;
        alt_tela = altura_tela;
        renderer = renderizador;
	    dy = 0;
		dx = 0;
		hp = 1;
		ativas = 0;
    }
    ~CGeradorParticulas(){
        for (int i=0;i<maxParticulas;i++)
            if (parts[i]) delete parts[i];
    }
    void MoveParticulas(){
        for (int i=0;i<maxParticulas;i++)
            if (parts[i]) {
                parts[i]->Move();
                if (!parts[i]->viva){
                    delete parts[i];
                    parts[i] = NULL;
                    ativas--;
                }
            }
    }
    void Move(int nx,int ny){
        px = nx;
        py = ny;
    }
    void MudaDirecao(int novaDx,int novaDy){
        dx = novaDx;
        dy = novaDy;
    }
    void MudaHP(int novoValor){
        hp = novoValor;
    }
    void Desenha(){
        for (int i=0;i<maxParticulas;i++)
            if ((parts[i])&&(parts[i]->viva)) {
                parts[i]->Desenha();
            }
    }
    int CriaParticula(){
        int i=0;
        if (ativas>=maxParticulas) return -1;
        while (parts[i])
            i++;
        parts[i] = new CParticula(px,py,dx,dy,hp,alt_tela,renderer,nome);
        parts[i]->DefineLimites(-50,1050,-50,1000,10000.0);
        ativas++;
        return i;
    }
    int Colisao(Objeto outro){
        int resp = 0;
        int i=0,cont=0;
        while (!resp && i<maxParticulas && cont<ativas){
            if (parts[i]){
                cont++;
                resp = parts[i]->Colisao(outro);
            }
            i++;
        }
        return resp;
    }
};

typedef CGeradorParticulas* GeradorParticulas;
