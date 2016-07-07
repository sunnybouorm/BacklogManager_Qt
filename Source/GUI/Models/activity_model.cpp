#include "activity_model.h"

#include <QFont>
#include <QBrush>

#include <iostream>//TODO delete me

ActivityModel::ActivityModel(Core* core_, QObject *parent) : QAbstractTableModel(parent){
	this->core_ = core_;
	this->tag_row_ = 0;

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

int ActivityModel::columnCount(const QModelIndex &parent) const {
	return 1;
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
		if (index.row() == tag_row_ && index.column() == 0) { return Qt::AlignCenter; }
		break;

	case Qt::FontRole:
		if (index.row() == tag_row_ && index.column() == 0) {
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

QVariant ActivityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal) {
			switch (section)
			{
			case 0:
				return QString("Activities");
			}
		}
		return QVariant();
	}
	else { return QVariant(); }

}

bool ActivityModel::insertRows(int position, int count, const QModelIndex &parent)
{
	beginInsertRows(QModelIndex(), position, position + count - 1);

	for (int row = 0; row < count; ++row) {
		this->string_list_.insert(position, "");
	}

	endInsertRows();
	return true;
}

bool ActivityModel::removeRows(int position, int count, const QModelIndex &index)
{
	beginRemoveRows(QModelIndex(), position, position + count - 1);

	for (int row = 0; row < count; ++row) {
		this->string_list_.removeAt(position);
	}

	endRemoveRows();

	return true;
}

Qt::ItemFlags ActivityModel::flags(const QModelIndex &index) const 
{
	if (index.isValid() == false) {
		return Qt::ItemIsEnabled;
	}

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ActivityModel::setData(const QModelIndex &index, const QVariant &value, int role) 
{
	return setDataSql(index, value, role, UPDATE); 
}

bool ActivityModel::setDataSql(const QModelIndex &index, const QVariant &value, int role,
	Request sql_request) 
{

	bool request_successful = false;

	QueryContainer query;
	RowContainer row;

	query.table_name = "Activity";
	query.request = sql_request;

	row["Name"] = string_list_.at(index.row()).toStdString();
	query.search_params = row;
	row.clear();

	row["Name"] = value.toString().toStdString();
	query.columns = row;
	row.clear();

	request_successful = core_->SqlRequest(query);

	if (request_successful == true) {
		this->string_list_.replace(index.row(), value.toString());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}