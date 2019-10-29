#include "CObjeto.h"
#include "CTimer.h"
#include "CGeradorParticulas.h"

#define MAX_OBJETOS 500
#define MAX_TIMERS 500
#define MAX_GERADORPARTICULAS 100
#define MAX_POLIGONOS 500

class CJogo{

private:

    SDL_Texture* text_fundo;
    TTF_Font *gFont;
    PIG_Cor corFonte;
    SDL_Event event;
    int livresObjetos[MAX_OBJETOS+1];
    int livresTimers[MAX_TIMERS+1];
    int livresGeradores[MAX_GERADORPARTICULAS+1];
    PIG_Teclado teclado;
public:
    SDL_Window* window;
    static SDL_Renderer* renderer;
    static int altura,largura;
    static int estado;
    static int rodando;
    static Objeto objetos[MAX_OBJETOS];
    static Timer timers[MAX_TIMERS];
    static GeradorParticulas geradores[MAX_GERADORPARTICULAS];
    CJogo(int alt,int larg, char *nome){
        int codigo;
        rodando = true;
        teclado = SDL_GetKeyboardState(NULL);
        altura = alt;
        largura = larg;
        estado = 0;
		text_fundo = NULL;
        if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
            printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
            codigo = -1;
        }else{
            window = SDL_CreateWindow( nome, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, larg, alt, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_SWSURFACE );
            if( window == NULL ){
                printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
                codigo = -2;
            }else{
                codigo = 0;
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
            }
        }
        TTF_Init();
        gFont = TTF_OpenFont( "fontes//arial.ttf", 36 );
        for (int i=0;i<MAX_OBJETOS;i++){
            objetos[i] = NULL;
            livresObjetos[i+1]=i;
        }
        livresObjetos[0] = MAX_OBJETOS;
        for (int i=0;i<MAX_TIMERS;i++){
            timers[i] = NULL;
            livresTimers[i+1]=i;
        }
        livresTimers[0] = MAX_TIMERS;
        for (int i=0;i<MAX_GERADORPARTICULAS;i++){
            geradores[i] = NULL;
            livresGeradores[i+1]=i;
        }
        livresGeradores[0] = MAX_GERADORPARTICULAS;
    }
    void DefineFundo(char *nomeArquivo){
        SDL_Surface* bitmap = SDL_LoadBMP(nomeArquivo);
        if (text_fundo) SDL_DestroyTexture(text_fundo);
        text_fundo = SDL_CreateTextureFromSurface(renderer,bitmap);
        SDL_FreeSurface(bitmap);
    }
    PIG_Evento TrataEventos(){
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) rodando = false;
            return event.type;
        }
        return 0;
    }
    int Pega_Botao(){
        if (event.type != MOUSE_PRESSIONADO) return 0;
        return event.button.button;
    }
    int Pega_MouseXY(int *mx,int *my){
        if (event.type != MOUSE_PRESSIONADO &&
            event.type != MOUSE_LIBERADO &&
            event.type != MOUSE_MOVIDO) return 0;
        *mx = event.motion.x;
        *my = altura-event.motion.y;
        return 1;
    }
    PIG_Teclado PegaTeclado(){
        return teclado;
    }
    void IniciaDesenho(){
        if (text_fundo==NULL) SDL_RenderClear( renderer );
        else SDL_RenderCopy(renderer,text_fundo,NULL,NULL);
    }
    void EncerraDesenho(){
        SDL_RenderPresent(renderer);
    }
    void DesenhaRetangulo(int x, int y, int altura, int largura, PIG_Cor cor){
        SDL_Rect rect;
        rect.x = x;
        rect.y = this->altura-(y+altura);
        rect.h = altura;
        rect.w = largura;

        SDL_SetRenderDrawColor(renderer, cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(renderer,&rect);
    }
    void EscreveString(char* str, int x,int y,int altura,int largura,PIG_Cor cor){
        SDL_Rect rect;
        rect.x = x;
        rect.y = this->altura-(y+altura);
        rect.h = altura;
        rect.w = largura;

        SDL_Surface *surface = TTF_RenderText_Blended(gFont,str,cor);
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);

        SDL_RenderCopy(renderer,text,NULL,&rect);
        SDL_DestroyTexture(text);
    }
    ~CJogo(){
        for (int i=0;i<MAX_OBJETOS;i++){
            if (objetos[i]) delete objetos[i];
        }
        for (int i=0;i<MAX_TIMERS;i++){
            if (timers[i]) delete timers[i];
        }
        for (int i=0;i<MAX_GERADORPARTICULAS;i++){
            if (geradores[i]) delete geradores[i];
        }
        TTF_CloseFont(gFont);
        TTF_Quit();
        if (text_fundo) SDL_DestroyTexture(text_fundo);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }
    int Cria_Objeto(int posx,int posy,char* nomeArquivoBMP){
        int resp=-1;
        int tam = livresObjetos[0];
        if (tam > 0){
            resp = livresObjetos[1];
            livresObjetos[1] = livresObjetos[tam];
            livresObjetos[0]--;
            objetos[resp] = new CObjeto(posx,posy,altura,renderer,nomeArquivoBMP);
        }
        return resp;
    }
    void Destroi_Objeto(int id_objeto){
        livresObjetos[0]++;
        int tam = livresObjetos[0];
        livresObjetos[tam] = id_objeto;
        delete objetos[id_objeto];
        objetos[id_objeto] = NULL;
    }
    int Cria_Timer(){
        int resp=-1;
        int tam = livresTimers[0];
        if (tam > 0){
            resp = livresTimers[1];
            livresTimers[1] = livresTimers[tam];
            livresTimers[0]--;
            timers[resp] = new CTimer();
        }
        return resp;
    }
    void Destroi_Timer(int id_timer){
        livresTimers[0]++;
        int tam = livresTimers[0];
        livresTimers[tam] = id_timer;
        delete timers[id_timer];
        timers[id_timer] = NULL;
    }
    int Cria_GeradorParticulas(int maxParticulas,char* nomeArquivoBMP){
        int resp=-1;
        int tam = livresGeradores[0];
        if (tam > 0){
            resp = livresGeradores[1];
            livresGeradores[1] = livresGeradores[tam];
            livresGeradores[0]--;
            geradores[resp] = new CGeradorParticulas(maxParticulas,altura,renderer,nomeArquivoBMP);
        }
        return resp;
    }
    void Destroi_GeradorParticulas(int id_gerador){
        livresGeradores[0]++;
        int tam = livresGeradores[0];
        livresGeradores[tam] = id_gerador;
        delete geradores[id_gerador];
        geradores[id_gerador] = NULL;
    }
    void GetPixel(int x,int y,int *r,int *g,int *b) {
        if (x<0 || x>=largura  ||y<0 ||y>=altura) return;

        SDL_Surface* saveSurface = NULL;
        SDL_Surface* infoSurface = NULL;
        infoSurface = SDL_GetWindowSurface(window);
        if (infoSurface != NULL) {
            unsigned char * pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
            if (pixels != 0) {
                if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) == 0) {
                    Uint8 mr,mg,mb;
                    Uint32 *p = (Uint32*) pixels;
                    p += (x+(altura-y)*largura);
                    SDL_GetRGB(*p,(const SDL_PixelFormat*) &infoSurface->format->format,&mr,&mg,&mb);
                    *r = mr;
                    *g = mg;
                    *b = mb;
                }
                delete[] pixels;
            }
            SDL_FreeSurface(infoSurface);
        }
    }

    void SetPixel(int x,int y,Uint8 r,Uint8 g,Uint8 b) {
        if (x<0 || x>=largura  ||y<0 ||y>=altura) return;

        SDL_Surface* infoSurface = NULL;
        infoSurface = SDL_GetWindowSurface(window);
        if (infoSurface != NULL) {
            SDL_LockSurface(infoSurface);
            unsigned char * pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
            if (pixels != 0) {
                if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) == 0) {
                    Uint8 mr,mg,mb;
                    Uint32 *p = (Uint32*) pixels;
                    p += (x+(altura-y)*largura);
                    Uint32 cor = SDL_MapRGB((const SDL_PixelFormat*) &infoSurface->format->format,r,g,b);
                    *p = cor;
                    SDL_UnlockSurface(infoSurface);
                }
                delete[] pixels;
            }
            SDL_FreeSurface(infoSurface);
        }
    }

    void saveScreenshotBMP(char *nome) {
        SDL_Surface* saveSurface = NULL;
        SDL_Surface* infoSurface = NULL;
        infoSurface = SDL_GetWindowSurface(window);
        if (infoSurface != NULL) {
            unsigned char * pixels = new unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
            if (pixels != 0) {
                if (SDL_RenderReadPixels(renderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) == 0) {
                    saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);
                    if (saveSurface == NULL) return;
                    SDL_SaveBMP(saveSurface, nome);
                    SDL_FreeSurface(saveSurface);
                    saveSurface = NULL;
                }
                delete[] pixels;
            }
            SDL_FreeSurface(infoSurface);
            infoSurface = NULL;
        }
    }
};

int CJogo::altura;
int CJogo::largura;
int CJogo::rodando;
int CJogo::estado;

Objeto CJogo::objetos[MAX_OBJETOS];
Timer CJogo::timers[MAX_TIMERS];
GeradorParticulas CJogo::geradores[MAX_GERADORPARTICULAS];
SDL_Renderer* CJogo::renderer;


typedef CJogo* Jogo;
