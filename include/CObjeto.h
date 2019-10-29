class CObjeto{

protected:
    int alt, larg, alt_tela;
    bool visivel;
    float angulo;
    SDL_Rect dest;
    SDL_Rect origem;
    SDL_Point pivo;
    SDL_Renderer* renderer;
    SDL_Texture* text;
    SDL_RendererFlip flip;
    SDL_Surface* bitmap;
public:
    int x,y;
    int estado;
    int valoresInt[100];
    float valoresFloat[100];
    CObjeto(int posx,int posy,int altura_tela, SDL_Renderer* renderizador,char* nomeArquivo){

        estado = 0;
        visivel = true;
        x = posx;
        y = posy;
        alt_tela = altura_tela;
        renderer = renderizador;
        angulo = 0;
        pivo.x = pivo.y = 0;
        memset(valoresInt,0,sizeof(int)*100);
        memset(valoresFloat,0,sizeof(float)*100);

        flip = SDL_FLIP_NONE;
        bitmap = IMG_Load(nomeArquivo);
        if (!bitmap) printf("Erro ao ler arquivo: %s\n",nomeArquivo);
        alt = bitmap->h;
        larg = bitmap->w;

        dest.x = x;
        dest.y = alt_tela-y-alt;
        dest.h = alt;
        dest.w = larg;

        origem.x = origem.y = 0;
        origem.h = alt;
        origem.w = larg;

        Uint8 red, green, blue, alpha;
        SDL_PixelFormat *fmt = bitmap->format;
        SDL_LockSurface(bitmap);
        if (fmt->BitsPerPixel==8){
            Uint8 *pixel;

            pixel = (Uint8*)bitmap->pixels;
            SDL_GetRGBA(*pixel,bitmap->format,&red,&green,&blue,&alpha);
        }else{
            Uint32 *pixel;

            pixel = (Uint32*)bitmap->pixels;
            SDL_GetRGBA(*pixel,bitmap->format,&red,&green,&blue,&alpha);
        }

        SDL_UnlockSurface(bitmap);
        SDL_SetColorKey( bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, red, green, blue) );
        text = SDL_CreateTextureFromSurface(renderizador, bitmap);

    }
    ~CObjeto(){
        SDL_DestroyTexture(text);
        SDL_FreeSurface(bitmap);
    }
    char *GetPixels(){
        return (char*)bitmap->pixels;
    }
    void AtualizaPixels(){
        SDL_DestroyTexture(text);
        text = SDL_CreateTextureFromSurface(renderer, bitmap);
    }
    void CriaFrame(int xBitmap, int yBitmap,int altura,int largura){
        origem.x = xBitmap;
        origem.y = yBitmap;
        origem.h = altura;
        origem.w = largura;
    }
    void GetXY(int &x,int &y){
        x = this->x;
        y = this->y;
    }
    void Modifica_Coloracao(PIG_Cor cor){
        SDL_SetTextureColorMod(text,cor.r,cor.g,cor.b);
    }
    void Desenha(){
        SDL_RenderCopyEx(renderer, text, &origem,&dest,angulo,&pivo,flip);
    }

    int Colisao(CObjeto* outro){
        int x1,x2,y1,y2;
        int a1,a2,b1,b2;
        x1 = this->x;
        x2 = x1 + this->larg;
        y1 = this->y;
        y2 = y1+this->alt;

        a1 = outro->x;
        a2 = a1+outro->larg;
        b1 = outro->y;
        b2 = b1+outro->alt;

        if (x1>=a1 && x1<=a2 && y1>=b1 && y1<=b2){
            return 1;
        }
        if (x1>=a1 && x1<=a2 && y2>=b1 && y2<=b2){
            return 1;
        }
        if (x2>=a1 && x2<=a2 && y1>=b1 && y1<=b2){
            return 1;
        }
        if (x2>=a1 && x2<=a2 && y2>=b1 && y2<=b2){
            return 1;
        }
        if (a1>=x1 && a1<=x2 && b1>=y1 && b1<=y2){
            return 1;
        }
        if (a2>=x1 && a2<=x2 && b2>=y1 && b2<=y2){
            return 1;
        }

        return 0;
    }

    void SetFlip(SDL_RendererFlip valor){
        flip = valor;
    }

    void SetAngulo(float a){
        angulo = -a;
    }

    void SetPivo(int px,int py){
        pivo.x = px;
        pivo.y = py;
    }
    void Move(int nx,int ny){
        x = nx;
        y = ny;
        dest.x = nx;
        dest.y = alt_tela-ny-alt;
        dest.h = alt;
        dest.w = larg;
    }
    void SetDimensoes(int altura,int largura){
        dest.h = alt = altura;
        dest.w = larg = largura;
        dest.x = x;
        dest.y = alt_tela-y-alt;
    }
    void GetDimensoes(int &altura, int &largura){
        altura = alt;
        largura = larg;
    }
};

typedef CObjeto* Objeto;
