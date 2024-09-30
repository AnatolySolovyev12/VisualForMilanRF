#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualForMilanRF.h"

#include <QInputDialog>
#include <QFileDialog>

#include <QFile>

#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>

#include <QtSql/QtSql>

#include <QAxObject>

#include <QTableWidgetItem>

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
    void refresh();
    bool connectDB();
    void recursionDbSqlReader(QTreeWidgetItem* some);
    void browse();
    void recursionXlsWriter(QTreeWidgetItem* some);
    void report();

    void startingImportXml();

private slots:
    void setData();
    void closeEditor(QTreeWidgetItem* any);
    void otherItemWasChecked(QTreeWidgetItem* any);


private:
    Ui::VisualForMilanRFClass ui;

    QTreeWidgetItem* middleItem = nullptr;
    int middleColumn;
    bool offChanger = false;
    QString line;
    QSqlDatabase mw_db; // экземпляр подключения к БД


    QAxObject* excelDonor = nullptr;
    QAxObject* workbooksDonor = nullptr;
    QAxObject* workbookDonor = nullptr;
    QAxObject* sheetsDonor = nullptr;
    QAxObject* sheetDonor = nullptr;
    QAxObject* cell = nullptr;
    QAxObject* paste = nullptr;
    QTableWidgetItem* item = nullptr;
    int countRow = 1;
};
