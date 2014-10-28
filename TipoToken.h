#ifndef TIPOTOKEN_H
#define TIPOTOKEN_H

#include <QString>
#include <QHash>
#include <QRegExp>
#include <iostream>

class TipoToken {
private:
    QString _tipoDeToken;
    QHash <QString, int> palavrasReservadas;
    QHash <QString, int> simbolos;
    QHash <QString, int> operadoresLogicos;
    QHash <QString, int> operadoresMatematicos;
    QHash <QString, int> identificadores;
    QHash <QString, int> valoresAlfa;
    QHash <int, int> valoresInteiros;
    QHash <float, int> valoresFlutuante;
    QRegExp * regExpIdentificador;
    QRegExp * regExpAlfa;
    QRegExp * regExpFlutuante;
    QRegExp * regExpInteiro;

public:
    TipoToken();
    QString identificaTipoDoToken(QString token);
    QString getTipoDeToken();
};

#endif // TIPOTOKEN_H
