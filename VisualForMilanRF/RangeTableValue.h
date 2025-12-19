#pragma once

#include <QMainWindow>
#include "ui_RangeTableValue.h"
#include <QtSql>
#include <QTableView>
#include <QFileDialog>
#include <QAxObject>
#include < QTreeWidgetItem>

class RangeTableValue : public QMainWindow
{
	Q_OBJECT

public:
    RangeTableValue(QWidget* parent = nullptr, QString numberAny = "");
	~RangeTableValue();

    void dataChangedCheck();

private slots:
    void applyFunc();
    void getXlsReport();


private:
	Ui::RangeTableValueClass ui;

    QTableView view;
    QSqlTableModel model;
    QString number;
};
