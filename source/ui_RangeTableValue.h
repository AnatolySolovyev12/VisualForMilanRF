/********************************************************************************
** Form generated from reading UI file 'RangeTableValue.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANGETABLEVALUE_H
#define UI_RANGETABLEVALUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RangeTableValueClass
{
public:
    QWidget *centralWidget;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RangeTableValueClass)
    {
        if (RangeTableValueClass->objectName().isEmpty())
            RangeTableValueClass->setObjectName(QString::fromUtf8("RangeTableValueClass"));
        RangeTableValueClass->resize(734, 560);
        RangeTableValueClass->setMinimumSize(QSize(500, 500));
        centralWidget = new QWidget(RangeTableValueClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(20, 30, 681, 451));
        RangeTableValueClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RangeTableValueClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 734, 21));
        RangeTableValueClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RangeTableValueClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RangeTableValueClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RangeTableValueClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RangeTableValueClass->setStatusBar(statusBar);

        retranslateUi(RangeTableValueClass);

        QMetaObject::connectSlotsByName(RangeTableValueClass);
    } // setupUi

    void retranslateUi(QMainWindow *RangeTableValueClass)
    {
        RangeTableValueClass->setWindowTitle(QCoreApplication::translate("RangeTableValueClass", "RangeTableValue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RangeTableValueClass: public Ui_RangeTableValueClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANGETABLEVALUE_H
