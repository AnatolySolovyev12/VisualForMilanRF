#include "VisualForMilanRF.h"

#include <QInputDialog>

VisualForMilanRF::VisualForMilanRF(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButtonAdd, &QPushButton::clicked, this, &VisualForMilanRF::addItemInList);
    connect(ui.pushButtonAddMinus, &QPushButton::clicked, this, &VisualForMilanRF::deleteItemInList);

   // connect(ui.pushButtonNamed, &QPushButton::clicked, this, &VisualForMilanRF::setData);
   // connect(ui.pushButtonNumber, &QPushButton::clicked, this, &VisualForMilanRF::setNumber);

    connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(setData()));
    connect(ui.treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(closeEditor(QTreeWidgetItem*)));
    connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(otherItemWasChecked(QTreeWidgetItem*)));

    middleColumn = 0;
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

/*
void VisualForMilanRF::setNumber()
{
    QTreeWidgetItem* any = ui.treeWidget->currentItem();

    QInputDialog inputDialog;

    QString c_text = inputDialog.getText(this, "Add name", "Name of object", QLineEdit::Normal);
    QString c_textSimp = c_text.simplified(); // удаляем проблеы в начале и в конце и заменяем внутренние двойные пробелы на одинарные.

    any->setText(0, c_textSimp);
}

*/

void VisualForMilanRF::setData()
{
    qDebug() << "OPEN EDITOR";
    
    QTreeWidgetItem* any = ui.treeWidget->currentItem();
    int column = ui.treeWidget->currentColumn();

    middleColumn = column;
    middleItem = any;

    ui.treeWidget->openPersistentEditor(any, column);
    ui.treeWidget->editItem(any, column);



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
    int column = ui.treeWidget->currentColumn();
    ui.treeWidget->closePersistentEditor(middleItem, middleColumn);

    qDebug() << "CLOSE EDITOR";
}

void VisualForMilanRF::otherItemWasChecked(QTreeWidgetItem* any)
{
    int column = ui.treeWidget->currentColumn();
    qDebug() << "Checked " << any->text(column);

    if (any == middleItem && column == middleColumn)
        return;

    ui.treeWidget->closePersistentEditor(middleItem, middleColumn);
    middleItem = nullptr;

    qDebug() << "CLOSE EDITOR";
}