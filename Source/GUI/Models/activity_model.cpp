#include "activity_model.h"

#include <QFont>
#include <QBrush>

#include <iostream>//TODO delete me

ActivityModel::ActivityModel(Core* core_, QObject *parent) : QAbstractListModel(parent){
	this->core_ = core_;

	//TODO delete me
	//---------------------------------------------
	QueryContainer query;
	std::string  column_name, column_data;
	RowContainer row;

	std::string table_name = "Activity";
	std::string activity_name = "Movies";

	column_name = "Name";
	column_data = activity_name;

	row[column_name] = column_data;

	query.table_name	= table_name;
	query.columns		= row;
	query.request		= INSERT;

	core_->SqlRequest(query);
	row.clear();

	table_name = "Activity";
	activity_name = "Video Games";

	column_name = "Name";
	column_data = activity_name;

	row[column_name] = column_data;

	query.table_name = table_name;
	query.columns = row;
	query.request = INSERT;

	core_->SqlRequest(query);
	row.clear();

	//---------------------------------------------
	this->string_list_ << "<Add new Activity>";

	std::string sql = "SELECT Name FROM Activity;";
	core_->database_.SqlCommand(sql);

	auto result = core_->database_.read_result_buffer();

	core_->database_.PrintResultBuffer();//TODO delete me

	for (auto row = result.begin(); row != result.end(); ++row) {
		this->string_list_ << QString::fromUtf8(row->at("Name").c_str());
	}
}

int ActivityModel::rowCount(const QModelIndex &parent) const {
	return string_list_.count();
}

/*
 * Configures display properties of the List view attached to this model
 */
QVariant ActivityModel::data(const QModelIndex &index, int role) const {
	switch (role) {

	case Qt::DisplayRole:
		if (!index.isValid()) {
			return QVariant();
		}

		if (index.row() >= string_list_.size()) {
			return QVariant();
		}

		return string_list_.at(index.row());
		break;

	case Qt::TextAlignmentRole:
		if (index.row() == 0) { return Qt::AlignCenter; }
		break;

	case Qt::FontRole:
		if (index.row() == 0) {
			QFont font;
			font.setItalic(true);
			return font;
		}
		break;

	case Qt::ForegroundRole:
		QBrush text;
		if (index.row() == 0) {
			text.setColor(Qt::gray);
			return text;
		}
		break;
	}
	return QVariant();
}

bool ActivityModel::setData(const QModelIndex &index, const QVariant &value,
	int role) 
{
	bool result;



	return result;
}