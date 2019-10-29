class CParticula: public CObjeto{

private:
Timer tempo;
int xini,yini;
int dx,dy;
int menor_x,maior_x,menor_y,maior_y;
int hp;
float lim_tempo;
public:
    bool viva;
    CParticula(int x,int y,int desloc_x,int desloc_y,int vida,int altura_tela, SDL_Renderer* renderizador,char *nomeArq):CObjeto(x,y,altura_tela,renderizador,nomeArq){
        xini = x;
        yini = y;
        dx = desloc_x;
        dy = desloc_y;
        hp = vida;

        tempo = new CTimer();
        viva = true;
    }
    void DefineLimites(int xMenor,int xMaior,int yMenor,int yMaior, float tempoMax){
        menor_x = xMenor;
        maior_x = xMaior;
        menor_y = yMenor;
        maior_y = yMaior;
        lim_tempo = tempoMax;
    }
    ~CParticula(){
        delete tempo;
    }
    void Move(){
        if (!viva) return;
        float decorrido = tempo->GetTempoDecorrido();
        x = xini + dx*decorrido;
        y = yini + dy*decorrido;
        CObjeto::Move(x,y);
        viva = (x>menor_x)&&(x<maior_x)&&(y>menor_y)&&(y<maior_y)&&(decorrido<lim_tempo);
    }
    void MudaDirecao(int novaDx,int novaDy){
        dx = novaDx;
        dy = novaDy;
    }
    int Colisao(Objeto outro){
        int resp = CObjeto::Colisao(outro);
        if (resp){
            hp--;
            viva = hp>0;
        }
        return resp;
    }
};

typedef CParticula* Particula;
