#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualForMilanRF.h"

class VisualForMilanRF : public QMainWindow
{
    Q_OBJECT

public:
    VisualForMilanRF(QWidget *parent = nullptr);
    ~VisualForMilanRF();

    void addItemInList();
    void deleteItemInList();




private slots:
    void setData();
    void setNumber();
    void closeEditor(QTreeWidgetItem* any);


private:
    Ui::VisualForMilanRFClass ui;
};
