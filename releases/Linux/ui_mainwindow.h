/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "sidebar.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd;
    QAction *actionRemove;
    QAction *actionImport;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    SideBar *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPredio;
    QComboBox *choosePredio;
    QLabel *labelSala;
    QComboBox *chooseSala;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *tableSalas;
    QTableWidget *tableNAlocados;
    QTableWidget *tableAlocar;
    QTableWidget *tablePedidos;
    QProgressBar *progressBar;
    QPushButton *initButton;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(667, 307);
        actionAdd = new QAction(MainWindow);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icon3"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd->setIcon(icon);
        actionRemove = new QAction(MainWindow);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icon4"), QSize(), QIcon::Normal, QIcon::Off);
        actionRemove->setIcon(icon1);
        actionImport = new QAction(MainWindow);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/icons/iconImport.jpeg"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport->setIcon(icon2);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new SideBar(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelPredio = new QLabel(centralWidget);
        labelPredio->setObjectName(QStringLiteral("labelPredio"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelPredio->sizePolicy().hasHeightForWidth());
        labelPredio->setSizePolicy(sizePolicy);
        labelPredio->setMinimumSize(QSize(50, 25));
        labelPredio->setWordWrap(false);

        horizontalLayout_2->addWidget(labelPredio, 0, Qt::AlignLeft);

        choosePredio = new QComboBox(centralWidget);
        choosePredio->setObjectName(QStringLiteral("choosePredio"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(choosePredio->sizePolicy().hasHeightForWidth());
        choosePredio->setSizePolicy(sizePolicy1);
        choosePredio->setMinimumSize(QSize(152, 25));
        choosePredio->setMaximumSize(QSize(10000, 25));

        horizontalLayout_2->addWidget(choosePredio);

        labelSala = new QLabel(centralWidget);
        labelSala->setObjectName(QStringLiteral("labelSala"));
        sizePolicy.setHeightForWidth(labelSala->sizePolicy().hasHeightForWidth());
        labelSala->setSizePolicy(sizePolicy);
        labelSala->setMinimumSize(QSize(50, 25));
        labelSala->setWordWrap(false);

        horizontalLayout_2->addWidget(labelSala);

        chooseSala = new QComboBox(centralWidget);
        chooseSala->setObjectName(QStringLiteral("chooseSala"));
        sizePolicy1.setHeightForWidth(chooseSala->sizePolicy().hasHeightForWidth());
        chooseSala->setSizePolicy(sizePolicy1);
        chooseSala->setMinimumSize(QSize(152, 0));
        chooseSala->setMaximumSize(QSize(10000, 25));

        horizontalLayout_2->addWidget(chooseSala);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        tableSalas = new QTableWidget(centralWidget);
        tableSalas->setObjectName(QStringLiteral("tableSalas"));

        horizontalLayout_4->addWidget(tableSalas);

        tableNAlocados = new QTableWidget(centralWidget);
        tableNAlocados->setObjectName(QStringLiteral("tableNAlocados"));

        horizontalLayout_4->addWidget(tableNAlocados);

        tableAlocar = new QTableWidget(centralWidget);
        tableAlocar->setObjectName(QStringLiteral("tableAlocar"));

        horizontalLayout_4->addWidget(tableAlocar);

        tablePedidos = new QTableWidget(centralWidget);
        tablePedidos->setObjectName(QStringLiteral("tablePedidos"));

        horizontalLayout_4->addWidget(tablePedidos);


        verticalLayout->addLayout(horizontalLayout_4);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        initButton = new QPushButton(centralWidget);
        initButton->setObjectName(QStringLiteral("initButton"));

        verticalLayout->addWidget(initButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionAdd);
        toolBar->addAction(actionRemove);
        toolBar->addAction(actionImport);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionAdd->setText(QApplication::translate("MainWindow", "Add", 0));
#ifndef QT_NO_TOOLTIP
        actionAdd->setToolTip(QApplication::translate("MainWindow", "Adds one element", 0));
#endif // QT_NO_TOOLTIP
        actionRemove->setText(QApplication::translate("MainWindow", "Remove", 0));
#ifndef QT_NO_TOOLTIP
        actionRemove->setToolTip(QApplication::translate("MainWindow", "Remove Selected", 0));
#endif // QT_NO_TOOLTIP
        actionImport->setText(QApplication::translate("MainWindow", "Import", 0));
#ifndef QT_NO_TOOLTIP
        actionImport->setToolTip(QApplication::translate("MainWindow", "Import from JSON", 0));
#endif // QT_NO_TOOLTIP
        labelPredio->setText(QApplication::translate("MainWindow", "Pr\303\251dio:", 0));
        labelSala->setText(QApplication::translate("MainWindow", "Sala:", 0));
        initButton->setText(QApplication::translate("MainWindow", "Iniciar", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
