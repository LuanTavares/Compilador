#ifndef TELAPRINCIPAL_H
#define TELAPRINCIPAL_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <iostream>
#include <QList>
#include <Token.h>

namespace Ui {
    class TelaPrincipal;
}

class TelaPrincipal : public QMainWindow {
    Q_OBJECT

private:
    Ui::TelaPrincipal *ui;
    QString diretorio;
    QFile * arquivo;
    QString conteudoDoArquivo;
    QList <Token *> tokens;

public:
    explicit TelaPrincipal(QWidget *parent = 0);
    ~TelaPrincipal();

public slots:
    void limpaTela();
    void abrirArquivo();
    void novoArquivo();
    void salvarArquivo();
    void compilaCodigoFonte();
};

#endif // TELAPRINCIPAL_H
