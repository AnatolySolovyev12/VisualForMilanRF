#pragma once

#include <QMainWindow>
#include "ui_RangeTableValue.h"

#include <QtSql>
#include <QTableView>

class RangeTableValue : public QMainWindow
{
	Q_OBJECT

public:
    RangeTableValue(QWidget* parent = nullptr, QString numberAny = "");
	~RangeTableValue();

private:
	Ui::RangeTableValueClass ui;

    QTableView view;
    QSqlTableModel model;
    QString number;
};


/*
* #include "TestProject.h"
#include <QtWidgets/QApplication>
#include <QtSql>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("DataBaseMilanRF");
    if (!dbase.open()) {
        qDebug() << "���-�� �� ��� � �����������!";
        return -1;
    }

    QTableView view;
    QSqlTableModel model;
    
    QString filterStr = "number = '400097410' and date > '05 - 10 - 2024'"; // ������ ���������� � "where" SQL ���������� ��� ������ ����� "where"
    model.setTable("channelTable"); // ����� ������� � ������� ��������
    model.setFilter(filterStr); // ����� ��������� ������ �� ������� select
    model.select(); // ��������� ������ ���������� �� �������
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // ������� �������� � �������1

    //model.setHeaderData(0, Qt::Horizontal, "Name"); // ��� �������� ������� �������
   // model.setHeaderData(1, Qt::Horizontal, "Salary"); // ��� �������� ������� �������

    view.setModel(&model);
    view.show();

    return a.exec();
}

*/
