#include "activity_model.h"

ActivityModel::ActivityModel(QObject *parent) : QAbstractListModel(parent){
	this->stringList_ << "item1";
}

int ActivityModel::rowCount(const QModelIndex &parent) const {
	return stringList_.count();
}

QVariant ActivityModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) {
		return QVariant();
	}

	if (index.row() >= stringList_.size()) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {
		return stringList_.at(index.row());
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