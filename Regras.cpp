#include "Regras.h"

Regras::Regras() {
    // Regra para definição do programa
    definicaoPrograma = new QRegExp("RESERVADO RESERVADO RESERVADO SIMBOLO SIMBOLO SIMBOLO ");
    // Regra para definição de variável
    definicaoVariavel = new QRegExp("RESERVADO RESERVADO IDENTIFICADOR SIMBOLO ");
    // Regra para definição de variável e atribuição
    definicaoEAtribuicao = new QRegExp("RESERVADO RESERVADO IDENTIFICADOR OPLOGICO (INTEIRO|FLUTUANTE|IDENTIFICADOR|ALFA) SIMBOLO ");
    // Regra para atribuição
    atribuicao = new QRegExp("IDENTIFICADOR OPLOGICO (INTEIRO|FLUTUANTE|IDENTIFICADOR|ALFA) SIMBOLO ");
    // Regra para operação matemática
    operacoesMatematicas = new QRegExp("IDENTIFICADOR OPLOGICO (INTEIRO|FLUTUANTE|IDENTIFICADOR)( OPMATEMATICO (INTEIRO|FLUTUANTE|IDENTIFICADOR))* SIMBOLO ");
    // Regra para concatenação de strings
    concatenacaoDeString = new QRegExp("IDENTIFICADOR OPLOGICO (ALFA|IDENTIFICADOR) (OPMATEMATICO (ALFA|IDENTIFICADOR))* SIMBOLO ");
    // Regras para Condição
    condicaoInicio = new QRegExp("RESERVADO SIMBOLO (((INTEIRO|FLUTUANTE|IDENTIFICADOR|ALFA) OPLOGICO (INTEIRO|FLUTUANTE|IDENTIFICADOR|ALFA))( RESERVADO (INTEIRO|FLUTUANTE|IDENTIFICADOR|ALFA) OPLOGICO (INTEIRO|FLUTUANTE|IDENTIFICADOR|ALFA))*) SIMBOLO SIMBOLO ");
    condicaoMeio = new QRegExp("SIMBOLO RESERVADO SIMBOLO ");
    condicaoFim = new QRegExp("SIMBOLO ");
    importacao = new QRegExp("RESERVADO ALFA SIMBOLO ");

    qtd = 0;


}

QList <QString> * Regras::validaLinha(QList<QString> * linhas) {
    QList <QString> * retorno = new QList <QString>;
    for (int i=0; i<linhas->size(); i++) {
        QString tokens = linhas->at(i);
        if (definicaoPrograma->exactMatch(tokens)) {
            retorno->insert(i,"DEFINICAO DO PROGRAMA");
            qtd++;
        } else if (definicaoVariavel->exactMatch(tokens)){
            retorno->insert(i,"DEFINICAO DE VARIAVEL");
        } else if (definicaoEAtribuicao->exactMatch(tokens)) {
            retorno->insert(i,"DEFINICAO E ATRIBUICAO DE VARIAVEL");
        } else if (atribuicao->exactMatch(tokens)) {
            retorno->insert(i,"ATRIBUICAO");
        } else if (operacoesMatematicas->exactMatch(tokens)) {
            retorno->insert(i,"OPERACAO MATEMATICA");
        } else if (concatenacaoDeString->exactMatch(tokens)) {
            retorno->insert(i,"CONCATENACAO DE STRING");
        } else if (condicaoInicio->exactMatch(tokens)) {
            retorno->insert(i,"INICIO CONDICAO");
            qtd++;
        } else if (condicaoMeio->exactMatch(tokens)) {
            retorno->insert(i,"MEIO CONDICAO");
        } else if (condicaoFim->exactMatch(tokens)) {
            retorno->insert(i,"FIM ");
            qtd--;
        } else if (importacao->exactMatch(tokens)) {
            retorno->insert(i,"DIRETIVA ");
        } else {
            retorno->insert(i,"INDEFINIDO");
        }
    }

    if (!retorno->contains("DEFINICAO DO PROGRAMA")) {
        retorno->push_back("Erro sintatico, nao foi localizado a definicao do programa.");
    }

    if(qtd > 0) {
        retorno->push_back("Erro sintatico, falta }");
    }

    if(qtd < 0) {
        retorno->push_back("Erro sintatico, falta {");
    }



    return retorno;
}
