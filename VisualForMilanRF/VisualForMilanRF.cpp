#include "VisualForMilanRF.h"

#include <QInputDialog>

VisualForMilanRF::VisualForMilanRF(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButtonAdd, &QPushButton::clicked, this, &VisualForMilanRF::addItemInList);
    connect(ui.pushButtonAddMinus, &QPushButton::clicked, this, &VisualForMilanRF::deleteItemInList);
   // connect(ui.pushButtonNamed, &QPushButton::clicked, this, &VisualForMilanRF::setData);

    connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(setNumber()));
    connect(ui.treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(closeEditor(QTreeWidgetItem*)));

    connect(ui.pushButtonNumber, &QPushButton::clicked, this, &VisualForMilanRF::setNumber);
    
}

VisualForMilanRF::~VisualForMilanRF()
{}


void VisualForMilanRF::addItemInList()
{

  
    
    //ui.treeWidget->expandItem(ui.treeWidget->currentItem()); // раскрытие элемента

    QTreeWidgetItem* any = nullptr;
    if(ui.treeWidget->currentItem() == nullptr)
        any = new QTreeWidgetItem(ui.treeWidget);
    else
        any = new QTreeWidgetItem(ui.treeWidget->currentItem());
  
    int column = ui.treeWidget->currentColumn();
    QString str;
    any->setText(0, "new");
   
}

void VisualForMilanRF::deleteItemInList()
{
    QTreeWidgetItem* taked = ui.treeWidget->currentItem();
    QTreeWidgetItem* parentTaked = taked->parent();

    if (parentTaked == nullptr)
        return;

    parentTaked->takeChild(parentTaked->indexOfChild(taked));
    
   // ui.treeWidget->collapseItem(ui.treeWidget->currentItem()); // закрытие элемента

    //  ui.treeWidget->clear(); // полная очистка виджета

    
}

void VisualForMilanRF::setData()
{
    QTreeWidgetItem* any = ui.treeWidget->currentItem();

    QInputDialog inputDialog;

    QString c_text = inputDialog.getText(this, "Add name", "Name of object", QLineEdit::Normal);
    QString c_textSimp = c_text.simplified(); // удаляем проблеы в начале и в конце и заменяем внутренние двойные пробелы на одинарные.

    any->setText(0, c_textSimp);

}

void VisualForMilanRF::setNumber()
{

    qDebug() << "TEST";
    
    QTreeWidgetItem* any = ui.treeWidget->currentItem();

    ui.treeWidget->openPersistentEditor(any, 0);
   // while (any->isSelected())
   // {
        ui.treeWidget->editItem(any, 0);
   // }
   // ui.treeWidget->closePersistentEditor(any, 0);

   


    /*
    QInputDialog inputDialog;

    int number = inputDialog.getInt(this, "Add number", "Serial number", QLineEdit::Normal);
    QString strNumber;

    any->setText(0, any->text(0));
    any->setText(1, strNumber.setNum(number));
    */
}


void VisualForMilanRF::closeEditor(QTreeWidgetItem* any)
{
    qDebug() << "EDITOR";
    ui.treeWidget->closePersistentEditor(any, 0);

}

