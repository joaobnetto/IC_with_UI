#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#import "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changeTable(QString tableSelected);
    void importFromJson();
    void changeTableSalas();
    void changeTablePedidos();
    void startProgram();
    void incrProgress();
    void numberOfSteps(int number);
    void paintNaoAlocados(QSet < int > nao_alocados);
    void setSalas(int pos);
    void preencherVisaoGeral(int pos);

private:
    Ui::MainWindow *ui;
    void setPredios();
    Data *data;
};

#endif // MAINWINDOW_H
