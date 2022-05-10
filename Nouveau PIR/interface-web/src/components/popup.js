import React from "react";
import "../CSS/popup.css";
import { Navigate, useNavigate } from "react-router-dom";
 
const Popup = props => {
    let navigate = useNavigate();

    let Test_result = () => {
      navigate("/test_result")
    }

    // const clickEvent = () => {
    //     props.handleClose;
    //     Test_result(); 
    // }

  return (
    <div className="popup-box">
      <div className="box">
        <span className="close-icon" onClick={props.handleClose}>x</span>
        <b>Design your Popup</b>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.</p>
        <button onClick={Test_result()} >Test button</button>
      </div>
    </div>
  );
};
 
export default Popup;