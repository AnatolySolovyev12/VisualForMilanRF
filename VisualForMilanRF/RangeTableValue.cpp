#include "RangeTableValue.h"

RangeTableValue::RangeTableValue(QWidget* parent, QString numberAny)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->number = numberAny;

	QString filterStr = "number = '" + number + "'" + " ORDER BY date desc"; // ������ ���������� � "where" SQL ���������� ��� ������ ����� "where"

	//+ "' and date > '05 - 10 - 2024'"

	if (number.length() > 5)
		model.setTable("channelTable"); // ����� ������� � ������� ��������
	else
		model.setTable("counterTable"); // ����� ������� � ������� ��������

	model.setFilter(filterStr); // ����� ��������� ������ �� ������� select
	model.select(); // ��������� ������ ���������� �� �������
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // ������� �������� � �������1

	//model.setHeaderData(0, Qt::Horizontal, "Name"); // ��� �������� ������� �������
   // model.setHeaderData(1, Qt::Horizontal, "Salary"); // ��� �������� ������� �������

	ui.tableView->setModel(&model);
}

RangeTableValue::~RangeTableValue()
{}
