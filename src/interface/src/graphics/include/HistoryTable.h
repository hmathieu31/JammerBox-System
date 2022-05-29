#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_HISTORYTABLE_INCLUDED_H_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_HISTORYTABLE_INCLUDED_H_

#include <QTableView>

#include "HistoryModel.h"

namespace jbox {
namespace graphics {

class HistoryTable : public QTableView {
  Q_OBJECT

 public:
  HistoryTable(QWidget* parent = nullptr);
  ~HistoryTable();

  /**
   * Ajoute une failure à la table
   *
   * @param timestamp le timestamp de l'event
   * @param failure la donnée
   */
  void add_data(std::time_t timestamp, failures::Failure failure);
  /**
   * Ajoute un result à la table
   *
   * @param timestamp le timestamp de l'event
   * @param failure la donnée
   */
  void add_data(std::time_t timestamp, results::Result result);

 signals:
  void onSelect(std::string timestamp, const failures::Failure * selected);
  void onSelect(std::string timestamp, const results::Result * selected);

 private:
  HistoryModel* model;
  void selectionChanged(const QItemSelection& selected,
                        const QItemSelection& deselected);
};

}  // namespace graphics
}  // namespace jbox

#endif
