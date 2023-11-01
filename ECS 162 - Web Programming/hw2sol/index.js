// index.js
// This is our main server file

const express = require("express");

const db = require("./sqlWrap");
const dbo = require("./databaseOps");

// gets data out of HTTP request body 
// and attaches it to the request object
const bodyParser = require('body-parser');

// create object to interface with express
const app = express();

// code below sets up the express pipeline

// the static server
// make all the files in 'public' available
app.use(express.static("public"));

// if no file specified, return the main page
app.get("/", (request, response) => {
  response.sendFile(__dirname + "/public/my_videos.html");
});

// get JSON from body of HTTP request, run JSON.parse, and put it in req.body
app.use(bodyParser.json());
 
// print info about incoming HTTP request 
// for debugging
app.use(function(req, res, next) {
  console.log(req.method,req.url);
  next();
})

// request to add a video to the database
app.post("/videoData", 
  async function(req, res) {
    let url = req.body.URL;
    let nickname = req.body.nickname;
    let username = req.body.username;
    console.log("I am here");
    console.log("add video", url, nickname, username);
    
    // check the number of videos in the database
    let numVideos = await dbo.get_num_videos();
    if (numVideos != null) {
      if (numVideos >= 8) {
        //display an alert that the db is full
        res.json({msg: "database is full"});
      } else {
        // otherwise, find most recent item and toggle
        await dbo.update_video();
        // insert new item into db
        await dbo.post_video(url, nickname, username);
        let dbState = await dbo.get_all()
        console.log(dbState);
        res.json({});
      }
    }
});

// get the URL of the most recent video
app.get("/getMostRecent", async function(req, res) {
  console.log("getting the most recent video data");
  let result = await dbo.json();
  res.json(result);
});

// get all the data in the database
app.get("/getAll", async function(req, res) {
  console.log("getting all video data");
  let result = await dbo.get_all();
  res.json(result);
})

// remove a video from the database
app.post("/deleteVideo", 
  async function(req, res) {
    let nickname = req.body.nickname;

    console.log("delete video", nickname);

    await dbo.delete_video(nickname);
    res.json({});
  }
);

// Need to add response if page not found!
app.use(function(req, res){
  res.status(404); 
  res.type('txt'); 
  res.send('404 - File '+req.url+' not found'); 
});

// end of pipeline specification

// Now listen for HTTP requests
// it's an event listener on the server!
const listener = app.listen(3000, function () {
  console.log("The static server is listening on port " + listener.address().port);
});
