#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualForMilanRF.h"

#include <QInputDialog>
#include <QFileDialog>

#include <QFile>

#include <QXmlStreamWriter>
#include <QXmlStreamAttribute>

class VisualForMilanRF : public QMainWindow
{
    Q_OBJECT

public:
    VisualForMilanRF(QWidget *parent = nullptr);
    ~VisualForMilanRF();

    void addItemInList();
    void deleteItemInList();
    void adressFinder();

    void test1();

    void test2();

    void recursionXmlWriter(QTreeWidgetItem* some);

private slots:
    void setData();
    void closeEditor(QTreeWidgetItem* any);
    void otherItemWasChecked(QTreeWidgetItem* any);


private:
    Ui::VisualForMilanRFClass ui;

    QTreeWidgetItem* middleItem = nullptr;
    int middleColumn;
    bool offChanger = false;
};
