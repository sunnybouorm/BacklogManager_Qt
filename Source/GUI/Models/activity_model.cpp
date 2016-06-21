#include "activity_model.h"

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

QVariant ActivityModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) {
		return QVariant();
	}

	if (index.row() >= string_list_.size()) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {
		return string_list_.at(index.row());
	}

	else {
		return QVariant();
	}
}

//bool ActivityModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) {
//	bool result;
//
//	return result;
//}