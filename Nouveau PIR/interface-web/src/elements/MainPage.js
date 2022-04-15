import React from "react";
import "../CSS/MainPage.css";
import { Navigate, useNavigate } from "react-router-dom";

function MainPage() {
  let navigate = useNavigate();

  let Test_selection = () => {
    navigate("/synthesize_tests")
  }

  let History_selection = () => {
    navigate("/tests_historics")
  }

  return (
    <>
    <div className="frame-1">
      <div className="group-19">
        <p className="txt-271 flex-hcenter">PIR Interface</p>
        <div className="flex-col">
          <button className="group-6" onClick={Test_selection}>
            <p className="txt-733 flex-hcenter">
              Synthesize tests
            </p>
          </button>
          <button className="group-6" onClick={History_selection}>
            <p className="txt-733 flex-hcenter">Test historics</p>
          </button>
        </div>
      </div>
    </div>
    </>
  );
}

export default MainPage;