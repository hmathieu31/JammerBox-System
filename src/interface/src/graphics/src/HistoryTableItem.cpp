#include "HistoryTableItem.h"

namespace jbox {
namespace graphics {

HistoryTableItem::HistoryTableItem(std::time_t t,
                                   failures::Failure failure)
    : type("Failure"), name(failure.name) {
  std::tm* now = std::localtime(&t);
  std::stringstream ss;
  ss << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
  ss >> timestamp;
  data.setValue(failure);
}

HistoryTableItem::HistoryTableItem(std::time_t t,
                                   results::Result result)
    : type("Result"), name(result.message) {
  std::tm* now = std::localtime(&t);
  std::stringstream ss;
  ss << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;
  ss >> timestamp;
  data.setValue(result);
}

}  // namespace graphics
}  // namespace jbox
