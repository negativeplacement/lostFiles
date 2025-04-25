function infoContent () {
    var content = `
      <h2>Info</h2>
      <p>
      Special Herbs, Vol. 1 is the first album in the Special Herbs series of instrumental works released by MF Doom under the Metal Fingers moniker on various independent hip hop labels.
      Establishing the trend for later albums in the series, each track is named after a herb or similar flora.
      </p>
    `;
    
    var ele = document.createElement("div");
    ele.innerHTML = content;
    return ele; 
}