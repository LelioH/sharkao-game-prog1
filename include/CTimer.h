class CTimer{

private:
        long int inicio;
        long int pausa;
        bool pausado;
public:
    CTimer(){
        inicio = clock();
        pausado = false;
    }
    ~CTimer(){
    }
    float GetTempoDecorrido(){
        if (pausado) return (pausa-inicio)/1000.0;
        else         return (clock()-inicio)/1000.0;
    }
    void Pausa(){
        pausado = true;
        pausa = clock();
    }
    void Despausa(){
        long int decorrido = pausa - inicio;
        inicio = clock() - decorrido;
        pausado = false;
    }
    void Reinicia(){
        pausado = false;
        inicio = clock();
    }
};

typedef CTimer* Timer;
