#include "PIG.h"

#define VELOCIDADE 3
PIG_Evento evento;
PIG_Teclado meuTeclado;

int sharkao;
int tempoTecla; // serve para testar o tempo entre um aperto de tecla e outro, pra quando vc segurar pra cima ele nao teleportar pro topo
int plataforma,invertida,espinho1,espinho2;
int x, y;
int anomena;
int rede;
int roda;
int redemoinho;
int cocafritas;
int diver,tt;
int mario;
int conta=0;
int tiro[8];
int blocotroll;
int inicio=0;
int colisao = 0;
int gameover;

void Criando_Objetos()
{
    Define_Fundo("imagens//fundo.bmp");
    sharkao = Cria_Objeto("imagens//sharkao.png");
    plataforma = Cria_Objeto("imagens//coral.bmp");
    espinho1 = Cria_Objeto("imagens//espinho1.png");
    espinho2 = Cria_Objeto("imagens//espinho2.png");
    anomena = Cria_Objeto("imagens//anemona.png");
    roda = Cria_Objeto("imagens//roda.png");
    redemoinho = Cria_Objeto("imagens//redemoinho.png");
    cocafritas = Cria_Objeto("imagens//cocafrita.png");
    mario = Cria_Objeto("imagens//mario.png");
    rede = Cria_Objeto("imagens//rede1.png");
    tiro[8] = Cria_GeradorParticulas(10,"imagens//tiro.bmp");
    diver = Cria_Objeto("imagens//atirador.png");
    invertida = Cria_Objeto("imagens//coral2.bmp");
    for(int i=0;i<9;i++){
    tiro[i] = Cria_GeradorParticulas(100,"imagens//tiro.bmp");}
    blocotroll = Cria_Objeto("imagens//blocotroll.png");
}

void criatiros() //Essa função só serve pra deixar a do projetil bonitinho
{
        Cria_Particula(tiro[1]);
        Cria_Particula(tiro[2]);
        Cria_Particula(tiro[3]);
        Cria_Particula(tiro[4]);
        Cria_Particula(tiro[5]);
        Cria_Particula(tiro[6]);
        Cria_Particula(tiro[7]);
}

void Plataforma1()
{
    Define_Dimensoes(plataforma, 5,1270);
    Desenha_Objeto(plataforma);
    Move_Objeto(plataforma,0,175);
    if (Testa_Colisao(sharkao,plataforma) !=0){
        GetXY_Objeto(sharkao,&x,&y);
        if(y<=175){
        Move_Objeto(sharkao,x,y-2);
        }
        if(y>175){
        Move_Objeto(sharkao,x,y+2);
        }
    }

}

void PlataformaInvertida()
{
    Define_Dimensoes(invertida, 175,5);
    Desenha_Objeto(invertida);
    Move_Objeto(invertida,950,0);
    if (Testa_Colisao(sharkao,invertida) !=0)
    {
        GetXY_Objeto(sharkao,&x,&y);
        if(x<=1000)
        {
        Move_Objeto(sharkao,x-2,y);
        }
    }

}

void Plataforma2()
{
    Desenha_Objeto(espinho1);
    Define_Dimensoes(espinho1, 5,1270);
    Move_Objeto(espinho1,0,350);
    if (Testa_Colisao(sharkao,espinho1) !=0){
        GetXY_Objeto(sharkao,&x,&y);
        if(y<=350){
        Move_Objeto(sharkao,0,0);
        }
        if(y>350){
        Move_Objeto(sharkao,x,y+2);}
    }

}

void Plataforma3()
{
    Desenha_Objeto(espinho2);
    Define_Dimensoes(espinho2, 5,1270);
    Move_Objeto(espinho2,0,525);
    if (Testa_Colisao(sharkao,espinho2) !=0){
        GetXY_Objeto(sharkao,&x,&y);
        if(y<=525){
        Move_Objeto(sharkao,0,0);
        conta++;
        }
        if(y>525){
        Move_Objeto(sharkao,0,0);
        conta++;
        }
    }

}

void Plataforma4()
{
    Desenha_Objeto(espinho1);
    Define_Dimensoes(espinho1, 5,1270);
    Move_Objeto(espinho1,0,695);
    if (Testa_Colisao(sharkao,espinho1) !=0){
        GetXY_Objeto(sharkao,&x,&y);
        if(y<=695){
        Move_Objeto(sharkao,0,0);
        }
    }
}

