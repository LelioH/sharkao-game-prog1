/********************************
Versão da Biblioteca PIG.H
0.2.0
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "Tipos_PIG.h"
#include "CJogo.h"


/********************************
/ Variáveis Globais
/********************************/
Jogo jogo=NULL;

/********************************
A função Cria_Jogo é responsável pela criação da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra função da biblioetac PIG.h. Não é possível criar dois
jogos no mesmo progama. Logo, somente a primeira chamada terá efeito.
Parâmetros:
Largura_Janela (entrada, passagem por valor): indica a largura da janela do jogo em pixels.
Altura_Janela (entrada, passagem por valor): indica a altura da janela do jogo em pixels.
Nome_Janela (entrada, passagem por referência*): indica o nome que ajanela do jogo mostrará no seu título
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void Cria_Jogo(int Largura_Janela, int Altura_Janela,char *Nome_Janela)
{
    if (jogo==NULL)
        jogo = new CJogo(Largura_Janela,Altura_Janela,Nome_Janela);
}


/********************************
A função GetEstado_Jogo() indica o estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo ou a vez de algum jogador por exemplo.
Retorno:
inteiro indicando o valor do estado do jogo;
********************************/
int GetEstado_Jogo()
{
    return jogo->estado;
}

/********************************
A função SetEstado_Jogo() atribui um novo valor ao estado do jogo. Este estado é apenas um valor inteiro
que pode ser usado para indicar uma fase do jogo, ou a vez de algum jogador por exemplo.
Parâmetro:
estado (entrada, passagem por valor): indica o novo estado do jogo;
********************************/
void SetEstado_Jogo(int estado)
{
    jogo->estado = estado;
}

/********************************
A função Define_Fundo permite escolher um arquivo fr imagem como fundo (background) do jogo.
Parâmetros:
NomeArquivoImagem (entrada, passagem por referência*): indica o caminho relativo ou absoluto do arquivo de imagem que será utilizado como fundo do jogo.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void Define_Fundo(char *NomeArquivoImagem)
{
    jogo->DefineFundo(NomeArquivoImagem);
}

/********************************
A função Confere_Evento() indica se houve algum tipo de evento desde quando o jogo começou ou desde a última vez que a função foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada à tela do jogo.
Retorno:
Indica o tipo de evento que ocorreu. Se não houve evento, retorna o valor 0 (zero).
********************************/
PIG_Evento Confere_Evento()
{
    return jogo->TrataEventos();
}

/********************************
A função Pega_Tecla() indica qual tecla foi pressionada.
Uma lista das possíveis teclas e seus código pode ser vista em .
Retorno:
O valor de retorno da função é um vetor de números inteiros que indicam se uma determinada tecla (índice do vetor) foi
pressionada (valor diferente de 0,zero) ou não (valor igual a zero).
********************************/
PIG_Teclado Pega_Teclado()
{
    return jogo->PegaTeclado();
}

/********************************
A função Pega_MouseXY() é responsável por obter a posição do mouse em relação à janela do jogo.
Parâmetros:
PosicaoX (saída, passagem por referência): indica a posicao no eixo X do mouse.
PosicaoY (saída, passagem por referência): indica a posicao no eixo Y do mouse.
********************************/
void Pega_MouseXY(int *PosicaoX,int *PosicaoY)
{
    jogo->Pega_MouseXY(PosicaoX,PosicaoY);
}

/********************************
A função Pega_MouseBotao() é responsável por indicar qual dos botões (direito, esquerdo ou central/rodinha)
do mouse foi pressionado ou liberado.
Retorno:
Indica o código do botão (MOUSE_DIREITO, MOUSE_ESQUERDO, MOUSE_CENTRAL).
********************************/
int Pega_MouseBotao(){
    return jogo->Pega_Botao();
}

/********************************
A função Inicia_Desenho é responsável por preparar a janela do jogo para que os objetos gráficos
possam ser mostrados, além de desenhar a imagem de fundo do jogo.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
********************************/
void Inicia_Desenho()
{
    jogo->IniciaDesenho();
}

/********************************
A função Encerra_Desenho é responsável por encerrar o desenho que foi criado. Após a execução dos frames,
ele encerra a animação. Deve ser chamado toda vez que um frame acabar de ser executado.
********************************/
void Encerra_Desenho()
{
    jogo->EncerraDesenho();
}

