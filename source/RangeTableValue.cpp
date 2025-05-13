#include "RangeTableValue.h"

RangeTableValue::RangeTableValue(QWidget* parent, QString numberAny)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->number = numberAny;

	QString filterStr = "number = '" + number + "'" + " ORDER BY date desc"; // фильтр начинается с "where" SQL синтаксиса без самого слова "where"

	//+ "' and date > '05 - 10 - 2024'"

	if (number.length() > 5)
		model.setTable("channelTable"); // задаём таблицу с которой работаем
	else
		model.setTable("counterTable"); // задаём таблицу с которой работаем

	model.setFilter(filterStr); // лучше применять фильтр до команды select
	model.select(); // заполняем модель значениями из таблицы
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // изменяя значения в отображ1

	//model.setHeaderData(0, Qt::Horizontal, "Name"); // даём название первому столбцу
   // model.setHeaderData(1, Qt::Horizontal, "Salary"); // даём название второму столбцу

	ui.tableView->setModel(&model);
}

RangeTableValue::~RangeTableValue()
{}
