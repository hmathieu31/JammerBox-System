#include "MainWindow.h"

namespace jbox {
namespace graphics {

MainWindow::MainWindow() {
  historyTable = new HistoryTable();
  failureBannerWidget = new FailureBannerWidget();

  // Set the window size to be 70% of the available screen space
  resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

  QWidget *centralWidget = new QWidget();
  QVBoxLayout *centralWidgetLayout = new QVBoxLayout();
  centralWidgetLayout->setMargin(0);
  centralWidgetLayout->setSpacing(0);
  centralWidgetLayout->addWidget(failureBannerWidget);
  historyTable->setFrameShape(HistoryTable::NoFrame);
  centralWidgetLayout->addWidget(historyTable);
  centralWidget->setLayout(centralWidgetLayout);
  setCentralWidget(centralWidget);

  createMenus();
  createDockWindows();
  createStatusBar();

  connectEvents();

  setWindowTitle(QString::fromStdString(title));
}

void MainWindow::createMenus() {
  // File
  fileMenu = menuBar()->addMenu(tr("&Fichier"));
  QAction *exitAction = new QAction(tr("Quitter"));
  fileMenu->addAction(exitAction);
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

  // Tools
  toolsMenu = menuBar()->addMenu(tr("&Outils"));
  signalMapper = new QSignalMapper(toolsMenu);

  connect(toolsMenu, &QMenu::aboutToShow, this, &MainWindow::on_tools_click);
  connect(signalMapper, qOverload<const QString &>(&QSignalMapper::mapped), this, &MainWindow::on_com_click);
}

void MainWindow::on_tools_click() {
  toolsMenu->clear();
  QAction *separatorText = new QAction(tr("Sélectionnez un port"));
  separatorText->setEnabled(false);
  toolsMenu->addAction(separatorText);
  toolsMenu->addSeparator();
  // Récuperation des com ports
  QList<QSerialPortInfo> ports_list = QSerialPortInfo::availablePorts();

  QList<QSerialPortInfo>::iterator it = ports_list.begin();

  while(it != ports_list.end()){
    QSerialPortInfo port = *it ;
    QString comName ;
    const QString comPort = port.portName();
    comName.append(comPort + " ");
    comName.append(port.description());
    QAction *action = new QAction(comName);
    toolsMenu->addAction(action);
    connect(action, SIGNAL(triggered()), signalMapper, SLOT(map()));
    signalMapper->setMapping(action,comPort);
    it++;
  }
  toolsMenu->addSeparator();
  addConfigAction = new QAction(tr("Flasher une configuration..."));
  toolsMenu->addAction(addConfigAction);
  connect(addConfigAction, &QAction::triggered, this, &MainWindow::on_flash_config_click);
  resetConfigAction = new QAction(tr("Réinitialiser la configuration"));
  toolsMenu->addAction(resetConfigAction);
  connect(resetConfigAction, &QAction::triggered, this, &MainWindow::on_reset_config_click);
}

void MainWindow::on_com_click(QString comPort) {
  // A connecter avec le middleware
  qDebug() << comPort ;
  middleware->connect(comPort.toStdString());
  statusBarWidget->switchState(StatusBarWidget::State::CONNECTED);
  std::cout << "connected" << std::endl ;
}

void MainWindow::on_flash_config_click(){
  // A connecter avec le middleware
  std::cout << "flash config" << std::endl;
}

void MainWindow::on_reset_config_click(){
  // A connecter avec le middleware
  std::cout << "reset config" << std::endl;
}

void MainWindow::createDockWindows() {
  // Left should be above bottom
  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

  failureListWidget = new FailureListWidget();
  addDockWidget(Qt::LeftDockWidgetArea, failureListWidget);

  eventDetailWidget = new EventDetailWidget();
  addDockWidget(Qt::BottomDockWidgetArea, eventDetailWidget);

  failureConfigureWidget = new FailureConfigureWidget();
  addDockWidget(Qt::LeftDockWidgetArea, failureConfigureWidget);
  failureConfigureWidget->setVisible(false);
}

void MainWindow::createStatusBar() {
  statusBarWidget = new StatusBarWidget();
  setStatusBar(statusBarWidget);
}

void MainWindow::connectEvents() {
  // On connecte le failure select
  connect(failureListWidget, &FailureListWidget::onSelect, this,
          &MainWindow::onFailureSelect);

  // On connecte le failure start
  connect(failureBannerWidget, &FailureBannerWidget::onStart, this,
          &MainWindow::onFailureStart);

  // On connecte le failure stop
  connect(failureBannerWidget, &FailureBannerWidget::onStop, this,
          &MainWindow::onFailureStop);

  connect(historyTable,
          qOverload<std::string, const failures::Failure *>(
              &HistoryTable::onSelect),
          this,
          qOverload<std::string, const failures::Failure *>(
              &MainWindow::onHistorySelect));

  connect(
      historyTable,
      qOverload<std::string, const results::Result *>(&HistoryTable::onSelect),
      this,
      qOverload<std::string, const results::Result *>(
          &MainWindow::onHistorySelect));

  connect(statusBarWidget,
      &StatusBarWidget::onSwitchState,
      this,
      &MainWindow::onComStateChanged);
}

void MainWindow::onFailureSelect(const failures::Failure *failure) {
  failureBannerWidget->setSelectedFailure(failure);

  if(failure == nullptr) {
    failureConfigureWidget->setVisible(false);
  } else {
    failureConfigureWidget->setVisible(true);
    failureConfigureWidget->setFailure(failure);
  }
}

void MainWindow::onFailureStart() {
  failureListWidget->setDisabled(true);
  const failures::Failure * selected = failureBannerWidget->getSelected();
  const failures::Failure instance = selected->create_instance(failureConfigureWidget->getParams());
  if (instance.type.type == failures::CAM) {
    //Choix de la CAM à utiliser avant l'envoi de la failure
    int cam_number = failureConfigureWidget->getCamChoice() ;
    middleware->set_cam(cam_number);
  }
  historyTable->add_data(std::time(0), instance);
  middleware->send(true, instance);
}

void MainWindow::onFailureStop() {
  failureListWidget->setDisabled(false);
  historyTable->add_data(std::time(0), *failureBannerWidget->getSelected());
  middleware->send(false, *failureBannerWidget->getSelected());
}

void MainWindow::onHistorySelect(std::string timestamp,
                                 const failures::Failure *selected) {
  eventDetailWidget->show_failure_detail(timestamp, selected);
}

void MainWindow::onHistorySelect(std::string timestamp,
                                 const results::Result *selected) {
  eventDetailWidget->show_result_detail(timestamp, selected);
}

void MainWindow::onComStateChanged(StatusBarWidget::State state) {
  failureBannerWidget->setEnabled(state == StatusBarWidget::State::CONNECTED);
}

/****** Events du middleware ******/
void MainWindow::onReceiveResult(jbox::results::Result result) {
  historyTable->add_data(std::time(0), result);
}

}  // namespace graphics
}  // namespace jbox
