import logo from "./logo.svg";
import "./App.css";
import MainPage from "./MainPage";
import Test2 from "./Test2";

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
        <Test2 />
      </header>
    </div>
  );
}

function Lol() {
  return (
    <div>
      <body>
        <h1>Ça marche?</h1>
        <a href="http://floppachat.ml/">Cliquez sur ce site svp</a>
      </body>
    </div>
  );
}

//export default App;
export default App;
