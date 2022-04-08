import "./MainPage.css";
import "./Background.css";

export default function Test2() {
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
  return <div>{Buttons.map(makeButton, this)}</div>;
}
