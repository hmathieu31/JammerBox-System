#ifndef SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_MAINWINDOW_INCLUDED_H_
#define SRC_INTERFACE_SRC_GRAPHICS_INCLUDE_MAINWINDOW_INCLUDED_H_

#include <QDockWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QSignalMapper>
#include <QTabWidget>
#include <QVBoxLayout>
#include <iostream>
#include <QDebug>
#include <QSerialPortInfo>
#include <QList>

#include "EventDetailWidget.h"
#include "FailureBannerWidget.h"
#include "FailureConfigureWidget.h"
#include "FailureListWidget.h"
#include "HistoryTable.h"
#include "StatusBarWidget.h"

namespace jbox {
namespace middleware {
class Middleware;
}
}  // namespace jbox

namespace jbox {
namespace graphics {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow();

  /****** Events du middleware ******/
  void onReceiveResult(jbox::results::Result result);

  jbox::middleware::Middleware* middleware;

 private slots:
  void on_com_click(QString comPort);
  void on_flash_config_click();
  void on_reset_config_click();
  /**
   * @brief this function is called when the user
   * clicked to show the tools menu, it updates the list
   * of existing ports
   */
  void on_tools_click();

 private:
  HistoryTable* historyTable;

  void createMenus();
  QMenu* fileMenu;
  QAction* exitAction;
  QMenu* toolsMenu;
  QAction* addConfigAction;
  QAction* resetConfigAction;
  QSignalMapper* signalMapper;

  void createDockWindows();
  FailureBannerWidget* failureBannerWidget;
  EventDetailWidget* eventDetailWidget;
  FailureListWidget* failureListWidget;
  FailureConfigureWidget* failureConfigureWidget;
  StatusBarWidget* statusBarWidget;

  void createStatusBar();

  void connectEvents();
  void onFailureSelect(const failures::Failure* selected);
  void onFailureStart();
  void onFailureStop();

  void onHistorySelect(std::string timestamp,
                       const failures::Failure* selected);
  void onHistorySelect(std::string timestamp, const results::Result* selected);

  void onComStateChanged(StatusBarWidget::State state);

  const std::string title = "Title";
};

}  // namespace graphics
}  // namespace jbox

#include "middleware.h"

#endif
