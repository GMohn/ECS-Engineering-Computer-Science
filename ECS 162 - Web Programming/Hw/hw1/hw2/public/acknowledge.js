'use strict';

let continueButton = document.getElementById("continue");
continueButton.addEventListener("click", continueB);

let vidName = sessionStorage.getItem("videoname")
console.log(vidName);
vidName = "'" + vidName + "'";
document.getElementById("videoname").textContent = vidName;

/* back to home page */
function continueB() {
  window.location.href='https://TheBigSalmon-1-GeoffreyMohn.ecs162-s22.repl.co'
}