/********************************
A função Salva_Screen é responsável por criar um arquivo Bitmap, contendo uma cópia da tela do jogo naquele momento.
Parâmetros:
nomeBMP (entrada, passagem por referência*): indica o nome do arquivo Bitmap que será salvo. O valor do parâmetro deve conter a extensão ".bmp".
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void Salva_Screen(char *nomeBMP)
{
    jogo->saveScreenshotBMP(nomeBMP);
}

/********************************
A função Jogo_Rodando é reponsável por retornar o funcionamento do jogo. Ela chama o método que
vai retornar um valor inteiro indicando se o jogo ainda está ativo ou não.
Retorno:
inteiro que indica se o jogo ainda está sendo executado (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int Jogo_Rodando()
{
    return jogo->rodando;
}

/********************************
A função Finaliza_Jogo é responsável por encerrar com a execução final do jogo. Após tudo ser realizado
a função pode ser chamada e ela irá realizar a interrupção do jogo e a sua finalização.
********************************/
void Finaliza_Jogo()
{
    delete jogo;
}

/********************************
A função Desenha_Retangulo() é responsável por desenhar um retângulo na tela em uma posição desejada pelo usuário.
O mesmo pode ser colocado em qualquer lugar do campo de visão da tela.
Parâmetros:
PosicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja colocar o retângulo.
PosicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja colocar o retângulo.
Altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura desse retângulo.
Largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura desse retângulo.
Cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho do retângulo;
********************************/
void Desenha_Retangulo(int PosicaoX, int PosicaoY, int Altura, int Largura, PIG_Cor cor)
{
    jogo->DesenhaRetangulo(PosicaoX,PosicaoY,Altura,Largura,cor);
}

/********************************
A função Espera() "congela" a tela do jogo por alguns milisegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Parâmetros:
tempo (entrada, passagem por valor): indica a quantidade de milisegundos durante a qual o jogo será pausado.
********************************/
void Espera(int tempo)
{
    SDL_Delay(tempo);
}

/********************************
A função Escrever() é responsável por exibir uma string na tela de jogo, escrevendo qualquer informação
deseja pelo usuário.
Parâmetros:
PosicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja começar a escrever a string.
PosicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja começar a escrever a string.
Altura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à altura dessa string.
Largura (entrada, passagem por valor): Valor onde o usuário irá fornecer o número correspondente em pixels à largura dessa string.
Cor (entrada, passagem por valor): indica a cor no sistema RGB para o desenho da string;
********************************/
void Escrever(char *frase, int PosicaoX, int PosicaoY, int Altura, int Largura, PIG_Cor cor)
{
    jogo->EscreveString(frase,PosicaoX,PosicaoY,Altura,Largura,cor);
}

/********************************
A função Cria_Objeto() é responsável por criar um objeto. Qualquer objeto que for necessário,
pode ser criado através dessa função. O objeto ainda não será desenhado, apenas criado dentro do jogo.
Parâmetros:
nomeArquivo (entrada, passagem por referência): string que informa o nome do arquivo da imagem do objeto a ser criado.
Retorno:
inteiro que representa o identificador único do objeto. Todas as operações subsequentes com este objeto deverão receber este identificador como parâmetro.
********************************/
int Cria_Objeto(char* nomeArquivo)
{
    return jogo->Cria_Objeto(0,0,nomeArquivo);
}

/********************************
A função Destroi_Objeto() é responsável por eliminar o objeto em questão do jogo.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser excluído.
********************************/
void Destroi_Objeto(int id_objeto)
{
    jogo->Destroi_Objeto(id_objeto);
}

/********************************
A função SetValorInt_Objeto() é responsável incorporar a um objeto um atributo inteiro.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo inteiro a ser associado ao objeto.
********************************/
void SetValorInt_Objeto(int id_objeto,int indice,int valor)
{
    jogo->objetos[id_objeto]->valoresInt[indice] = valor;
}


/********************************
A função SetValorFloat_Objeto() é responsável incorporar a um objeto um atributo float.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): relaciona um número inteiro ao atributo.
valor (entrada, passagem por valor): valor do atributo float a ser associado ao objeto.
********************************/
void SetValorFloat_Objeto(int id_objeto,int indice,int valor)
{
    jogo->objetos[id_objeto]->valoresFloat[indice] = valor;
}


/********************************
A função GetValorInt_Objeto() é responsável recuperar o valor de um atributo int relacionado a um objeto.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
Retorno:
Retorna o valor do atributo int solicitado pelo usuário.
********************************/
int GetValorInt_Objeto(int id_objeto,int indice)
{
    return jogo->objetos[id_objeto]->valoresInt[indice];
}

