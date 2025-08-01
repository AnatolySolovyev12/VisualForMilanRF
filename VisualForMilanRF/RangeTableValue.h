﻿#pragma once

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

    void dataChangedCheck();

private slots:
    void applyFunc();


private:
	Ui::RangeTableValueClass ui;

    QTableView view;
    QSqlTableModel model;
    QString number;
};
