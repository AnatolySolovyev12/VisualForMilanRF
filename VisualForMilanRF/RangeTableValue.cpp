#include "RangeTableValue.h"

RangeTableValue::RangeTableValue(QWidget *parent, QString numberAny)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    this->number = numberAny;

    QString filterStr = "number = '" + number + "'" + " ORDER BY date DESC"; // фильтр начинаетс€ с "where" SQL синтаксиса без самого слова "where"

    //+ "' and date > '05 - 10 - 2024'"

    model.setTable("channelTable"); // задаЄм таблицу с которой работаем
    model.setFilter(filterStr); // лучше примен€ть фильтр до команды select
    model.select(); // заполн€ем модель значени€ми из таблицы
    model.setEditStrategy(QSqlTableModel::OnManualSubmit);// OnManualSubmit // OnFieldChange // OnRowChange // измен€€ значени€ в отображ1

    //model.setHeaderData(0, Qt::Horizontal, "Name"); // даЄм название первому столбцу
   // model.setHeaderData(1, Qt::Horizontal, "Salary"); // даЄм название второму столбцу

    ui.tableView->setModel(&model);
}

RangeTableValue::~RangeTableValue()
{}