/********************************
A função GetValorFloat_Objeto() é responsável recuperar o valor de um atributo float relacionado a um objeto.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto.
indice (entrada, passagem por valor): indica o número do atributo que se deseja recuperar.
Retorno:
Retorna o valor do atributo float solicitado pelo usuário.
********************************/
float GetValorFloat_Objeto(int id_objeto,int indice)
{
    return jogo->objetos[id_objeto]->valoresFloat[indice];
}

/********************************
A função GetXY_Objeto() é responsável recuperar o valor da posição (X,Y) do objeto de acordo com o sistema de coordenadas do jogo.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto.
PosicaoX (saída, passagem por referencia): indica a posicao no eixo X do objeto.
PosicaoY (saída, passagem por referencia): indica a posicao no eixo Y do objeto.
********************************/
void GetXY_Objeto(int id_objeto,int *PosicaoX,int *PosicaoY)
{
    jogo->objetos[id_objeto]->GetXY(*PosicaoX,*PosicaoY);
}

/********************************
A função Move_Objeto() é responsável por movimentar um determinado obeto para uma nova posição informada.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser movido.
PosicaoX (entrada, passagem por valor): Valor da coordenada X da tela onde o usuário deseja reposicionar o objeto.
PosicaoY (entrada, passagem por valor): Valor da coordenada Y da tela onde o usuário deseja reposicionar o objeto.
********************************/
void Move_Objeto(int id_objeto,int PosicaoX,int PosicaoY)
{
    jogo->objetos[id_objeto]->Move(PosicaoX,PosicaoY);
}

/********************************
A função Define_Angulo() é responsável pela angulação de determinado objeto. A angulação é calculada em sentido
anti-horário a partir do eixo X (0 graus). O objeto será desenhado com a angulação informada no próximo comando
Desenha_Objeto(). A detecção de colisão não funciona com objetos fora da angulação padrão (0 graus).
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto.
angulo (entrada, passagem por valor): valor para indicar a angulação do objeto em graus.
********************************/
void Define_Angulo(int id_objeto, float angulo)
{
    jogo->objetos[id_objeto]->SetAngulo(angulo);
}

/********************************
A função Define_Pivo() define um ponto (X,Y) em relação ao ponto (0,0) do objeto, sobre o qual o objeto será
rotacionado quando a função Define_Angulo() for executada.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto.
PosicaoX (entrada, passagem por valor): Valor da coordenada X em relação ao ponto (0,0) do objeto.
PosicaoY (entrada, passagem por valor): Valor da coordenada Y em relação ao ponto (0,0) do objeto.
********************************/
void Define_Pivo(int id_objeto,int PosicaoX,int PosicaoY)
{
    jogo->objetos[id_objeto]->SetPivo(PosicaoX,PosicaoY);
}

/********************************
A função Define_Flip() é responsável por virar o objeto, invertendo-o em alguma direção. O objeto somente será
desenhado na nova orientação no próximo comando Desenha_Objeto().
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser virado.
valor (entrada, passagem por valor): valor do tipo de Flip. Pode ser FLIP_NENHUM (nenhum tipo de inversão),
FLIP_HORIZONTAL (inverte da esquerda para a direita), FLIP_VERTICAL (inverte de cima para baixo),
ou FLIP_HORIZ_VERT (inverte da esquerda para direita e de cima para baixo).
********************************/
void Define_Flip(int id_objeto,PIG_Flip valor)
{
    jogo->objetos[id_objeto]->SetFlip(valor);
}


/********************************
A função Define_Dimensoes() é responsável por delimitar a altura e a largura do objeto que será desenhado na tela,
independentemente do tamanho original do arquivo de imagem.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
Altura (entrada, passagem por valor): altura em pixels do objeto a ser desenhado.
Largura (entrada, passagem por valor): largura em pixels do objeto a ser desenhado.
********************************/
void Define_Dimensoes(int id_objeto, int Altura, int Largura)
{
    jogo->objetos[id_objeto]->SetDimensoes(Altura,Largura);
}

/********************************
A função Pega_Dimensoes() é responsável por recuperar a altura e a largura da área a ser usada
para desenhar o objeto na tela.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
Altura (saída, passagem por referência): altura em pixels do objeto a ser desenhado.
Largura (saída, passagem por referência): largura em pixels do objeto a ser desenhado.
********************************/
void Pega_Dimensoes(int id_objeto, int *Altura, int *Largura)
{
    jogo->objetos[id_objeto]->GetDimensoes(*Altura,*Largura);
}