void Desenha_Sharkao()
{
    Define_Dimensoes(sharkao,50,40);
    Desenha_Objeto(sharkao);
}

void obstaculo(int px,int py)
{
    Desenha_Objeto(roda);
    Define_Dimensoes(roda,50,50);
    Move_Objeto(roda,px,py);
    if (Testa_Colisao(sharkao,roda)){
        Move_Objeto(sharkao,0,0);
        conta++;
    }

}

void faztroll(int px,int py)
{
    Desenha_Objeto(blocotroll);
    Define_Dimensoes(blocotroll,50,50);
    Move_Objeto(blocotroll,px,py);
    if (Testa_Colisao(sharkao,blocotroll)){
        Move_Objeto(sharkao,0,0);
        conta++;
    }

}

void obstaculo_mario(int px,int py)
{
    Desenha_Objeto(mario);
    Define_Dimensoes(mario,49,49);
    Move_Objeto(mario,px,py);
    if (Testa_Colisao(sharkao,mario)){
        Move_Objeto(sharkao,0,0);
        conta++;
    }

}

void anemona(int px, int py)
{
    Define_Flip(anomena,FLIP_VERTICAL);
    Define_Dimensoes(anomena,40,50);
    Desenha_Objeto(anomena);
    Move_Objeto(anomena,px,py);
    if(Testa_Colisao(anomena,sharkao)){
        Move_Objeto(sharkao,0,0);
        conta++;
    }

}

void anemona_flip(int px, int py)
{
    Define_Flip(anomena,FLIP_NENHUM);
    Define_Dimensoes(anomena,40,50);
    Desenha_Objeto(anomena);
    Move_Objeto(anomena,px,py);
    if(Testa_Colisao(anomena,sharkao)){
        Move_Objeto(sharkao,0,0);
        conta++;
    }


}

void projetil(int px,int py,int n)
{
    if (Tempo_Decorrido(tt) > 4.5){
        criatiros();
        Reinicia_Timer(tt);
    }
    Move_GeradorParticulas(tiro[n],px,py);
    MudaDirecao_Particulas(tiro[n],-90,0);
    Desenha_Particulas(tiro[n]);
    Move_Particulas(tiro[n]);
    if (Colisao_Particulas(tiro[n],sharkao)){ //Tem que inverter shakao com tiro, senão da merda
        Move_Objeto(sharkao,0,0);
        conta++;
    }

}

void atirador(int px, int py, int n)//n é o numero do gerador de particulas
{
    Desenha_Objeto(diver);
    Define_Dimensoes(diver,40,65);
    Move_Objeto(diver,px,py);
    projetil(px,py,n);
    if(Testa_Colisao(diver,sharkao)){
        Move_Objeto(sharkao,0,0);
        conta++;
    }
}


void Rede(int px, int py)
{
    Define_Dimensoes(rede,50,100);
    Desenha_Objeto(rede);
    Move_Objeto(rede,px,py);
    if(Testa_Colisao(rede,sharkao)){
        Move_Objeto(sharkao,0,0);
        conta++;
    }
}

void TrataTecla(PIG_Teclado teclado)
{

    int x,y;

    if (Tempo_Decorrido(tempoTecla)<0.01-GetValorFloat_Objeto(sharkao,VELOCIDADE)) return;
    Reinicia_Timer(tempoTecla);


    if(teclado[TECLA_o]|| inicio==1){
    GetXY_Objeto(sharkao,&x,&y);
    if(teclado[TECLA_i]&inicio==0){
        conta=0;
        inicio=1;
    }

    if (teclado[TECLA_CIMA])
    {
        y = y +3;

    }
    if (teclado[TECLA_BAIXO]){
        if (y<=0)
            y=0;
        else
            y = y - 3;

    }
    if (teclado[TECLA_DIREITA]){
        Define_Flip(sharkao,FLIP_NENHUM);
        if (x>=1225){
            x=1225;
            Define_Flip(sharkao,FLIP_HORIZONTAL);
        }else
            x = x + 3;
    }

    if (teclado[TECLA_ESQUERDA]){
        Define_Flip(sharkao,FLIP_HORIZONTAL);
        if (x<=0){
            x=0;
            Define_Flip(sharkao,FLIP_NENHUM);
        }else
            x = x - 3;
    }
    if (x>=1180 && y >= 530)
    {
        if(teclado[TECLA_ENTER])
        {
            x=0;
            y=0;
            conta=0;
        }
    }
    Move_Objeto(sharkao,x,y);

    }
}


