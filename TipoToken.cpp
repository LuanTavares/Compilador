#include "TipoToken.h"

TipoToken::TipoToken() {

    // Inicializa as hash com os valores pré definidos
    palavrasReservadas["definir"] = 1;
    palavrasReservadas["inteiro"] = 2;
    palavrasReservadas["alfa"] = 3;
    palavrasReservadas["flutuante"] = 4;
    palavrasReservadas["se"] = 5;
    palavrasReservadas["senao"] = 6;
    palavrasReservadas["enquanto"] = 7;
    palavrasReservadas["inicio"] = 8;
    palavrasReservadas["E"] = 9;
    palavrasReservadas["OU"] = 10;
    palavrasReservadas["imprimir"] = 11;

    simbolos["("] = 1;
    simbolos[")"] = 2;
    simbolos["{"] = 3;
    simbolos["}"] = 4;
    simbolos[";"] = 5;

    operadoresLogicos["="] = 1;
    operadoresLogicos["=="] = 2;
    operadoresLogicos["<>"] = 3;
    operadoresLogicos[">"] = 4;
    operadoresLogicos[">="] = 5;
    operadoresLogicos["<"] = 6;
    operadoresLogicos["<="] = 7;

    operadoresMatematicos["+"] = 1;
    operadoresMatematicos["-"] = 2;
    operadoresMatematicos["*"] = 3;
    operadoresMatematicos["/"] = 4;

    // Inicializa as expressões regulares
    regExpFlutuante = new QRegExp("([0-9])*(,)([0-9])*");
    regExpInteiro = new QRegExp("([0-9])*");
    regExpAlfa = new QRegExp("'([A-za-z0-9])*'");
    regExpIdentificador = new QRegExp("([A-Za-z])([A-Za-z0-9])*");
}

QString TipoToken::identificaTipoDoToken(QString token) {

    if(palavrasReservadas.contains(token)) {        // Verifica se o Token é uma palavra reservada
        _tipoDeToken = "RESERVADO";
    } else if (simbolos.contains(token)) {          // Verifica se o Token é um símbolo
        _tipoDeToken = "SIMBOLO";
    } else if (operadoresLogicos.contains(token)) {        // Verifica se o Token é um Operador Lógico
        _tipoDeToken = "OPLOGICO";
    } else if (operadoresMatematicos.contains(token)) {     // Verifica se o Token é um Operador Matemático
        _tipoDeToken = "OPMATEMATICO";
    } else if (regExpIdentificador->exactMatch(token)) {       // Se o Token não é nenhum dos anteriores então verifica se é um identificado válido
        _tipoDeToken = "IDENTIFICADOR";
    } else if (regExpAlfa->exactMatch(token)) {                // Verifica se o Token é um Alfa
        _tipoDeToken = "ALFA";
    } else if (regExpFlutuante->exactMatch(token)) {           // Verifica se o Token é um Flutuante
        _tipoDeToken = "FLUTUANTE";
    } else if (regExpInteiro->exactMatch(token)) {             // verifica se o Token é um Inteiro
        _tipoDeToken = "INTEIRO";
    } else {                                        // Se não é nenhum dos anteriores é erro de sintaxe
        _tipoDeToken = "NAO";
    }
    return _tipoDeToken;
}

QString TipoToken::getTipoDeToken() {
    return _tipoDeToken;
}
