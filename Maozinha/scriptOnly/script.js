let checkboxf = document.querySelector("input[name=finger]");
let checkboxa = document.querySelector("input[name=arm]");

checkboxf.addEventListener('change', function() {
  if (this.checked) {
    console.log("levantando dedo");
    $("#result").load( "/fingerOn");
  } else {
    console.log("voltando dedo");
    $("#result").load( "/fingerOff");
  }
});
checkboxa.addEventListener('change', function() {
  if (this.checked) {
    console.log("girando braço");
    $("#result").load( "/armOn");
  } else {
    console.log("voltando braço");
    $("#result").load( "/armOff");
  }
});