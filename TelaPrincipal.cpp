#include "TelaPrincipal.h"
#include "ui_TelaPrincipal.h"
#include <qdebug.h>

TelaPrincipal::TelaPrincipal(QWidget *parent) : QMainWindow(parent), ui(new Ui::TelaPrincipal) {
    ui->setupUi(this);

    // Conecta os botões a uma ação
    connect(ui->pushButtonLimpar, SIGNAL(clicked()), this, SLOT(limpaTela()));
    connect(ui->pushButtonAbrir, SIGNAL(clicked()), this, SLOT(abrirArquivo()));
    connect(ui->pushButtonNovo,SIGNAL(clicked()), this, SLOT(novoArquivo()));
    connect(ui->pushButtonSalvar, SIGNAL(clicked()), this, SLOT(salvarArquivo()));
    connect(ui->pushButtonCompilar, SIGNAL(clicked()), this, SLOT(compilaCodigoFonte()));
}

TelaPrincipal::~TelaPrincipal() {
    delete ui;
}


// Slots
void TelaPrincipal::limpaTela() {
    ui->textEditCodigoFonte->setText("");
    ui->textEditCodigoIntermediario->setText("");
    ui->textEditCodigoCompilado->setText("");
    tokens.clear();
}

void TelaPrincipal::abrirArquivo() {
    diretorio = QFileDialog::getOpenFileName(this, tr("Abrir Arquivo"), QDir::currentPath(), tr("Files (*.txt)"));
    if (diretorio.size() > 0) {
        arquivo = new QFile(diretorio);
        if (!arquivo->open(QIODevice::ReadWrite | QIODevice::Text))
            std::cout << "Não foi possível abrir o arquivo: " << diretorio.toStdString() << std::endl;
        else {
            QByteArray byteArrayConteudoDoArquivo = arquivo->readAll();
            char * charConteudoDoArquivo = byteArrayConteudoDoArquivo.data();
            conteudoDoArquivo = QString(charConteudoDoArquivo);
            ui->textEditCodigoFonte->setPlainText(conteudoDoArquivo);
            arquivo->close();

            ui->textEditCodigoCompilado->setEnabled(true);
            ui->textEditCodigoIntermediario->setEnabled(true);
            ui->textEditCodigoFonte->setEnabled(true);
        }
    } else {
        std::cout << "Não foi possível localizar o diretório: "<< diretorio.toStdString() << std::endl;
    }
}

void TelaPrincipal::novoArquivo() {
    diretorio = QFileDialog::getExistingDirectory(this,tr("Local do novo Arquivo"),QDir::currentPath());
    diretorio += "/CodigoCompilado.txt";
    ui->textEditCodigoFonte->setText("");
    ui->textEditCodigoIntermediario->setText("");
    ui->textEditCodigoCompilado->setText("");

    if (diretorio.size() > 0) {
        arquivo = new QFile(diretorio);
        if (!arquivo->open(QIODevice::ReadWrite | QIODevice::Text))
            std::cout << "Não foi possível abrir o arquivo: " << diretorio.toStdString() << std::endl;
        else {
            arquivo->close();
            ui->textEditCodigoCompilado->setEnabled(true);
            ui->textEditCodigoIntermediario->setEnabled(true);
            ui->textEditCodigoFonte->setEnabled(true);
        }
    } else {
        std::cout << "Não foi possível localizar o diretório: "<< diretorio.toStdString() << std::endl;
    }

}

void TelaPrincipal::salvarArquivo() {
    if (diretorio.size() > 0) {
        arquivo = new QFile(diretorio);
        if (!arquivo->open(QIODevice::ReadWrite | QIODevice::Text))
            std::cout << "Não foi possível abrir o arquivo: " << diretorio.toStdString() << std::endl;
        else {
            arquivo->remove();
            arquivo = new QFile(diretorio);
            if (!arquivo->open(QIODevice::WriteOnly | QIODevice::Text))
                std::cout << "Não foi possível abrir o arquivo: " << diretorio.toStdString() << std::endl;
            else {
                QString codigoFonte = ui->textEditCodigoFonte->toPlainText();
                arquivo->write(codigoFonte.toLatin1());
                conteudoDoArquivo = codigoFonte;
                arquivo->close();
            }
        }
    } else {
        std::cout << "Não foi possível salvar o arquivo no diretório: "<< diretorio.toStdString() << std::endl;
    }
}

void TelaPrincipal::compilaCodigoFonte() {
    // Salva o que foi digitado para carregar as variáveis necessárias
    salvarArquivo();

    // Joga o código fonte para uma variável temporária
    QByteArray dialogConteudo = conteudoDoArquivo.toLatin1();

    QList <char> token; // Armazena o valor do token em char
    int ref = 0; // Referência para percorrer cada char da variavel token
    while (dialogConteudo.size() > 0) { // Enquanto tiver código fonte faça
        QString dialog; // Variável que armazena o token em String
        token.insert(ref, dialogConteudo.at(0)); // Armazena o primeiro char do token
        if (token.at(ref) ==  ' ' || token.at(ref) ==  '\n') { // O char atual é um espaço ?
            for (int i=0; i < ref; i++) // Se for, percorre da referência até a posição do espaço
                dialog += token.at(i); // Cria uma String com os char da referencia até o espaço
            if (dialog.size() > 0) // Só cria novo token se for identificado algum valor para o token (evita criar token para o enter)
                tokens.insert(tokens.size(),new Token(dialog)); // Adiciona na lista de tokens o token formado
            ref = 0; // Zera a referência
        } else { // Se o char atual não é um espaço
            ref++; // Incrementa a referência
        }
        dialogConteudo.remove(0,1); // Deleta sempre o char lido
    }
    // Exemplo para percorrer uma hash
    /*QHashIterator <QString, int> teste(identificadores);
    while(teste.hasNext()) {
        teste.next();
        std::cout << teste.key().toStdString()<< ": " << teste.value() << std::endl;
    }*/

    QString a;
    for (int i=0; i < tokens.size(); i++) {
        Token * dialog = tokens.at(i);
        a += dialog->getTipoToken() + " ";
        //if (dialog->getTipoDeToken() == "NAO")
        //    a += " Erro de sintaxe no token "+dialog->getToken() +" \n";
    }
    ui->textEditCodigoIntermediario->setText(a);
}

















