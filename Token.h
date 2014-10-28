#ifndef TOKEN_H
#define TOKEN_H
#include <QString>
#include "TipoToken.h"
class Token : public TipoToken {
private:
    int _linha;
    QString _valor;
public:
    Token(QString valor);
    QString getToken();
    QString getTipoToken();
};

#endif // TOKEN_H
