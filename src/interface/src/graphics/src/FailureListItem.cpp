#include "FailureListItem.h"

namespace jbox {
namespace graphics {

FailureListItem::FailureListItem(const QVector<QVariant> &data,
                                 const failures::Failure *failure,
                                 FailureListItem *parent)
    : m_failure(failure), m_itemData(data), m_parentItem(parent) {
    }

FailureListItem::~FailureListItem() {
  qDeleteAll(m_childItems);
}

FailureListItem *FailureListItem::appendChild(FailureListItem *item) {
  m_childItems.append(item);
  return item;
}

FailureListItem *FailureListItem::child(int row) {
  if (row < 0 || row >= m_childItems.size()) {
    return nullptr;
  }
  return m_childItems.at(row);
}

int FailureListItem::childCount() const {
  return m_childItems.count();
}

int FailureListItem::row() const {
  if (m_parentItem) {
    return m_parentItem->m_childItems.indexOf(
        const_cast<FailureListItem *>(this));
  }
  return 0;
}

int FailureListItem::columnCount() const {
  return m_itemData.count();
}

QVariant FailureListItem::data(int column) const {
  if (column < 0 || column >= m_itemData.size()) {
    return QVariant();
  }
  return m_itemData.at(column);
}

FailureListItem *FailureListItem::parentItem() {
  return m_parentItem;
}

}  // namespace graphics
}  // namespace jbox
