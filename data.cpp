#include "data.h"
#include <QDebug>
#include <QFile>
#include "rapidjson/document.h"
#include "graph.h"
#include "rapidjson/filereadstream.h"

Data::Data()
{
}

void Data::readSalasFromJson(QString fileName)
{
    // Variaveis que serão utilizadas depois
    int capacidade = 0;
    // Abro o arquivo Json e coloco ele num documento pra ser utilizado depois
    FILE *fp = fopen(fileName.toLatin1(), "r");

    char readBuffer[1000010];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);

    // Declaro uma variavel para iterar pelo meu documento, comecando pelos grupos.
    const rapidjson::Value& g = d;
    for(rapidjson::Value::ConstMemberIterator grupo = g.MemberBegin();grupo != g.MemberEnd();++grupo){
        // Começo iterar pelos predios.
        const rapidjson::Value& predio = grupo->value;
        for(rapidjson::Value::ConstMemberIterator iter = predio.MemberBegin();iter != predio.MemberEnd();++iter){
            const rapidjson::Value& tipo = iter->value;
            // Como cada predio tem 3 tipos de sala, itero pelos tipos.
            for(rapidjson::Value::ConstMemberIterator tipos = tipo.MemberBegin();tipos != tipo.MemberEnd();++tipos){

                // Comeco iterar pelas salas dentro desse predio.
                const rapidjson::Value& sala = tipos->value;


                for(rapidjson::Value::ConstMemberIterator itr = sala.MemberBegin();itr != sala.MemberEnd();++itr){

                    // Pego a capacidade das salas, e a lista de salas com aquela capacidade.
                    capacidade = std::stoi(itr->name.GetString());
                    for(auto& array : itr->value.GetArray()){
                        // E coloco essa sala na minha lista de salas
                        salas.push_back(Sala(QString(array.GetString()), QString(iter->name.GetString()), QString(tipos->name.GetString()),capacidade, std::stoi(grupo->name.GetString())));
                    }
                }
            }
        }
    }
    fclose(fp);
    emit notifyImportSala();
}

void Data::readPedidosFromJson(QString fileName){
    // Abro o arquivo Json e coloco ele num documento pra ser utilizado depois
    int j = 0, i = 0;
    FILE *fp = fopen(fileName.toLatin1(), "r");
    char readBuffer[1000010];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);

    // Coloco ele numa variavel pra ser iterada.
    const rapidjson::Value& pedido = d;

    for(rapidjson::Value::ConstMemberIterator itr = pedido.MemberBegin();itr != pedido.MemberEnd();++itr){
        std::vector < int > dias;

        const rapidjson::Value& membro = itr->value;
        Pedido tmp;

        // Pego as variaveis necessarias do pedido.
        tmp.horario = QString(membro["horario"].GetString());
        tmp.info = QString(membro["info"].GetString());
        tmp.predio = QString(membro["predio"].GetString());
        tmp.tipo = QString(membro["tipo"].GetString());
        tmp.capacidade = std::stoi(membro["capacidade"].GetString());
        tmp.prioridade = membro["prioridade"].GetInt();
        tmp.curso = QString(membro["curso"].GetString());
        tmp.periodo = membro["periodo"].GetInt();
        tmp.pedidoOriginal = i++;

        pedidosTable.push_back(tmp);
    }
    emit notifyImportPedidos();
    fclose(fp);
}

int Data::sizeOfSalas(){
    return salas.size();
}

QStringList Data::salaInfo(int pos){
    Sala tmp = salas[pos];
    QStringList retorno;
    retorno << tmp.getName() << QString::number(tmp.getCapacidade()) << tmp.getTipo()
            << tmp.getPredio() << QString::number(tmp.getGrupo());
    return retorno;
}

int Data::sizeOfPedidos(){
    return pedidosTable.size();
}

QStringList Data::pedidosInfo(int pos)
{
    Pedido tmp = pedidosTable[pos];
    QStringList retorno;
    retorno << tmp.predio << QString::number(tmp.capacidade) << tmp.tipo << tmp.horario
            << tmp.curso << QString::number(tmp.periodo) << tmp.info << QString::number(tmp.pedidoOriginal);
    return retorno;
}

QStringList Data::salasDoPredio(QString predio)
{
    QStringList retorno;
    for(auto i : salas){
        if(!QString::compare(i.getPredio(), predio))
            retorno << i.getName();
    }
    return retorno;
}

Sala Data::getSala(QString predio, QString sala)
{
    for(auto i : salas){
        if(!QString::compare(predio, i.getPredio())
                && !QString::compare(sala, i.getName()))
            return i;
    }
    return Sala();
}

void Data::mountPedidos()
{
    for(int i = 0;i < pedidosTable.size();++i){

        const Pedido tmp = pedidosTable[i];

        const QString horario = tmp.horario;

        int j = 0, turno;

        QVector < int > dias, hrs;
        while(horario[j].isNumber()){
            dias.push_back(QString(horario[j++]).toInt()-1);
        }

        if(horario[j] == 'M') turno = 0;
        else if(horario[j] == 'T') turno = 1;
        else turno = 2;

        while(j < horario.size()){
            hrs.push_back(QString(horario[j++]).toInt()-1);
        }
        for(int k = 0;k < dias.size();++k){
            for(int l = 0;l < hrs.size();++l){
                pedidos[dias[k]][turno][hrs[l]].p.push_back(tmp);
            }
        }
    }
}

void Data::alocar()
{
    emit numberOfSteps(NDIAS * NTURNOS * NHORARIOS);
    mountPedidos();
    for(int i = 0;i < NDIAS;++i){
        for(int j = 0;j < NTURNOS;++j){
            for(int k = 0;k < NHORARIOS;++k){
                qDebug() << i << " " << j << " " << k;
                Graph aloc;
                QVector < Pedido > *pedTmp = &pedidos[i][j][k].p;
                aloc.criaArestas(*pedTmp, salas);
                aloc.min_cost_flow((*pedTmp).size() + salas.size() + 2, INT_MAX, 0, (*pedTmp).size() + salas.size() + 1);
                aloc.iterarArestas(*pedTmp, salas,i,j,k, nao_alocados);

                emit incrProgress();
                pedidos[i][j][k].p.clear();
            }
        }
    }
    emit paintNaoAlocados(nao_alocados);
}


