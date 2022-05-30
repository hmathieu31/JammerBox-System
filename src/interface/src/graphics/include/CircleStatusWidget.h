#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_CIRCLE_STATUS_WIDGET_H_INCLUDED_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_CIRCLE_STATUS_WIDGET_H_INCLUDED_

#include <QBoxLayout>
#include <QColor>
#include <QWidget>

namespace jbox {
namespace graphics {

class CircleStatusWidget : public QWidget {
  Q_OBJECT

 public:
  CircleStatusWidget(QWidget* parent = 0);

  /**
   * @brief change the color of the circle 
   *
   * @param color the new color
   */
  void updateColor(QColor color);

  QSize minimumSizeHint() const {
    return QSize(10, 10);
  }
};

}  // namespace graphics
}  // namespace jbox

#endif
