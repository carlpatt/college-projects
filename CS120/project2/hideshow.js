$(document).ready(function(){
    $(".hideshow").click(function(){
      var $this = $(this);

      $this.toggleClass("hidden");

      if ($this.hasClass("hidden")) {
        $this.html("<i class=\"material-icons\">arrow_downward</i>Show answer");
      }
      else {
        $this.html("<i class=\"material-icons\">arrow_downward</i>Hide answer");
      }

      $(this).siblings().slideToggle();
    });
});
