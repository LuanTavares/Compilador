#include "Token.h"

Token::Token(QString valor) {
    _valor = valor;
    _linha = 0;
    identificaTipoDoToken(_valor);
}

QString Token::getToken() {
    return _valor;
}

QString Token::getTipoToken() {
    return getTipoDeToken();
}
