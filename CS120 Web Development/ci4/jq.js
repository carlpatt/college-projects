// Depends on jQuery being loaded first.

// jQuery encapsulates most of its functionality
// into an object called "$".

var highlighted = false
var destVisitedCount = 1

function jsHighlight()
{
    var elts = document.getElementsByTagName("li")
    // Apply to each element in list
    for(var i = 0; i < elts.length; i++) {
        elts[i].style["font-weight"] = highlighted ? "normal" : "bold"
    }
    highlighted = ! highlighted
}

function jqHighlight() {
    $("li").css("font-weight", highlighted ? "normal" : "bold")
    highlighted = ! highlighted
}

// Equivalent to "document.onload" -- this function is executed
// as soon as the DOM is properly initialized.
$(function(){
    // Now we know DOM is initialized, can proceed with setup.
    $("li").click(function(){
        $(this).toggleClass("finished")
        destVisitedCount += $(this).hasClass("finished")? 1 : -1
        $("#destCount").html(destVisitedCount + "  destination" +
                             (destVisitedCount == 1 ? "" : "s"))
    });
    $("#reset").click(function() {
      $("li").removeClass("finished")
      destVisitedCount = 0
      $("#destCount").html(destVisitedCount + " destination")
    })
})

console.log("Loaded jq.js")
