#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualForMilanRF.h"

#include <QInputDialog>
#include <QFileDialog>

#include <QFile>

#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>

#include <QtSql/QtSql>

class VisualForMilanRF : public QMainWindow
{
    Q_OBJECT

public:
    VisualForMilanRF(QWidget *parent = nullptr);
    ~VisualForMilanRF();

    void addItemInList();
    void deleteItemInList();
    void adressFinder();
    void exportXml();
    void recursionXmlWriter(QTreeWidgetItem* some, QXmlStreamWriter& someXmlWriter);
    void importXml();
    void loopXmlReader(QTreeWidgetItem* some, QXmlStreamReader& xmlReader);


    void test();

    bool connectDB();


private slots:
    void setData();
    void closeEditor(QTreeWidgetItem* any);
    void otherItemWasChecked(QTreeWidgetItem* any);


private:
    Ui::VisualForMilanRFClass ui;

    QTreeWidgetItem* middleItem = nullptr;
    int middleColumn;
    bool offChanger = false;


    QSqlDatabase mw_db; // экземпляр подключения к БД
};
