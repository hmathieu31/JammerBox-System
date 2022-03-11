#include "FailureListModel.h"

namespace jbox {
namespace graphics {

FailureListModel::FailureListModel(
    const std::vector<failures::Failure> failures, QObject *parent)
    : QAbstractItemModel(parent) {
  m_rootItem = new FailureListItem({tr("Failures")});

  std::map<failures::FailureTypeEnum, FailureListItem*> types;
  std::vector<failures::Failure>::const_iterator it = failures::failures.cbegin();
  while(it != failures::failures.cend()) {
    FailureListItem * parent;
    try {
      parent = types.at(it->type.type);
    } catch(const std::out_of_range & e) {
      parent = m_rootItem->appendChild(new FailureListItem({QString::fromStdString(it->type.name)}, nullptr, m_rootItem));
      types[it->type.type] = parent;
    }
    parent->appendChild(new FailureListItem({QString::fromStdString(it->name)}, &*it, parent));

    it += 1;
  }
}

FailureListModel::~FailureListModel() {
  delete m_rootItem;
}

QModelIndex FailureListModel::index(int row, int column,
                                    const QModelIndex &parent) const {
  if (!hasIndex(row, column, parent)) {
    return QModelIndex();
  }

  FailureListItem *parentItem;

  if (!parent.isValid()) {
    parentItem = m_rootItem;
  } else {
    parentItem = static_cast<FailureListItem *>(parent.internalPointer());
  }

  FailureListItem *childItem = parentItem->child(row);
  if (childItem) {
    return createIndex(row, column, childItem);
  }
  return QModelIndex();
}

QModelIndex FailureListModel::parent(const QModelIndex &index) const {
  if (!index.isValid()) {
    return QModelIndex();
  }

  FailureListItem *childItem =
      static_cast<FailureListItem *>(index.internalPointer());
  FailureListItem *parentItem = childItem->parentItem();

  if (parentItem == m_rootItem)
    return QModelIndex();

  return createIndex(parentItem->row(), 0, parentItem);
}

int FailureListModel::rowCount(const QModelIndex &parent) const {
  FailureListItem *parentItem;
  if (parent.column() > 0) {
    return 0;
  }

  if (!parent.isValid()) {
    parentItem = m_rootItem;
  } else {
    parentItem = static_cast<FailureListItem *>(parent.internalPointer());
  }

  return parentItem->childCount();
}

int FailureListModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return static_cast<FailureListItem *>(parent.internalPointer())
        ->columnCount();
  }
  return m_rootItem->columnCount();
}

QVariant FailureListModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return QVariant();
  }

  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  FailureListItem *item =
      static_cast<FailureListItem *>(index.internalPointer());

  return item->data(index.column());
}

Qt::ItemFlags FailureListModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) {
    return Qt::NoItemFlags;
  }

  Qt::ItemFlags flag = QAbstractItemModel::flags(index);
  // Si c'est une catégorie, on le disable
  // Ou si la liste est disabled
  if(index.parent().row() == -1) {
    flag &= Qt::ItemIsEnabled;
  }
  if(m_disabled) {
    flag &= Qt::ItemIsSelectable;
  }
  
  return flag;
}

QVariant FailureListModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    return m_rootItem->data(section);
  }

  return QVariant();
}

FailureListItem * FailureListModel::rootItem() {
  return m_rootItem;
}

void FailureListModel::setDisabled(bool disabled) {
  m_disabled = disabled;
}

}  // namespace graphics
}  // namespace jbox
