var data = null;
function init(){
  const req = new XMLHttpRequest();
  req.addEventListener("load", processData);
  req.open("GET", "../php/getData.php");
  req.send();
}

init();

function processData() {
  data = JSON.parse(this.responseText);
  for(let i = 0; i < data.length; i++){
    let html = `
      <p>`+data[i].id+`</p>
      <p>`+data[i].name+`</p>
      <p>`+data[i].city+`</p>
      <p>`+data[i].age+`</p>
    `
    document.getElementById('dataWrapper').innerHTML += html;
  }
}

function addData() {
  var name = document.getElementById('form__name').value;
  var age = document.getElementById('form__age').value;
  var city = document.getElementById('form_city').value;
  console.log(name, age, city)
  var req = new XMLHttpRequest();
  req.open("POST", "../php/sendData.php", true);
  req.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  var sendData =  'name=' + encodeURIComponent(name) +
                  '&city=' + encodeURIComponent(city) +
                  '&age=' + encodeURIComponent(parseInt(age));
  req.send(sendData);
  setTimeout(()=>{
    //location.reload();
  }, 500)
}

document.querySelector('form').addEventListener('submit', function(event) {
  event.preventDefault(); // Prevents the form from submitting and the page from reloading
  // Your custom logic here
});
document.getElementById('addData__form').addEventListener('submit', function(event) {
  event.preventDefault();
  var name = document.getElementById('form__name').value;
  var age = document.getElementById('form__age').value;
  var city = document.getElementById('form__city').value;
  console.log(name, age, city)
  var req = new XMLHttpRequest();
  req.open("POST", "../php/sendData.php", true);
  req.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  var sendData =  'name=' + encodeURIComponent(name) +
                  '&city=' + encodeURIComponent(city) +
                  '&age=' + encodeURIComponent(parseInt(age));
  req.send(sendData);
  setTimeout(()=>{
    location.reload();
  }, 500)
})
