#ifndef SRC_INTERFACE_SRC_MIDDLEWARE_INCLUDE_MIDDLEWARE_H_INCLUDED_
#define SRC_INTERFACE_SRC_MIDDLEWARE_INCLUDE_MIDDLEWARE_H_INCLUDED_

#include <QtWidgets>

#include "MainWindow.h"
#include "virtualcomport.h"

namespace jbox {
namespace middleware {

class Middleware {
 public:
  Middleware(int &argc, char** argv);

  /**
   * Démarre le middleware
   *
   * @return la valeur de retour de la fenêtre qt
   */
  int start();

  /**
   * Connect to a COM port
   *
   * @param port the port to connect to
   */
  void connect(std::string port);

  /**
   * Envoi une failure à la jammerbox
   * @param failure La failure à envoyer
   */
  void send(bool isStart, failures::Failure failure);


  /**
   * Callback appelée lors de la réception d'un message
   *
   */
  void receive();


  /**
   * Choix de CAM utilisé
   *
   */
  void set_cam(int cam_id);
  

 private:
  QApplication app;

  jbox::graphics::MainWindow mainWindow;
  jbox::com::VirtualComPort vcp;
};

}  // namespace middleware
}  // namespace jbox

#endif
