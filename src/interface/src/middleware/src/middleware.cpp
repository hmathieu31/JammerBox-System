#include "middleware.h"

namespace jbox {
namespace middleware {

Middleware::Middleware(int& argc, char** argv) : app(argc, argv) {
  mainWindow.middleware = this;
}

int Middleware::start() {
  mainWindow.show();
  return app.exec();
}

void Middleware::connect(std::string port) {
  vcp.connect(port);
  receive();
}

void Middleware::send(bool isStart, failures::Failure failure) {
  std::string data =
      isStart ? failure.toStartMessage() : failure.toStopMessage();
  vcp.send(data);
}

void Middleware::receive() {
  std::thread([&]() {
    vcp.start_receive_thread([&](std::string data) {
      jbox::results::Result result(data.at(0));
      mainWindow.onReceiveResult(result);
    });
    while (1) {
    }
  }).detach();
}

void Middleware::set_cam(int cam_id) {
  vcp.set_cam(cam_id);
}

}  // namespace middleware
}  // namespace jbox
