import React from "react"
import "../CSS/ReturnButton.css"
import { useNavigate } from "react-router-dom";

function ReturnButton() {
  let navigate = useNavigate();
  const HomePage = () => {
      navigate("/");
  }

  return(
    <div className="flex-col-hstart-vstart topleft">
      <input class="arrow-circle-up" type="submit" value="" onClick={HomePage} />
    </div>
  );
}


export default ReturnButton