let Renderer;

onmessage = function (e) {
  console.log("Message received from main script");
  console.log(e.data);
  console.log("Possting message back to main script");
};
