#include "RangeTableValue.h"

RangeTableValue::RangeTableValue(QWidget* parent, QString numberAny)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(close()));

	connect(ui.applyButton, SIGNAL(clicked()), this, SLOT(applyFunc()));

	this->number = numberAny;

	QString filterStr = "number = '" + number + "'" + " ORDER BY date desc, channelFirst desc"; // фильтр начинается с "where" SQL синтаксиса без самого слова "where"

	if (number.length() > 5)
		model.setTable("channelTable"); // задаём таблицу с которой работаем
	else
		model.setTable("counterTable"); // задаём таблицу с которой работаем

	model.setFilter(filterStr); // лучше применять фильтр до команды select
	model.select(); // заполняем модель значениями из таблицы
	model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // изменяя значения в отображении

	ui.tableView->setModel(&model);
}

RangeTableValue::~RangeTableValue()
{}

void RangeTableValue::applyFunc()
{
	if (!model.submitAll())
		qDebug() << model.lastError();
}