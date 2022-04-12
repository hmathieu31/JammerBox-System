import "../CSS/MainPage.css";
import "../CSS/Background.css";
import { useNavigate } from "react-router-dom";

function SynthesizeTests() {
  let navigate = useNavigate();
  const Home = () => {
      navigate("/");
  }

  var Buttons = ["Lol", "Test", "Haha!", "Truc", "NOOOOn"];

  function makeButton(data) {
    return (
      <button
        key={Buttons.indexOf(data)}
        className="group-6"
        onClick={console.log}
      >
        {data}
      </button>
    );
  }

  return (
    <>
    <div className="frame-1">
      <div>
        {Buttons.map(makeButton, this)}
      </div>       
      <div>
      <button className="group-6" onClick={Home}>
          <p className="txt-733 flex-hcenter">
            Home
          </p>
        </button>
      </div>
    </div>
    </>
  );
}

export default SynthesizeTests