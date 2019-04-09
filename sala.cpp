#include "sala.h"

QMap < QString , int > Sala::g;

Sala::Sala(QString _name, QString _predio, QString _tipo, int _capacidade, int _grupo)
    : name(_name), predio(_predio), tipo(_tipo), capacidade(_capacidade), grupo(_grupo)
{
    for(int i = 0;i < NDIAS;++i)
        for(int j = 0;j < NTURNOS;++j)
            for(int k = 0;k < NHORARIOS;++k)
                horario[i][j][k].capacidade = -1;
    g[_predio] = _grupo;
}

Sala::Sala()
{
}

void Sala::setHorario(int dia, int turno, int _horario, Pedido p){
    horario[dia][turno][_horario] = p;
}

const int Sala::getPredioGrupo(QString predio){
    return g[predio];
}

QString Sala::getName(){
    return name;
}

QString Sala::getTipo(){
    return tipo;
}

QString Sala::getPredio(){
    return predio;
}

int Sala::getCapacidade(){
    return capacidade;
}

int Sala::getGrupo(){
    return grupo;
}

bool Sala::mesmoHorario(int i, int j, int k, int capacidade, QString info, QString curso,
                  QString predio, int periodo)
{
    Pedido tmp = horario[i][j][k];
    if(tmp.capacidade == capacidade && tmp.periodo == periodo && !QString::compare(tmp.info, info, Qt::CaseInsensitive) &&
            !QString::compare(tmp.curso, curso, Qt::CaseInsensitive) && !QString::compare(tmp.predio, predio, Qt::CaseInsensitive))
        return true;
    return false;
}

QString Sala::getPedidoInfo(int i, int j, int k)
{
    Pedido tmp = horario[i][j][k];
    if(tmp.capacidade == -1) return QStringLiteral("");
    QString retorno = tmp.info + " - " + tmp.curso + ", "
            + QString::number(tmp.periodo) + "º periodo";
    return retorno;
}

QStringList Sala::getPrediosList()
{
    QStringList retorno;
    for(auto i = g.begin();i != g.end();++i){
        retorno << i.key();
    }
    return retorno;
}


