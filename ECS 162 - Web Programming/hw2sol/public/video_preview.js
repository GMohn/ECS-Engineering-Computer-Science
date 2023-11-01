let reloadButton = document.getElementsByClassName("reload")[0];
let divElmt = document.getElementById("tiktokDiv");
let nickname = document.getElementById("nickname");

// set up button
reloadButton.addEventListener("click",reloadVideo);

async function getMostRecent() {
  let recentVideoRes = await fetch("/getMostRecent");
  let recentVideoData = await recentVideoRes.json();
  console.log(recentVideoData);
  const recentURL = recentVideoData.url;
  console.log("most recently added video url", recentURL);
  nickname.textContent = recentVideoData.nickname;
  addVideo(recentURL, divElmt);
  loadTheVideos();
}

// Add the blockquote element that tiktok will load the video into
async function addVideo(tiktokurl,divElmt) {
  let videoNumber = tiktokurl.split("video/")[1];

  let block = document.createElement('blockquote');
  block.className = "tiktok-embed";
  block.cite = tiktokurl;
  // have to be formal for attribute with dashes
  block.setAttribute("data-video-id",videoNumber);
  block.style = "width: 325px; height: 563px;"

  let section = document.createElement('section');
  block.appendChild(section);
  
  divElmt.appendChild(block);
}

// Ye olde JSONP trick; to run the script, attach it to the body
function loadTheVideos() {
  body = document.body;
  script = newTikTokScript();
  body.appendChild(script);
}

// makes a script node which loads the TikTok embed script
function newTikTokScript() {
  let script = document.createElement("script");
  script.src = "https://www.tiktok.com/embed.js"
  script.id = "tiktokScript"
  return script;
}

// the reload button; takes out the blockquote and the scripts, and puts it all back in again.
// the browser thinks it's a new video and reloads it
function reloadVideo () {
  
  // get the two blockquotes
  let blockquotes = document.getElementsByClassName("tiktok-embed");

  // and remove the indicated one
    block = blockquotes[0];
    console.log("block",block);
    let parent = block.parentNode;
    parent.removeChild(block);

  // remove both the script we put in and the
  // one tiktok adds in
  let script1 = document.getElementById("tiktokScript");
  let script2 = script1.nextElementSibling;

  let body = document.body; 
  body.removeChild(script1);
  body.removeChild(script2);

  addVideo(block.cite, divElmt);
  loadTheVideos();
}

getMostRecent();
