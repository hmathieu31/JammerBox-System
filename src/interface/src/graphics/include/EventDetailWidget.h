#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_EVENT_DETAIL_WIDGET_H_INCLUDED_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_EVENT_DETAIL_WIDGET_H_INCLUDED_

#include <QDockWidget>
#include <QFont>
#include <QLabel>
#include <string>

#include "failures.h"
#include "results.h"

namespace jbox {
namespace graphics {

class EventDetailWidget : public QDockWidget {
  Q_OBJECT

 public:
  EventDetailWidget(QWidget* parent = 0) : QDockWidget(tr("Détails"), parent) {
    setFeatures(QDockWidget::NoDockWidgetFeatures);

    label = new QLabel(this);
    label->setStyleSheet(
        "QLabel { padding: 10px 10px 30px 10px; background-color : white;}");
    label->setAlignment(Qt::AlignTop);
    setWidget(label);
  }

 public slots:
  /**
   * @brief Affiche les détails d'une failure
   *
   * @param timestamp le timestamp du test
   * @param failure la donnée
   */
  void show_failure_detail(std::string timestamp, const failures::Failure* failure);

  /**
   * @brief Affiche les détails d'un result
   *
   * @param timestamp le timestamp du result
   * @param result la donnée
   */
  void show_result_detail(std::string timestamp, const results::Result* result);

 private:
  QLabel* label;
};

}  // namespace graphics
}  // namespace jbox

#endif
