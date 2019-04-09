#ifndef DATA_H
#define DATA_H

#include <QVector>
#include "sala.h"
#include <QObject>
#include <QSet>


class Data : public QObject
{
    Q_OBJECT
public:
    Data();
    void readSalasFromJson(QString fileName);
    void readPedidosFromJson(QString fileName);
    int sizeOfSalas();
    int sizeOfPedidos();
    QStringList salaInfo(int pos);
    QStringList pedidosInfo(int pos);
    void alocar();
    void mountPedidos();
    Pedido info(int i, int j, int k);
    QStringList salasDoPredio(QString predio);
    Sala getSala(QString predio, QString sala);

signals:
    void notifyImportSala();
    void notifyImportPedidos();
    void numberOfSteps(int number);
    void incrProgress();
    void paintNaoAlocados(QSet < int > nao_alocados);

private:
    QVector < Sala > salas;
    QVector < Pedido > pedidosTable;
    struct Vector4D{
        QVector < Pedido > p;
    };

    Vector4D pedidos[NDIAS][NTURNOS][NHORARIOS];
    QSet < int > nao_alocados;
};

#endif // DATA_H
