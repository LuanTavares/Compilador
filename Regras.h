#ifndef REGRAS_H
#define REGRAS_H
#include <QString>
#include <QHash>
#include <QRegExp>
#include <iostream>

class Regras {

private:
    QRegExp * definicaoPrograma;
    QRegExp * definicaoVariavel;
    QRegExp * operacoesMatematicas;
    QRegExp * atribuicao;
    QRegExp * importacao;
    QRegExp * definicaoEAtribuicao;
    QRegExp * concatenacaoDeString;
    QRegExp * condicaoInicio;
    QRegExp * condicaoMeio;
    QRegExp * condicaoFim;
    int qtd;


public:
    Regras();
    QList<QString> *validaLinha(QList <QString> * linhas);


};

#endif // REGRAS_H
