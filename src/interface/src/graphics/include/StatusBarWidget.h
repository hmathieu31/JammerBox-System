#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_STATUS_BAR_WIDGET_H_INCLUDED_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_STATUS_BAR_WIDGET_H_INCLUDED_

#include <QBrush>
#include <QColor>
#include <QHBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include <QWidget>

#include "CircleStatusWidget.h"

namespace jbox {
namespace graphics {

class StatusBarWidget : public QStatusBar {
  Q_OBJECT

 public:
  StatusBarWidget(QWidget* parent = 0);

  enum State { DISCONNECTED, CONNECTED };

  /**
   * @brief change d'état parmis les states
   *
   * @param state le nouvel état
   */
  void switchState(State state);

signals:
  void onSwitchState(State state);

 private:
  QLabel* label;
  CircleStatusWidget* circleWidget;
};

}  // namespace graphics
}  // namespace jbox

#endif
