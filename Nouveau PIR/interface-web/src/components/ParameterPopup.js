import React from "react";
import Modal from "react-modal";
import "../CSS/ParameterPopup.css";
import "../CSS/MainPage.css";

export default function ParameterPopup(truc) {
  const [modalIsOpen, setIsOpen] = React.useState(false);

  function openModal() {
    console.log("Lol");
    setIsOpen(true);
  }

  function closeModal() {
    setIsOpen(false);
  }

  truc = openModal;

  return (
    <Modal isOpen={modalIsOpen} onRequestClose={closeModal}>
      <div className="test-configuration flex-col-hstart-vstart clip-contents">
        <div className="group-917 flex-col-hcenter">
          <p className="txt-120 flex-hcenter">Nom du test</p>
          <div className="group-213 flex-col-hend">
            <div className="group-21">
              <p className="txt-649 flex-hcenter">Parametre :</p>
              <input className="rectangle-17 txt-905" />
            </div>
            <div className="group-786 flex-row">
              <button className="group-6">
                <p className="txt-905 flex-hcenter">Let’s not go</p>
              </button>
              <button className="group-6">
                <p className="txt-637 flex-hcenter">Let’s go</p>
              </button>
            </div>
          </div>
        </div>
      </div>
    </Modal>
  );
}
