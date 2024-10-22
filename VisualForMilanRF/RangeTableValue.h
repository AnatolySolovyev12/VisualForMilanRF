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
        qDebug() << "Что-то не так с соединением!";
        return -1;
    }

    QTableView view;
    QSqlTableModel model;
    
    QString filterStr = "number = '400097410' and date > '05 - 10 - 2024'"; // фильтр начинается с "where" SQL синтаксиса без самого слова "where"
    model.setTable("channelTable"); // задаём таблицу с которой работаем
    model.setFilter(filterStr); // лучше применять фильтр до команды select
    model.select(); // заполняем модель значениями из таблицы
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // изменяя значения в отображ1

    //model.setHeaderData(0, Qt::Horizontal, "Name"); // даём название первому столбцу
   // model.setHeaderData(1, Qt::Horizontal, "Salary"); // даём название второму столбцу

    view.setModel(&model);
    view.show();

    return a.exec();
}

*/
