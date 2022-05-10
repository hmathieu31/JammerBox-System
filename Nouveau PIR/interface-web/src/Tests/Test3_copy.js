import React from "react";
import "./Test3.css";
import { Navigate, useNavigate } from "react-router-dom";

function Test3() {
  let navigate = useNavigate();

  let Synthesize_tests = () => {
    navigate("/synthesize_tests")
  }

  return (
    <>
    <div className="group-19">
      <p className="txt-271 flex-hcenter">PIR Interface</p>
      <div className="flex-col">
        <button className="group-6" onClick={Synthesize_tests}>
          <p className="txt-733 flex-hcenter">
            Synthesize tests
          </p>
        </button>
        <button className="group-6">
          <p className="txt-733 flex-hcenter">Test historics</p>
        </button>
      </div>
    </div>
  </>
  );
}

export default Test3;