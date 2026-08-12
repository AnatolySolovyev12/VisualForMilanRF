#pragma once

#include <QMainWindow>
#include "ui_warningTableClass.h"
#include <QtSql>

class warningTableClass : public QMainWindow
{
	Q_OBJECT

public:
	warningTableClass(QWidget *parent = nullptr);

	void clearTable();

private:
	Ui::warningTableClassClass ui;
	QSqlTableModel model;
	int countOfRows;
};

