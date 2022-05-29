#include "CircleStatusWidget.h"

namespace jbox {
namespace graphics {

CircleStatusWidget::CircleStatusWidget(QWidget* parent) : QWidget(parent) {
  // Autorise le background à changer
  setAttribute(Qt::WA_StyledBackground, true);
  setObjectName("CircleStatusWidget");
}

void CircleStatusWidget::updateColor(QColor color) {
  setStyleSheet("#CircleStatusWidget {"
      "background-color: " + color.name() + ";" 
      "border-radius: 5px;}");
}

}  // namespace graphics
}  // namespace jbox

