
var map;
// var grandcanyon = {lat: 36.246489, lng: -113.101544}
// var liubk = {lat:40.689967, lng: -73.981380}
var dunns = {lat: 18.418553, lng: -77.140041}
var marina = {lat: 18.180589, lng: -76.452761}
var bond = {lat: 18.406028, lng: -76.948940}
var boston = {lat: 18.157247, lng: -76.353602}

// {lat: 40.690450, lng: -73.981163}

function clearNavs() {
  // We're using <button> for navigation elements,
  // so clear the 'disabled' attribute from all of them.
  var navs = document.getElementsByClassName("navitem")
  //console.log(navs)
  for(var i = 0; i < navs.length; i++) {
    navs[i].className = "navitem"
  }
}

function setNavTo(id) {
  document.getElementById(id).className = "navitem selected"
}

function gotoBond() {
  clearNavs()
  setNavTo("bond")
  map.panTo(bond)
  map.setZoom(16)
  var img = document.getElementById("descimg")
  img.setAttribute("src", "jamesbond.jpg")
  img.setAttribute("alt", "Sean Connery on set for Dr. No")
  var desc = document.getElementById("description")
  desc.innerHTML = "This beach is famous for being featured in the movie Dr. No, \
                    a James Bond film. Like many beaches on the north coast, it\
                    has white sand and clear blue waters."
}
function gotoDunns() {
  clearNavs()
  setNavTo("dunns")
  map.panTo(dunns)
  map.setZoom(15)
  var img = document.getElementById("descimg")
  img.setAttribute("src", "dunns.jpg")
  img.setAttribute("alt", "Dunns River Falls")
  var desc = document.getElementById("description")
  desc.innerHTML = "Dunns River Falls is famous for it's easy to climb waterfall \
                    with beautiful rocks next to a wite sand beach. \
                    Interesting tidbit, the welcome sign (if it wasn't changed by now)\
                    was designed by my older brother who is a graphic designer."
}
function gotoMarina() {
  clearNavs()
  setNavTo("marina")
  map.panTo(marina)
  map.setZoom(16)
  var img = document.getElementById("descimg")
  img.setAttribute("src", "errolflynn.jpg")
  img.setAttribute("alt", "Errol Flynn Marina")
  var desc = document.getElementById("description")
  desc.innerHTML = "The Errol Flynn Marina is a beautiful spot perfect for an \
                    evening stroll with family or friends. There is also a small \
                    beach you can go swimming as well as a hotel, bar and pool.\
                    I spent many of my teenage days here with my friends."
}
function gotoBoston() {
  clearNavs()
  setNavTo("boston")
  map.panTo(boston)
  map.setZoom(16)
  var img = document.getElementById("descimg")
  img.setAttribute("src", "bostonbeach.jpg")
  img.setAttribute("alt", "Boston Beach")
  var desc = document.getElementById("description")
  desc.innerHTML = "Home of the famous 'Boston Jerk Festival' and the best \
                    jerk stands on the island. Jerk is Jamaica's infamous method \
                    for smoking meats to perfection (highly subjective but I stand by my beilefs)."
}

function initMap() {
  map = new google.maps.Map(document.getElementById('themap'), {
    center: dunns,
    zoom: 6
  });
  gotoMarina()
  var bondMarker = new google.maps.Marker({
    position: bond,
    map: map
  });
  var dunnsMarker = new google.maps.Marker({
    position: dunns,
    map: map
  });
  var bostonMarker = new google.maps.Marker({
    position: boston,
    map: map
  });
  var marinaMarker = new google.maps.Marker({
    position: marina,
    map: map
  });

  bondMarker.addListener('click', gotoBond)
  dunnsMarker.addListener('click', gotoDunns)
  marinaMarker.addListener('click', gotoMarina)
  bostonMarker.addListener('click', gotoBoston)
}
