#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTextStream>
#include <QDebug>
#include <QPushButton>
#include <QAction>
#include <QFileDialog>
#include <QProgressBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->addAction(QString("Salas"), QIcon(QString(":/icons/icon0")));
    ui->widget->addAction(QString("Pedidos"), QIcon(QString(":/icons/icon1")));
    ui->widget->addAction(QString("Não Alocados"), QIcon(QString(":/icons/icon5")));
    ui->widget->addAction(QString("Visão Geral"), QIcon(QString(":/icons/icon2")));


    QStringList header;
    header << "Predio" << "Capacidade" << "Tipo" << "Horario" << "Curso" << "Periodo" << "Info" << "id";
    ui->tablePedidos->setColumnCount(header.size());
    ui->tablePedidos->setHorizontalHeaderLabels(header);
    ui->tablePedidos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tablePedidos->hideColumn(header.size()-1);

    ui->tableNAlocados->setColumnCount(header.size());
    ui->tableNAlocados->setHorizontalHeaderLabels(header);
    ui->tableNAlocados->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableNAlocados->hideColumn(header.size()-1);



    header = QStringList();
    header << "Nome" << "Capacidade" << "Tipo" << "Predio" << "Grupo";
    ui->tableSalas->setColumnCount(header.size());
    ui->tableSalas->setHorizontalHeaderLabels(header);
    ui->tableSalas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    header = QStringList();
    header << "Domingo" << "Segunda" << "Terca" << "Quarta" << "Quinta" << "Sexta" << "Sabado";
    ui->tableAlocar->setColumnCount(header.size());
    ui->tableAlocar->setHorizontalHeaderLabels(header);
    ui->tableAlocar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    header = QStringList();
    header << "07:10-08:00" << "08:00-08:50" << "08:50-09:40" << "10:00-10:50" << "10:50-11:40" << "11:40-12:30" <<
              "13:10-14:00" << "14:00-14:50" << "14:50-15:40" << "16:00-16:50" << "16:50-17:40" << "17:40-18:30" <<
              "18:50-19:35" << "19:35-20:20" << "20:30-21:15" << "21:15-22:00";
    ui->tableAlocar->setRowCount(header.size());
    ui->tableAlocar->setVerticalHeaderLabels(header);
    ui->tableAlocar->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    header = QStringList();

    connect(ui->widget, SIGNAL(notifyChangeTable(QString)), this, SLOT(changeTable(QString)));
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(importFromJson()));
    data = new Data;

    connect(data, SIGNAL(notifyImportSala()), this, SLOT(changeTableSalas()));
    connect(data, SIGNAL(notifyImportPedidos()), this, SLOT(changeTablePedidos()));
    connect(ui->initButton, SIGNAL(clicked()), this, SLOT(startProgram()));
    connect(data, SIGNAL(paintNaoAlocados(QSet < int >)), this, SLOT(paintNaoAlocados(QSet < int >)));
    connect(ui->choosePredio, SIGNAL(currentIndexChanged(int)), this, SLOT(setSalas(int)));
    connect(ui->chooseSala, SIGNAL(currentIndexChanged(int)), this, SLOT(preencherVisaoGeral(int)));

    ui->initButton->setEnabled(false);

    ui->widget->startUpAction();
}

void MainWindow::startProgram()
{
    connect(data, SIGNAL(incrProgress()), this, SLOT(incrProgress()));
    connect(data, SIGNAL(numberOfSteps(int)), this, SLOT(numberOfSteps(int)));
    ui->initButton->setEnabled(false);
    data->alocar();
    ui->initButton->setEnabled(true);
    ui->progressBar->reset();
}

void MainWindow::preencherVisaoGeral(int pos)
{
    ui->tableAlocar->clear();
    if(!QString::compare(ui->chooseSala->itemText(pos), QStringLiteral("-"))) return;
    Sala choosed = data->getSala(ui->choosePredio->currentText(), ui->chooseSala->itemText(pos));

    qDebug() << choosed.getName() << " -- " << ui->choosePredio->currentText() << " - " <<
                ui->chooseSala->itemText(pos);

    for(int i = 0;i < 6;++i)
        for(int j = 0;j < 3;++j)
            for(int k = 0;k < 7;++k){
                ui->tableAlocar->setItem(j*6+i, k, new QTableWidgetItem(choosed.getPedidoInfo(k, j, i)));
//                qDebug() << choosed.getPedidoInfo(i, j, k);
            }
}

