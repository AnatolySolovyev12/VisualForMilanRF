#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VisualForMilanRF.h"

class VisualForMilanRF : public QMainWindow
{
    Q_OBJECT

public:
    VisualForMilanRF(QWidget *parent = nullptr);
    ~VisualForMilanRF();

private:
    Ui::VisualForMilanRFClass ui;
};
