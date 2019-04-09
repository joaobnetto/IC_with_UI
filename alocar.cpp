#include "alocar.h"
#include <QProgressDialog>
#include <fstream>
std::string dia[6] = {"Segunda", "Terca", "Quarta", "Quinta", "Sexta", "Sabado"};
std::string hr[3][6] = {{"07:00-08:00", "08:00-08:50","08:50-09:40","10:00-10:50","10:50-11:40","11:40-12:30"},
{"13:10-14:00","14:00-14:50","14:50-15:40","16:00-16:50","16:50-17:40","17:40-18:30"},
{"18:50-19:35","19:35-20:20","20:30-21:15","21:15-22:00","-","-"}};

// Leio os pedidos e os armazeno.

QStringList Alocar::lerPedidos(QString fileName){
    // Abro o arquivo Json e coloco ele num documento pra ser utilizado depois
    int j = 0, i = 0;
    FILE *fp = fopen(fileName.toLatin1(), "r");
    char readBuffer[1000010];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);

    QStringList pedidosRetorno;

    // Coloco ele numa variavel pra ser iterada.
    const rapidjson::Value& pedido = d;

    for(rapidjson::Value::ConstMemberIterator itr = pedido.MemberBegin();itr != pedido.MemberEnd();++itr){
        std::vector < int > dias;
        int turno;
        const rapidjson::Value& membro = itr->value;
        Pedido tmp;
        i = j = 0;

        // Pego as variaveis necessarias do pedido.
        std::string horario = membro["horario"].GetString();
        tmp.info = membro["info"].GetString();
        tmp.predio = membro["predio"].GetString();
        tmp.tipo = membro["tipo"].GetString();
        tmp.capacidade = std::stoi(membro["capacidade"].GetString());
        tmp.prioridade = membro["prioridade"].GetInt();
        tmp.curso = membro["curso"].GetString();
        tmp.periodo = membro["periodo"].GetInt();

        pedidosRetorno << QStringLiteral("%1;%2;%3;%4;%5;%6").arg( QString::fromStdString(tmp.predio) ).
                          arg( QString::number(tmp.capacidade) ).arg( QString::fromStdString(horario) ).
                          arg( QString::fromStdString(tmp.curso) ).arg( QString::number(tmp.periodo) ).
                          arg( QString::fromStdString(tmp.info) );

        // Pego os dias que tem a aula, quando comeca, termina e o turno
        j = 0;

        while(horario[j] <= '9' && horario[j] >= '0'){
            dias.push_back(horario[j++] - '0' - 2);
        }
        if(horario[j] == 'M') turno = 0;
        else if(horario[j] == 'T') turno = 1;
        else turno = 2;

        j++;

        for(;j < horario.size();++j){
            for(auto k : dias){
                pedidos[k][turno][horario[j]-'0'-1].p.push_back(tmp);
            }
        }
    }

    // sort(pedidos.begin(),pedidos.end());
    fclose(fp);
    return pedidosRetorno;
}

// Leio as salas e as armazeno num vetor só.

QStringList Alocar::lerSalas(QString fileName){
    // Variaveis que serão utilizadas depois
    int i = 0, capacidade = 0;

    QStringList retorno;

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
                        salas.push_back(Sala(capacidade, iter->name.GetString(), array.GetString(), tipos->name.GetString(), std::stoi(grupo->name.GetString())));
                        retorno << QStringLiteral("%1;%2;%3;%4;%5").arg(QString::fromStdString(array.GetString())).
                                   arg(QString::number(capacidade)).arg(QString::fromStdString(tipos->name.GetString()))
                                   .arg(QString::fromStdString(iter->name.GetString())).
                                   arg(QString::number(std::stoi(grupo->name.GetString())));
                        // std::cout << capacidade << " " << iter->name.GetString () << " " << array.GetString() << " " << tipos->name.GetString() << "\n";
                    }
                }
            }
        }
    }
    sort(salas.begin(), salas.end());
    fclose(fp);
    return retorno;
}

// Imprimo minhas salas após a alocação.

void Alocar::imprimirSalas(){

    for(auto z : salas){
        Sala tmp = z;
        std::cout << "Sala: " << z.getNome() << " Predio: " << z.getPredio() << " Capacidade: " << z.getCapacidade()
            << " Tipo: "  << z.getTipo() <<",";
        std::cout << "Segunda,Terça,Quarta,Quinta,Sexta,Sabado\n";
        for(int j = 0;j < 3;++j){
            for(int k = 0;k < 6;++k){
                if(j == 2 && k >= 4) continue;
                std::cout << hr[j][k] << ",";
                for(int i = 0;i < 6;++i){
                    z.imprimeHorario(i, j, k);
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}

// Imprimo os pedidos que li

void Alocar::imprimirPedidos(){

    std::ofstream out("out.csv");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    for(int i = 0;i < 6;++i){
        std::cout << dia[i] << ":\n";
        for(int j = 0;j < 3;++j){
            for(int k = 0;k < 6;++k){
                std::vector < Pedido > tmp = pedidos[i][j][k].p;
                std::cout << tmp.size() << std::endl;
                std::map < int , int > m;
                for(int l = 0;l < tmp.size();++l){
                    m[tmp[l].capacidade]++;
                }
                for(auto i = m.begin();i != m.end();++i){
                    std::cout << i->first << ": " << i->second << std::endl;
                }
                return;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
    std::cout.rdbuf(coutbuf); //reset to standard output again
}

// Imprimo o que não foi alocado.

void Alocar::imprimirNaoAlocados(){
    std::cout << "Nao Alocados: " << nao_alocados.size() << "\n";
    for(auto i : nao_alocados){
        std::cout << i.info << " " << i.curso << " " << i.tipo << " " << i.predio << " " << i.capacidade << std::endl;
    }
}

// Aloco os pedidos, usando o min-cost max-flow, para cada horário crio um grafo e faço isso.
void Alocar::alocar(QProgressBar &progress){

    Group novo;
    int counter = 0;

    for(int i = 0;i < 6;++i){
        for(int j = 0;j < 3;++j){
            for(int k = 0;k < 6;++k){

                progress.setValue(counter++);

                Graph aloc;

                std::vector < Pedido > tmp = pedidos[i][j][k].p;
                aloc.criaArestas(tmp, salas);
                aloc.min_cost_flow(tmp.size() + salas.size() + 2, INT_MAX, 0, tmp.size() + salas.size() + 1);
                aloc.iterarArestas(tmp, salas,i,j,k, nao_alocados);

            }
        }
    }

    progress.setValue(counter);
}
