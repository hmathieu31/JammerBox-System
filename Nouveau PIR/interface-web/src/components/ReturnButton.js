<<<<<<< HEAD:Nouveau PIR/interface-web/src/components/returnButton.js
import React from "react";
import "../CSS/returnButton.css";
=======
import "../CSS/ReturnButton.css";
>>>>>>> origin/InterfaceWeb:Nouveau PIR/interface-web/src/components/ReturnButton.js
import { useNavigate } from "react-router-dom";

function ReturnButton() {
  let navigate = useNavigate();
  const HomePage = () => {
    navigate(-1);
  };

  return (
    <div className="flex-col-hstart-vstart topleft">
      <input
        class="arrow-circle-up"
        type="submit"
        value=""
        onClick={HomePage}
      />
    </div>
  );
}

export default ReturnButton;
