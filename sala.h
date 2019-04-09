#ifndef SALA_H
#define SALA_H

#include <QString>
#include <QMap>
#define NTURNOS 3
#define NDIAS 7
#define NHORARIOS 6

struct Pedido{
    int capacidade, periodo, prioridade, pedidoOriginal;
    QString tipo, predio, curso, info, horario;
};

class Sala
{
public:
    Sala(QString _name, QString _predio, QString _tipo, int _capacidade, int _grupo);
    Sala();
    QString getName();
    QString getPredio();
    QString getTipo();
    int getCapacidade();
    int getGrupo();
    bool mesmoHorario(int i, int j, int k, int capacidade, QString info, QString curso,
                      QString predio, int periodo);
    const static int getPredioGrupo(QString predio);
    void setHorario(int dia, int turno, int horario, Pedido p);
    static QStringList getPrediosList();
    QString getPedidoInfo(int i, int j, int k);
private:
    QString name;
    QString predio;
    QString tipo;
    int capacidade;
    int grupo;
    Pedido horario[NDIAS][NTURNOS][NHORARIOS];
    static QMap < QString , int > g;

};

#endif // SALA_H