void fase_1()
{
    Desenha_Objeto(redemoinho);
    x = 870;
    y = 0;
    Move_Objeto(redemoinho,x,y);
    Define_Dimensoes(redemoinho,70,70);
    if (Testa_Colisao(sharkao,redemoinho)){
        x = 0;
        y = 180;
        Move_Objeto(sharkao,x,y);
    }
    anemona(650,0);
    anemona_flip(300,135);
    anemona(250,0);
    anemona_flip(650,135);
    Rede(450,60);
    obstaculo_mario(770,60);
}

void fase_2()
{
    Desenha_Objeto(redemoinho);
    x = 1200;
    y = 180;
    Move_Objeto(redemoinho,x,y);
    Define_Dimensoes(redemoinho,70,70);
    if (Testa_Colisao(sharkao,redemoinho)){
        x = 0;
        y = 360;
        Move_Objeto(sharkao,x,y);
    }
    anemona(150,180);
    anemona_flip(420,350);
    Rede(700,185);
    Rede(280,300);
    atirador(380,250,3);
    atirador(1000,290,4);
    obstaculo_mario(500,185);
    obstaculo_mario(545,225);
}

void fase_3()
{
    Desenha_Objeto(redemoinho);
    x = 1200;
    y = 356;
    Move_Objeto(redemoinho,x,y);
    Define_Dimensoes(redemoinho,70,70);
    if (Testa_Colisao(sharkao,redemoinho)){
        x = 0;
        y = 541;
        Move_Objeto(sharkao,x,y);
    }
    anemona_flip(420,490);
    anemona(800,310);

    Rede(250,355);
    Rede(250,470);
    atirador(550,430,1);
    obstaculo(1130,370);
    obstaculo_mario(670,360);
    obstaculo_mario(670,410);
    obstaculo_mario(850,470);
    obstaculo_mario(850,360);
    atirador(1000,440,2);
}

void fase_4()
{
    Desenha_Objeto(cocafritas);
    Move_Objeto(cocafritas,1220,530);
    Define_Dimensoes(cocafritas,40,40);
    atirador(200,575,5);
    atirador(590,655,6);
    Rede(420,590);
    atirador(590,550,7);
    obstaculo_mario(70,640);
    anemona(320,530);
    anemona_flip(320,650);
    obstaculo(720,590);
    Rede(850,640);
    Rede(850,590);
    obstaculo_mario(1000,645);
    obstaculo_mario(1000,595);
    obstaculo_mario(1120,530);
    obstaculo_mario(1230,610);

}

void fim()
{
    char over[50];
    char cont[50];
    char restart[20];
    if (Testa_Colisao(sharkao,cocafritas)){
        sprintf(over,"VOCE GANHOU!");
        Escrever(over,295,350,200,600,VERDE);
        sprintf(cont,"Numero de mortes: %d",conta);
        Escrever(cont,445,250,40,300,VERDE);
        sprintf(restart,"Pressione ENTER para reiniciar.");
        Escrever(restart,395,300,50,400,VERDE);
        sprintf(over,"VOCE GANHOU!");
        Escrever(over,300,350,200,600,VERMELHO);
        sprintf(cont,"Numero de mortes: %d",conta);
        Escrever(cont,450,250,40,300,VERMELHO);
        sprintf(restart,"Pressione ENTER para reiniciar.");
        Escrever(restart,400,300,50,400,VERMELHO);
        Move_Objeto(sharkao,1220,540);
    }
}

int main( int argc, char* args[] )
{

    Cria_Jogo(700,1270,"Sharkao");
    meuTeclado = Pega_Teclado();
    Criando_Objetos();
    tempoTecla = Cria_Timer();
    tt = Cria_Timer();

    while (Jogo_Rodando()!=0)
    {
        evento = Confere_Evento();
        TrataTecla(meuTeclado);

        Inicia_Desenho();
        Desenha_Sharkao();
        fase_1();
        fase_2();
        fase_3();
        fase_4();


        Plataforma1();
        Plataforma2();
        Plataforma3();
        Plataforma4();
        PlataformaInvertida();
        fim();



        Encerra_Desenho();
    }

    Destroi_Timer(tempoTecla);

    Finaliza_Jogo();
    return 0;
}
