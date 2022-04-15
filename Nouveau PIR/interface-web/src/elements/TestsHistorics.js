import "../CSS/UnderConstruction.css";

import "../components/ReturnButton.js"
import ReturnButton from "../components/ReturnButton.js";

export default function UnderConstruction() {
  return( 
  <>
    { ReturnButton() }
    <div className="frame-2" />
  </>
  );
}