void MainWindow::numberOfSteps(int number)
{
    ui->progressBar->setRange(0, number);
}

void MainWindow::incrProgress()
{
    ui->progressBar->valueChanged(ui->progressBar->value()+1);
}

void MainWindow::changeTable(QString tableSelected)
{
    ui->tableSalas->hide();
    ui->tablePedidos->hide();
    ui->tableAlocar->hide();
    ui->labelSala->hide();
    ui->labelPredio->hide();
    ui->chooseSala->hide();
    ui->choosePredio->hide();
    ui->tableNAlocados->hide();
    ui->toolBar->show();
    if(tableSelected == QStringLiteral("Salas"))
        ui->tableSalas->show();
    else if(tableSelected == QStringLiteral("Pedidos"))
        ui->tablePedidos->show();
    else if(tableSelected == QStringLiteral("Não Alocados")){
        ui->tableNAlocados->show();
    }
    else{
        ui->toolBar->hide();
        ui->tableAlocar->show();
        ui->labelSala->show();
        ui->labelPredio->show();
        ui->chooseSala->show();
        ui->choosePredio->show();
    }
}

void MainWindow::importFromJson()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir JSON", "/home/", tr("JSON (*.json)"));
    if(fileName.isEmpty()) return;
    if(ui->tableSalas->isHidden()) data->readPedidosFromJson(fileName);
    else data->readSalasFromJson(fileName);
}

void MainWindow::changeTableSalas()
{
    int n = data->sizeOfSalas(), m = ui->tableSalas->columnCount();
    QStringList salaItem;
    for(int i = 0;i < n;++i){
        ui->tableSalas->insertRow(i);
        salaItem = data->salaInfo(i);
        for(int j = 0;j < m;++j)
            ui->tableSalas->setItem(i, j, new QTableWidgetItem(salaItem[j]));
     }
    ui->tableSalas->sortByColumn(0, Qt::AscendingOrder);
    ui->tableSalas->sortByColumn(4, Qt::AscendingOrder);
    if(n && data->sizeOfPedidos()) ui->initButton->setEnabled(true);
    setPredios();
}

void MainWindow::setPredios()
{
    ui->tableAlocar->clear();
    ui->choosePredio->clear();
    QStringList prediosList = Sala::getPrediosList();
    ui->choosePredio->addItem(QStringLiteral("-"));

    for(auto i : prediosList)
        ui->choosePredio->addItem(i);

}

void MainWindow::setSalas(int pos)
{
    ui->chooseSala->clear();
    ui->chooseSala->addItem(QStringLiteral("-"));
    if(ui->choosePredio->itemText(pos) == "-") return;

    QStringList salasDoPredio = data->salasDoPredio(ui->choosePredio->itemText(pos));
    salasDoPredio.sort();
    for(auto i : salasDoPredio)
        ui->chooseSala->addItem(i);

}

void MainWindow::changeTablePedidos()
{
    int n = data->sizeOfPedidos(), m = ui->tablePedidos->columnCount();
    QStringList pedidoItem;
    for(int i = 0;i < n;++i){
        ui->tablePedidos->insertRow(i);
        pedidoItem = data->pedidosInfo(i);
        for(int j = 0;j < m;++j){
            ui->tablePedidos->setItem(i, j, new QTableWidgetItem(pedidoItem[j]));
        }
    }
    ui->tablePedidos->sortByColumn(0, Qt::AscendingOrder);
    if(n && data->sizeOfSalas()) ui->initButton->setEnabled(true);
}

void MainWindow::paintNaoAlocados(QSet < int > nao_alocados)
{
    int n = data->sizeOfPedidos(), m = ui->tablePedidos->columnCount()-1;
    for(int i = n-1;i >= 0;--i){
        QString tmp = ui->tablePedidos->item(i, ui->tablePedidos->columnCount()-1)->text();
        if(nao_alocados.find(tmp.toInt()) != nao_alocados.end()){
            ui->tableNAlocados->insertRow(ui->tableNAlocados->rowCount());
            for(int j = 0;j < m;++j){
                ui->tableNAlocados->setItem(ui->tableNAlocados->rowCount()-1, j, ui->tablePedidos->takeItem(i,j));
            }
            ui->tablePedidos->removeRow(i);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete data;
}
