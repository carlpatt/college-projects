$(function(){
  console.log("HELLO WORLD")
  $.getJSON("http://localhost:5000/people/",
    function(data) {
      console.log("SUCCESS", data)
      for(var i = 0; i < data._items.length; i++) {
        console.log(data._items[i].name)
        var person = $("<li>" + data._items[i].name
                        + "</li>")
        console.log(person)
  //      person.appendTo($("#people"))
         $("#people").append(person)
      }
      $.getJSON("http://localhost:5000/books/",
        function(data) {
          console.log("SUCCESS", data)
          for(var i = 0; i < data._items.length; i++) {
            console.log(data._items[i].name)
            var books = $("<li>" + data._items[i].name + ', '
                            + data._items[i].author + ', '
                            + data._items[i].publisher + ', '
                            + data._items[i].published + '. '
                            + "</li>")
            console.log(books)
      //      person.appendTo($("#people"))
             $("#books").append(books)
          }
    })
})
})
