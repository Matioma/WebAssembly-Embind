// const readUploadedFileAsText = (inputFile) => {
//   const temporaryFileReader = new FileReader();

//   return new Promise((resolve, reject) => {
//     temporaryFileReader.onerror = () => {
//       temporaryFileReader.abort();
//       reject(new DOMException("Problem parsing input file."));
//     };

//     temporaryFileReader.onload = () => {
//       resolve(temporaryFileReader.result);
//     };
//     temporaryFileReader.readAsText(inputFile);
//   });
// };
// const handleUpload = async (event) => {
//   const file = event.target.files[0];
//   try {
//     const fileContents = await readUploadedFileAsText(file);
//     return fileContents;
//   } catch (e) {
//     console.warn(e.message);
//   }
// };

// let fragmentSource;
// let vertexSource;
// let objFile;

// function clearInput(target) {
//   target.value = null;
// }

// let vertexInput = document.getElementById("vertex-shader");
// vertexInput.addEventListener("click", (ev) => clearInput(ev.target));
// vertexInput.addEventListener("input", (ev) => {
//   handleUpload(ev).then((res) => {
//     vertexSource = res;
//   });
// });

// vertexInput.addEventListener("click", (ev) => console.log("working"));

// let fragmentInput = document.getElementById("fragment-shader");
// fragmentInput.addEventListener("click", (ev) => clearInput(ev.target));
// fragmentInput.addEventListener("input", (ev) => {
//   handleUpload(ev).then((res) => {
//     fragmentSource = res;
//   });
// });

// let objFileId = document.getElementById("obj-file");
// objFileId.addEventListener("click", (ev) => clearInput(ev.target));
// objFileId.addEventListener("input", (ev) => {
//   handleUpload(ev).then((res) => {
//     objFile = res;
//   });
// });

onmessage = function (e) {
  console.log("Message received from main script");
  var workerResult = "Result: " + e.data[0] * e.data[1];
  console.log("Posting message back to main script");
  postMessage(workerResult);
};