/********************************
A função Define_Frame() é responsável por delimitar o posicionamento dos pixels do arquivo de imagem
que serão utilizados para representar o objeto na tela. Desta forma, nem toda a imagem será automaticamente
utilizada para representar o objeto.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
Altura (entrada, passagem por valor): altura em pixels do objeto a ser desenhado.
Largura (entrada, passagem por valor): largura em pixels do objeto a ser desenhado.
********************************/
void Define_Frame(int id_objeto,int xBitmap, int yBitmap,int Altura,int Largura)
{
    jogo->objetos[id_objeto]->CriaFrame(xBitmap,yBitmap,Altura,Largura);
}

/********************************
A função Modifica_Coloracao() é responsável por mesclar uma determinada cor com os pixels do arquivo de imagem.
Após a modificação, todos os desenhos deste objeto serão mostrados já com a mesclagem definida.
Para voltar ao padrão original de pixels, deve-se chamar a função, passando a cor branca (255,255,255).
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
cor (entrada,passagem por valor): cor do sistema RGB utilizada para mesclagem com o arquivo de imagem
********************************/
void Modifica_Coloracao(int id_objeto,PIG_Cor cor)
{
    jogo->objetos[id_objeto]->Modifica_Coloracao(cor);
}

/********************************
A função Desenha_Objeto() é responsável por desenhar um objeto na tela. O objeto será desenhado de acordo com todos as definições
de posição e ângulo informado até o momento. Além disso, se o objeto estiver virado (flipping), isso também será levado em consideração.
Parâmetros:
id_objeto (entrada, passagem por valor): identificador do objeto a ser desenhado.
********************************/
void Desenha_Objeto(int id_objeto)
{
    jogo->objetos[id_objeto]->Desenha();
}

/********************************
A função Testa_Colisão() é responsável por testar se dois objetos se colidiram ou não, ao passar
os identificadores dos objetos por parâmetro.
Parâmetros:
id_objeto1 (entrada, passagem por valor): Identificador do primeiro objeto.
id_objeto2 (entrada, passagem por valor): Identificador do segundo objeto.
Retorno:
Inteiro indicando se houve colisão (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int Testa_Colisao(int id_objeto1,int id_objeto2)
{
    Objeto obj1 = jogo->objetos[id_objeto1];
    Objeto obj2 = jogo->objetos[id_objeto2];
    return obj2->Colisao(obj1);
}

/********************************
A função Cria_GeradorParticulas() cria um novo gerador de partículas (GDP). As partículas em si precisam ser criadas
posteriormente através da função Cria_Particula(), passando o identificador do GDP como parâmetro.
Parâmetros:
maxParticulas (entrada, passagem por valor): informa o maior número de partículas que o gerador terá simultaneamente. O maior valor aceito é 1000 partículas.
nomeArquivo (entrada, passagem por referência): indica o caminho relativo ou absoluto do arquivo de imagem,
 que será utilizado para cada partícula do GDP.
********************************/
int Cria_GeradorParticulas(int maxParticulas,char* nomeArquivo)
{
    return jogo->Cria_GeradorParticulas(maxParticulas,nomeArquivo);
}

/********************************
A função Destroi_GeradorParticulas() encerra um gerador de partículas (GDP). Todas as partículas relacionadas a ele também são finalizadas
neste momento.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
********************************/
void Destroi_GeradorParticulas(int id_gerador)
{
    jogo->Destroi_GeradorParticulas(id_gerador);
}

/********************************
A função Move_GeradorParticulas() reposiciona um gerador de partículas (GDP). Na prática, isto significa que as novas partículas que
forem criadas posteriormente terão esse ponto de origem.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
PosicaoX (entrada, passagem por valor): informa a nova posição X do GDP, em relação ao sistema de coordenadas do jogo.
PosicaoY (entrada, passagem por valor): informa a nova posição Y do GDP, em relação ao sistema de coordenadas do jogo.
********************************/
void Move_GeradorParticulas(int id_gerador,int PosicaoX,int PosicaoY)
{
    jogo->geradores[id_gerador]->Move(PosicaoX,PosicaoY);
}

