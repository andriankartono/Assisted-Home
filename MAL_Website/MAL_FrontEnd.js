// Funktionen um die Bilder auf der Website in verschiedenen Arten
// zu beleuchten. Der erste Parameter ist der Objektstring, der im 
// HTML File für das Objekt definiert wurde
// Z.B. bei <div class="container" id="washMash">
// wäre der objectString "washMash"

// der zweite Parameter - statusString - ist der String, der als Text ausgegeben wird

// der dritte Parameter - timeString - ist der String, der unten rechts, üblicherweise 
// eine Zeit, ausgegeben wird

// Funktion, die Code, den alle Frontendfunktionen brauchen, bereitstellt
function alterObject(objectString, statusString, timeString, borderString, opacityString) {
    let container = document.getElementById(objectString);

    let img = container.querySelector('img'); 
    let txt = container.querySelector('.centeredTop');
    let timeStr = container.querySelector('.rightBottom');

    container.style["border"] = borderString;
    img.style["opacity"] = opacityString;
    txt.innerHTML = statusString;
    timeStr.innerHTML = timeString;
}

function changeViewToOK(objectString, statusString, timeString) {
    alterObject(objectString, statusString, timeString, "5px solid green", "0.2");
}


function changeViewToNotOK(objectString, statusString, timeString) {
    alterObject(objectString, statusString, timeString, "5px solid red", "1");
}

// Zum Beispiel um eine Warnung "Sensor Küchenfenster nicht verbunden!" auszugeben
function changeViewToError(objectString, statusString, timeString) {
    alterObject(objectString, statusString, timeString, "5px solid orange", "0.1");
}

