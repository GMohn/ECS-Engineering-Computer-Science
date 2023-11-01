let continueButton = document.getElementById("continue");
continueButton.addEventListener("click", continueB);

function continueB() {
  let username = document.getElementById("username").value;
  let url = document.getElementById("url").value;
  let videoname = document.getElementById("videoname").value;
  sessionStorage.setItem("videoname", videoname);
  window.location = "/acknowledge";
  
  let info = {username, url, videoname};
  console.log(info);

  postRequest(username+url+videoname);

}

async function sendPostRequest(url,data) {
  console.log("about to send post request");
  let response = await fetch(url, {
    method: 'POST', 
    headers: {'Content-Type': 'text/plain'},
    body: data });
  if (response.ok) {
    let data = await response.text();
    return data;
  } else {
    throw Error(response.status);
  }
}

function postRequest(info){
  console.log("starting up");
  sendPostRequest('/videoData',info)
  .then((data) => {
    console.log(data);
    sessionStorage.setItem("videoname", info[2]);
    window.location = "/acknowledge";
  })
  .catch((error) => {
    console.log("Error: ", error);
  });
}
