#include "RangeTableValue.h"

RangeTableValue::RangeTableValue(QWidget *parent, QString numberAny)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    this->number = numberAny;

    QString filterStr = "number = '" + number + "'" + " ORDER BY date DESC"; // ������ ���������� � "where" SQL ���������� ��� ������ ����� "where"

    //+ "' and date > '05 - 10 - 2024'"

    model.setTable("channelTable"); // ����� ������� � ������� ��������
    model.setFilter(filterStr); // ����� ��������� ������ �� ������� select
    model.select(); // ��������� ������ ���������� �� �������
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // ������� �������� � �������1

    //model.setHeaderData(0, Qt::Horizontal, "Name"); // ��� �������� ������� �������
   // model.setHeaderData(1, Qt::Horizontal, "Salary"); // ��� �������� ������� �������

    ui.tableView->setModel(&model);
}

RangeTableValue::~RangeTableValue()
{}
