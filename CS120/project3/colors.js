var red = 0
var green = 0
var blue = 0

function updateSwatch() {
  var color = makeRGB()
  console.log("Color is now", color)
  $("#disprgb").html(color)
  $("div#swatch").css("background", color)
}

function getRGB(str){
  var match = str.match(
    /rgba?\((\d{1,3}), ?(\d{1,3}), ?(\d{1,3})\)?(?:, ?(\d(?:\.\d?))\))?/
  );
  return match ? {
    red: match[1],
    green: match[2],
    blue: match[3]
  } : {};
}

function updateColors() {
  var rgb = getRGB($(this).css("background-color"))
  red = rgb.red
  green = rgb.green
  blue = rgb.blue
  updateSliders()
  updateSwatch()
}

function updateSliders() {
  $("input#red").val(red)
  $("input#green").val(green)
  $("input#blue").val(blue)
}

function makeRGB() {
  return "rgb(" + red + "," + green + "," + blue + ")"
}

$(function(){
  console.log("DOM Ready")
  updateSliders()
  updateSwatch()

  $("input").on('input', function(){
    if($(this).attr("id") == "red") {
      red = $(this).val()
    } else if($(this).attr("id") == "green") {
      green = $(this).val()
    } else if($(this).attr("id") == "blue") {
      blue = $(this).val()
    }
    updateSwatch()
  })

  $("#palette > *").click(updateColors)

  $("#swatch").click(function() {
    var elt = $("<div></div>")
    elt.css("background", makeRGB())
    elt.on("click", updateColors)
    elt.dblclick(function() {
      $(this).remove()
    })
    $("div#palette").append(elt)
  })
})
