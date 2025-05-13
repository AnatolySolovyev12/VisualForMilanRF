/********************************************************************************
** Form generated from reading UI file 'VisualForMilanRF.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALFORMILANRF_H
#define UI_VISUALFORMILANRF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VisualForMilanRFClass
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidget;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonAddMinus;
    QPushButton *pushButtonFinder;
    QPushButton *pushButtonImport;
    QPushButton *pushButtonExport;
    QPushButton *pushButtonTest;
    QPushButton *pushButtonBrowse;
    QPushButton *pushButtonReport;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QFrame *line_5;
    QPushButton *pushButtonRange;
    QPushButton *pushButtonSort;
    QFrame *line_6;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VisualForMilanRFClass)
    {
        if (VisualForMilanRFClass->objectName().isEmpty())
            VisualForMilanRFClass->setObjectName(QString::fromUtf8("VisualForMilanRFClass"));
        VisualForMilanRFClass->resize(1158, 493);
        centralWidget = new QWidget(VisualForMilanRFClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        treeWidget = new QTreeWidget(centralWidget);
        QBrush brush(QColor(213, 213, 213, 255));
        brush.setStyle(Qt::NoBrush);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem->setBackground(0, brush);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(40, 10, 1101, 421));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setLayoutDirection(Qt::LeftToRight);
        treeWidget->setAutoFillBackground(false);
        treeWidget->setSortingEnabled(false);
        pushButtonAdd = new QPushButton(centralWidget);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        pushButtonAdd->setGeometry(QRect(10, 10, 20, 20));
        pushButtonAddMinus = new QPushButton(centralWidget);
        pushButtonAddMinus->setObjectName(QString::fromUtf8("pushButtonAddMinus"));
        pushButtonAddMinus->setGeometry(QRect(10, 40, 20, 20));
        pushButtonFinder = new QPushButton(centralWidget);
        pushButtonFinder->setObjectName(QString::fromUtf8("pushButtonFinder"));
        pushButtonFinder->setGeometry(QRect(10, 80, 20, 20));
        pushButtonImport = new QPushButton(centralWidget);
        pushButtonImport->setObjectName(QString::fromUtf8("pushButtonImport"));
        pushButtonImport->setGeometry(QRect(10, 120, 20, 20));
        pushButtonExport = new QPushButton(centralWidget);
        pushButtonExport->setObjectName(QString::fromUtf8("pushButtonExport"));
        pushButtonExport->setGeometry(QRect(10, 150, 20, 20));
        pushButtonTest = new QPushButton(centralWidget);
        pushButtonTest->setObjectName(QString::fromUtf8("pushButtonTest"));
        pushButtonTest->setGeometry(QRect(10, 220, 20, 20));
        pushButtonBrowse = new QPushButton(centralWidget);
        pushButtonBrowse->setObjectName(QString::fromUtf8("pushButtonBrowse"));
        pushButtonBrowse->setGeometry(QRect(10, 190, 20, 20));
        pushButtonReport = new QPushButton(centralWidget);
        pushButtonReport->setObjectName(QString::fromUtf8("pushButtonReport"));
        pushButtonReport->setGeometry(QRect(10, 270, 20, 20));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 100, 41, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 60, 41, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(0, 170, 41, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(0, 250, 41, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(0, 290, 41, 16));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        pushButtonRange = new QPushButton(centralWidget);
        pushButtonRange->setObjectName(QString::fromUtf8("pushButtonRange"));
        pushButtonRange->setGeometry(QRect(10, 310, 20, 20));
        pushButtonSort = new QPushButton(centralWidget);
        pushButtonSort->setObjectName(QString::fromUtf8("pushButtonSort"));
        pushButtonSort->setGeometry(QRect(10, 350, 20, 20));
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(0, 330, 41, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        VisualForMilanRFClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VisualForMilanRFClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1158, 22));
        VisualForMilanRFClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VisualForMilanRFClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        VisualForMilanRFClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VisualForMilanRFClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        VisualForMilanRFClass->setStatusBar(statusBar);

        retranslateUi(VisualForMilanRFClass);

        QMetaObject::connectSlotsByName(VisualForMilanRFClass);
    } // setupUi

    void retranslateUi(QMainWindow *VisualForMilanRFClass)
    {
        VisualForMilanRFClass->setWindowTitle(QCoreApplication::translate("VisualForMilanRFClass", "VisualForMilanRF", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(9, QCoreApplication::translate("VisualForMilanRFClass", "StartingValueHot", nullptr));
        ___qtreewidgetitem->setText(8, QCoreApplication::translate("VisualForMilanRFClass", "StartingValueCold", nullptr));
        ___qtreewidgetitem->setText(7, QCoreApplication::translate("VisualForMilanRFClass", "Channel 4", nullptr));
        ___qtreewidgetitem->setText(6, QCoreApplication::translate("VisualForMilanRFClass", "Channel 3", nullptr));
        ___qtreewidgetitem->setText(5, QCoreApplication::translate("VisualForMilanRFClass", "Channel 2", nullptr));
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("VisualForMilanRFClass", "Channel 1", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("VisualForMilanRFClass", "Date", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("VisualForMilanRFClass", "Number", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("VisualForMilanRFClass", "ID", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("VisualForMilanRFClass", "Adress", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("VisualForMilanRFClass", "General", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

#if QT_CONFIG(tooltip)
        treeWidget->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButtonAdd->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "Adds a child to the selected", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAdd->setText(QCoreApplication::translate("VisualForMilanRFClass", "+", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonAddMinus->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "Deletes the selected object", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonAddMinus->setText(QCoreApplication::translate("VisualForMilanRFClass", "-", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonFinder->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "Searches for a value in the selected column and displays its location in the tree", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonFinder->setText(QCoreApplication::translate("VisualForMilanRFClass", "Fd", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonImport->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "Imports an object tree into XML", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonImport->setText(QCoreApplication::translate("VisualForMilanRFClass", "Im", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonExport->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "Exports an object tree from XML", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonExport->setText(QCoreApplication::translate("VisualForMilanRFClass", "Ex", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonTest->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "Update values for objects in the tree", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonTest->setText(QCoreApplication::translate("VisualForMilanRFClass", "Rf", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonBrowse->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "Specify the SQLite database", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonBrowse->setText(QCoreApplication::translate("VisualForMilanRFClass", "Br", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonReport->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "<html><head/><body><p>We unload the XLS report with the current values of the object tree</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonReport->setText(QCoreApplication::translate("VisualForMilanRFClass", "Rp", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonRange->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "<html><head/><body><p>Display the device value in tabular form</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonRange->setText(QCoreApplication::translate("VisualForMilanRFClass", "Ra", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSort->setToolTip(QCoreApplication::translate("VisualForMilanRFClass", "<html><head/><body><p>Display the device value in tabular form</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSort->setText(QCoreApplication::translate("VisualForMilanRFClass", "Sr", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VisualForMilanRFClass: public Ui_VisualForMilanRFClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALFORMILANRF_H
