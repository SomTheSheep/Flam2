"use strict";
// A dummy base64 encoded image string.
// In a real application, this would be sent from the Android app.
var dummyFrame = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mNkYAAAAAYAAjCB0C8AAAAASUVORK5CYII=";
var frameImage = document.getElementById("processedFrame");
var statsDiv = document.getElementById("stats");
frameImage.src = dummyFrame;
statsDiv.innerHTML = "\n    <p>Resolution: 1x1</p>\n    <p>FPS: 60</p>\n";