/********************************
A função MudaDirecao_Particulas() modifica a direção na qual as partículas se movimentarão após serem criadas.
Somente as partículas criadas posteriormente seguirão a direção especificada.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
valorX (entrada, passagem por valor): informa a componente X da direção a ser definida para as partículas.
valorY (entrada, passagem por valor): informa a componente Y da direção a ser definida para as partículas.
********************************/
void MudaDirecao_Particulas(int id_gerador,int valorX,int valorY)
{
    jogo->geradores[id_gerador]->MudaDirecao(valorX,valorY);
}

/********************************
A função Cria_Particula() adiciona uma nova partícula ao jogo relacionada com o GDP passado como parâmetro.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
Retorno:
inteiro indicando se a partícula foi criada (valor maior ou igual a zero) ou não (valor menor do que zero).
A partícula não será criada se já houver o número máximo de partículas ativas.
********************************/
int Cria_Particula(int id_gerador)
{
    return jogo->geradores[id_gerador]->CriaParticula();
}

/********************************
A função Move_Particulas() faz com que todas as partícula ativas do GDP em questão se movimentem de acordo com as componentes
X e Y passadas na função MudaDirecao_Particulas(). As partículas que saírem da tela de jogo ou aqueles que já existerm a mais de 10000 segundos
serão consideradas inativas e deixarão de existir.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
********************************/
void Move_Particulas(int id_gerador)
{
    jogo->geradores[id_gerador]->MoveParticulas();
}

/********************************
A função Quantidade_ParticulasAtivas() indica quantas partículas do GDP em questão ainda estão ativas. As partículas deixam de
ser ativas quando saem da tela do jogo, quando colidem com algum objeto ou depois de 10000 segundos de vida.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
Retorno:
inteiro que indica o número de partículas ativas.
********************************/
int Quantidade_ParticulasAtivas(int id_gerador)
{
    return jogo->geradores[id_gerador]->ativas;
}

/********************************
A função Desenha_Particulas() desenha todas as partículas ativas do GDP na posição que estiverem.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
********************************/
void Desenha_Particulas(int id_gerador)
{
    jogo->geradores[id_gerador]->Desenha();
}

/********************************
A função Colisao_Particulas() indica se houve colisão de alguma partícula ativa do GDP com um outro objeto específico, através do seu identificador.
Parâmetros:
id_gerador (entrada, passagem por valor): informa o identificador do GDP passado como retorno da função Cria_GeradorParticulas().
id_objeto (entrada, passagem por valor): identificador do objeto que pode ter colidido com as partículas do GDP.
Retorno:
inteiro que indica se houve colisão de alguma partícula ativa do GDP (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/
int Colisao_Particulas(int id_gerador,int id_objeto)
{
    Objeto obj = jogo->objetos[id_objeto];
    return jogo->geradores[id_gerador]->Colisao(obj);
}

/********************************
A função Cria_Timer() é responsável por criar um timer (temporizador). Após a criação o tempo decorrido
poderá ser obtido a partir da função Tempo_Decorrido(), informando o identificador que é passado na resposta.
Retorno:
inteiro que identifica o timer criado.
********************************/
int Cria_Timer()
{
    return jogo->Cria_Timer();
}

/********************************
A função Tempo_Decorrido() é responsável por informar o tempo decorrido desde a criação do timer
até a hora em que a função for chamada.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
Retorno:
número real indicando o tempo (em segundos) desde a criação do timer.
********************************/
float Tempo_Decorrido(int id_timer)
{
    return jogo->timers[id_timer]->GetTempoDecorrido();
}

/********************************
A função Pausa() é responsável por realizar uma pausa na contagem do tempo de um timer. Após a despausa,
o timer continuará a contar o tempo normalmente.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void Pausa_Timer(int id_timer)
{
    jogo->timers[id_timer]->Pausa();
}

/********************************
A função Despausa() é responsável por retomar a contagem do tempo de um timer após uma pausa.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void Despausa_Timer(int id_timer)
{
    jogo->timers[id_timer]->Despausa();
}

/********************************
A função Reinicia_Timer() é responsável por zerar a contagem do tempo de um timer, idependente do tempo já decorrido.
Na prática, é equivalente a encerrer um temporizador e recriá-lo em seguida.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void Reinicia_Timer(int id_timer)
{
    jogo->timers[id_timer]->Reinicia();
}

/********************************
A função Destroi_Timer() é responsável por encerrar a utilização de timer.
Seu identificador não poderá ser utilizado após a função ser executada.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void Destroi_Timer(int id_timer)
{
    jogo->Destroi_Timer(id_timer);
}
