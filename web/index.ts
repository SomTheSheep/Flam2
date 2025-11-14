// A dummy base64 encoded image string.
// In a real application, this would be sent from the Android app.
const dummyFrame = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAQAAAC1HAwCAAAAC0lEQVR42mNkYAAAAAYAAjCB0C8AAAAASUVORK5CYII=";

const frameImage = document.getElementById("processedFrame") as HTMLImageElement;
const statsDiv = document.getElementById("stats");

frameImage.src = dummyFrame;

statsDiv.innerHTML = `
    <p>Resolution: 1x1</p>
    <p>FPS: 60</p>
`;
