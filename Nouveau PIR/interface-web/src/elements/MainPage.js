import "../CSS/MainPage.css";
import { useNavigate } from "react-router-dom";
import RecordSignal from "../components/RecordSignal";

function MainPage() {
  let navigate = useNavigate();

  let Test_selection = () => {
    navigate("/synthesize_tests");
  };

  let History_selection = () => {
    navigate("/tests_historics");
  };

  let Configuration_selection = () => {
    navigate("/configuration");
  };

  return (
    <>
      <div className="frame-1">
        <div className="group-19">
          <p className="txt-271 flex-hcenter">PIR Interface</p>
          <div className="flex-col">
            <button className="group-6" onClick={Test_selection}>
              <p className="txt-733 flex-hcenter">Inject Fault</p>
            </button>
            <button className="group-6" onClick={Configuration_selection}>
              <p className="txt-733 flex-hcenter">Configuration</p>
            </button>
            <button className="group-6" onClick={History_selection}>
              <p className="txt-733 flex-hcenter">Faults Injection Logs</p>
            </button>
            <RecordSignal />
          </div>
        </div>
      </div>
    </>
  );
}

export default MainPage;
