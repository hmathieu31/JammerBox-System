import React, { useContext, useState } from "react";
import "../CSS/RecordSignal.css";

function RecordSignal() {
  const [recording, setRecord] = useState(
    JSON.parse(localStorage.getItem("recording"))
  );

  const recordToggle = () => {
    setRecord(!recording);
    localStorage.setItem("recording", JSON.stringify(!recording));
    fetch("http://localhost:8080/record", {
      method: "PUT",
      mode: "cors",
      headers: { "Content-type": "application/json" },
      body: JSON.stringify({}),
    }).then(
      (data) => {
        console.log(data.status);
      },
      (error) => {
        console.log("Did not send data!");
      }
    );
  };

  return (
    <div className="flex-col-hstart-vstart">
      <button
        className="group-6 txt-733"
        type="submit"
        value=""
        onClick={recordToggle}
      >
        <div className="row">
          {recording ? (
            <div>
              <p className="column">STOP RECORDING SIGNALS</p>
              <svg
                width="25"
                height="25"
                viewBox="0 0 24 24"
                fill="none"
                xmlns="http://www.w3.org/2000/svg"
                className="column icon"
              >
                <path
                  d="M17.2757 5.46995C17.7109 5.63029 18 6.04492 18 6.50872L18 17.4912C18 17.955 17.7109 18.3696 17.2757 18.53C16.4523 18.8333 15.5477 18.8333 14.7243 18.53C14.2891 18.3696 14 17.955 14 17.4912L14 6.50872C14 6.04492 14.2891 5.63029 14.7243 5.46995C15.5477 5.16659 16.4523 5.16659 17.2757 5.46995Z"
                  fill="black"
                />
                <path
                  d="M9.27568 5.46995C9.71088 5.63029 10 6.04492 10 6.50872L10 17.4912C10 17.955 9.71088 18.3696 9.27568 18.53C8.45228 18.8333 7.54772 18.8333 6.72432 18.53C6.28912 18.3696 6 17.955 6 17.4912L6 6.50872C6 6.04492 6.28912 5.63029 6.72432 5.46995C7.54772 5.16659 8.45228 5.16659 9.27568 5.46995Z"
                  fill="black"
                />
              </svg>
            </div>
          ) : (
            <div>
              <p className="column icon">START RECORDING SIGNALS</p>
              <svg
                width="20"
                height="20"
                viewBox="0 0 16 16"
                fill="none"
                xmlns="http://www.w3.org/2000/svg"
                className="column icon"
              >
                <path
                  d="M14.266 9.51616C15.2579 8.74868 15.2579 7.25122 14.266 6.48374C11.2685 4.16434 7.9213 2.33619 4.34976 1.06771L3.69729 0.835971C2.44901 0.392631 1.1305 1.23719 0.961511 2.52574C0.489352 6.12595 0.489351 9.87394 0.961511 13.4742C1.1305 14.7627 2.44901 15.6073 3.69728 15.1639L4.34976 14.9322C7.9213 13.6637 11.2685 11.8356 14.266 9.51616Z"
                  fill="black"
                />
              </svg>
            </div>
          )}
        </div>
      </button>
    </div>
  );
}

export default RecordSignal;
