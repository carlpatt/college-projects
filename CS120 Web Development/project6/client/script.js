var PEOPLE = "http://localhost:5000/people/"
var EDITING = false

function loadUsers() {
  $("#people").empty()
  $.ajaxSetup({cache: false})
  $.getJSON(PEOPLE,
    function(data) {
      for(var i = 0; i < data._items.length; i++) {
        var p = data._items[i]
        var person = $(
          `<li>
            <span class="read-write" style="display:none">
              <input type="text" id="editn" value="${p.name}">
              <input type="text" id="editj" value="${p.job}">
              <button onclick="saveUser(this,'${p._id}','${p._etag}')">Save</button>
              <button onclick="cancelEdit(this,'${p.name}', '${p.job}')">Cancel</button>
            </span>
            <span class="read-only">
              <span onclick="editUser(this,'${p._id}')">${p.name}, ${p.job}</span>
              <button onclick="deleteUser('${p._id}','${p._etag}')">
                delete
              </button>
            </span>
           </li>`
        )
        console.log(person)
        person.appendTo($("#people"))
      }
    })
}

$(function(){
  console.log("HELLO WORLD")
  loadUsers()
})

function editUser(span, id) {
  if(!EDITING) {
    $(span).parent().hide().prev().show()
    EDITING = true
  }
}

function cancelEdit(button, originalName, originalJob) {
  EDITING = false
  $(button).siblings('#editn').val(originalName)
  $(button).siblings('#editj').val(originalJob)
  $(button).parent().hide().next().show()
}

function deleteUser(id, etag) {
  $.ajax({
    method: "DELETE",
    url: PEOPLE + id,
    headers: {
      "If-Match": etag
    },
    success: function() {
      loadUsers()
    },
  })
}

function saveUser(button, id, etag) {
  var obj = {"name": $(button).siblings('#editn').val(), "job": $(button).prev().val()}
  $.ajax({
    method: "PUT",
    url: PEOPLE + id,
    headers: {"If-Match": etag},
    dataType: "json",
    data: obj,
    success: function() {
      EDITING = false
      loadUsers()
    },
    error: function(jqXHR, textStatus, errorThrown) {
      console.log("FAIL", jqXHR, textStatus, errorThrown)
      $(button).prev().css("border", "1px solid red")
    }
  })
}

function addUser(event) {
  event.preventDefault()
  var name = $("#username").val()
  var job = $("#job").val()
  var obj = {"name": name, "job" : job}
  $.ajax({
    method: "POST",
    url: PEOPLE,
    dataType: "json",
    data: obj,
    success: function() {
      // Clear the name entry
      $("#username").val("")
      $("#job").val("")
      loadUsers()
    },
    failure: function() {
      console.log("FAILED....")
    }
  })
}
