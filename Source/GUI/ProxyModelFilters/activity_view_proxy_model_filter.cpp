#include "activity_view_proxy_model_filter.h"

#include <QAbstractItemModel>

#include <iostream>

ActivityViewSortFilterProxyModel::ActivityViewSortFilterProxyModel(QTableView *view, 
	ActivityModel *activity_model, QObject *parent)
{
	this->activity_model_ = activity_model;
	this->setSourceModel(activity_model);
	view->setModel(this);
}

bool ActivityViewSortFilterProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {

	if (index.isValid() && role == Qt::EditRole) 
	{
		if (value.toString() == "") {}
		else if ((index.row() == activity_model_->tag_row_) && (value.toString().toStdString() == "<Add new Activity>"))
		{
			activity_model_->insertRows(activity_model_->tag_row_, 1);

			activity_model_->string_list_.replace(index.row(), value.toString());
			activity_model_->data(index, Qt::FontRole);
			activity_model_->data(index, Qt::ForegroundRole);
			activity_model_->data(index, Qt::TextAlignmentRole);

			emit dataChanged(index, index);

			return true;
		} else if (index.row() == activity_model_->tag_row_) 
		{
			bool is_successful = false;
			QModelIndex tag_index = QAbstractItemModel::createIndex(0, 0);
			int index_row = removeAddActivityItem(tag_index);
			activity_model_->insertRows(index_row, 1);

			is_successful &= this->activity_model_->setDataSql(index, value, Qt::EditRole, INSERT);

			//QModelIndex tag_index = QAbstractItemModel::createIndex(index_row, 0);
			is_successful &= setData(tag_index, "<Add new Activity>", Qt::EditRole);

			return is_successful;
		} /*else
		{
			bool is_successful = false;
			is_successful = activity_model_->removeRows(activity_model_->tag_row_, 1);
			is_successful &= this->activity_model_->setDataSql(index, value, Qt::EditRole, UPDATE);
			is_successful &= setData(index, "<Add new Activity>", Qt::EditRole);

			return is_successful;
		}*/
	}

	return false;
}

/*
 * Removes <Add new Activity> item and returns the index at which it was removed
 */
int ActivityViewSortFilterProxyModel::removeAddActivityItem(QModelIndex &index) {
	int first_row, last_row, index_row;

	if (activity_model_->string_list_.count() != 0) {

		first_row = 0;
		last_row  = this->activity_model_->string_list_.count() - 1;

		//remove <Add New Activity> tag
		if (activity_model_->string_list_.at(first_row) == "<Add new Activity>")
		{
			activity_model_->removeRows(first_row, 1, index);
			last_row -= 1;
			index_row = 0;	
		}
		else
		{
			std::cerr << "ActivityViewProxyModel Warning: <Add new Activity> item is missing\n";
		}

		this->activity_model_->tag_row_ = index_row;
	}

	return index_row;
}

void ActivityViewSortFilterProxyModel::sort(int column, Qt::SortOrder order) {

	if (activity_model_->string_list_.count() != 0) {
		int index_row = 0;

		//sort List
		QSortFilterProxyModel::sort(column, order);

		//Insert <Add new Activity> tag at the top of the list
		QModelIndex tag_index = QAbstractItemModel::createIndex(index_row, 0);
		index_row = removeAddActivityItem(tag_index);
		QModelIndex index = QAbstractItemModel::createIndex(index_row, 0);
		this->setData(index, "<Add new Activity>", Qt::EditRole);
	}
}