#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_HISTORY_TABLE_ITEM_INCLUDED_H_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_HISTORY_TABLE_ITEM_INCLUDED_H_

#include "failures.h"
#include "results.h"

#include <QVariant>
#include <string>
#include <sstream>

namespace jbox {
namespace graphics {

struct HistoryTableItem {
  std::string timestamp;
  std::string type;
  std::string name;
  QVariant data;

  // Default constructor
  HistoryTableItem() : timestamp(""), type(""), name(""),data(QVariant()) {}
  // Copy constructor
  HistoryTableItem(const HistoryTableItem & item) : timestamp(item.timestamp), type(item.type), name(item.name),data(item.data) {}

  HistoryTableItem(std::time_t t, failures::Failure failure);
  HistoryTableItem(std::time_t t, results::Result result);

  // Default destructor
  ~HistoryTableItem() = default;
};

} // namespace graphics
} // namespace jbox

// Permet d'utiliser le struct dans un QVariant
Q_DECLARE_METATYPE(jbox::graphics::HistoryTableItem);
Q_DECLARE_METATYPE(jbox::failures::Failure);
Q_DECLARE_METATYPE(jbox::results::Result);

#endif
