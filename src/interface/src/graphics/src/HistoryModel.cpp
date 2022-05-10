#include "HistoryModel.h"

namespace jbox {
namespace graphics {

HistoryModel::HistoryModel(QObject *parent) : QAbstractTableModel(parent) {}

int HistoryModel::rowCount(const QModelIndex & /*parent*/) const {
  return row_count;
}

int HistoryModel::columnCount(const QModelIndex & /*parent*/) const {
  return column_count;
}

QVariant HistoryModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  if (role == Qt::DisplayRole) {
    try {
      return header.at(section);
    } catch (std::out_of_range) {
    }
  }

  return QVariant();
}

QVariant HistoryModel::data(const QModelIndex &index, int role) const {
  switch (role) {
    case Qt::DisplayRole: {
      try {
        HistoryTableItem item = list.at(index.row()).value<HistoryTableItem>();
        switch (index.column()) {
          case 0:
            return QString::fromStdString(item.timestamp);
            break;
          case 1:
            return QString::fromStdString(item.type);
            break;
          case 2:
            return QString::fromStdString(item.name);
            break;
        }
      } catch (const std::out_of_range &e) {
      }
      return QVariant();
    }
    case Qt::FontRole: {
      QFont font;
      font.setFamily("Courier New");
      font.setStyleHint(QFont::TypeWriter);
      return font;
    }
    case Qt::BackgroundRole: {
                     HistoryTableItem item = list.at(index.row()).value<HistoryTableItem>();
      if(item.type == "Failure") {
        QBrush background(QColor(230, 230, 230)); 
        return background;
      }
      return QVariant();
      break;
    }
    default:
      return QVariant();
  }
}

bool HistoryModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role) {
  // We don't use the vertical header
  if (orientation == Qt::Vertical) {
    return true;
  }

  if (role == Qt::EditRole) {
    header.insert(std::pair(section, value));

    // Recompute the column count
    column_count = header.rbegin()->first + 1;

    // Emit a signal saying the headers between section and section changed in
    // the orientation header
    emit headerDataChanged(orientation, section, section);
  }

  return true;
}

bool HistoryModel::setData(const QModelIndex &index, const QVariant &value,
                           int role) {
  // The index doesn't matter as we add new data to the bottom of the list
  if (role == Qt::EditRole) {
    list[row_count] = value;

    // Recompute the row count
    row_count = list.rbegin()->first + 1;

    // Emit a signal saying the content changed
    emit dataChanged(index, index);
  }

  return true;
}

std::map<int, QVariant> HistoryModel::getList(){
  return list;
}

}  // namespace graphics
}  // namespace jbox

