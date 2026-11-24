#ifndef DSU_HPP
#define DSU_HPP

#include "Lista.hpp"

class DSU {
    public:
        void Make(int x);
        int Find(int x);
        void Union(int x, int y);
        
        // Variáveis de análise
        Analise Get_Analise() const; void Zerar_Analise();
    private:
        mutable Analise ana;

        Lista<int> pai;
        Lista<int> rank;
};

#endif