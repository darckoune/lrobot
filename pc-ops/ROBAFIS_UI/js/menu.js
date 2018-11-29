var strCopyMenu = '';

addWebsocketCallback(function(data){
  if(data.type == "controller") {
    var str     = data.message;
    strCopyMenu = str.split(':');
    var links   = document.querySelectorAll(".mynav a");
    if(strCopyMenu[1] == "PILOT") {
      links[0].click();
    }
    if(strCopyMenu[1] == "MANU") {
      links[1].click();
    }
  }
});

$(document).ready(function(){
    var target = document.querySelector(".target");
    var links = document.querySelectorAll(".mynav a");
    var li = document.querySelectorAll(".mynav li");

    target.style.borderColor = "#02948A";

    const margin = 40;
    for (var i = 0; i < li.length; i++) {
        li[i].style.marginRight = margin + "px";
        li[i].style.marginLeft = margin + "px";
    }

    for (var i = 0; i < li.length; i++) {
        var span = document.createElement('span');
        span.id = 'menu_item_' + i;

        var width = links[i].getBoundingClientRect().width + margin * 2;
        var height = links[i].getBoundingClientRect().height;
        var left = links[i].getBoundingClientRect().left + window.pageXOffset - margin;
        var top = links[i].getBoundingClientRect().top + window.pageYOffset;

        span.style.width = width + "px";
        //span.style.height = height + "px";
        span.style.left = left + "px";
        //span.style.top = top + 1 + "px";
        span.style.transform = "none";

        li[i].appendChild(span);
    }

    function mouseenterFunc() {
      if (!this.parentNode.classList.contains("active")) {
        for (var i = 0; i < links.length; i++) {
          if (links[i].parentNode.classList.contains("active")) {
            links[i].parentNode.classList.remove("active");
          }
          //links[i].style.opacity = "0.25";
          //links[i].style.color = "#929BA3";
        }

        this.parentNode.classList.add("active");
        //this.style.opacity = "1";
        //this.style.color = "#FFFFFF";

        var width = this.getBoundingClientRect().width + margin * 2;
        var height = this.getBoundingClientRect().height;
        var left = this.getBoundingClientRect().left + window.pageXOffset - margin;
        var top = this.getBoundingClientRect().top + window.pageYOffset;

        target.style.width = width + "px";
        target.style.height = height + "px";
        target.style.left = left + "px";
        //target.style.top = top + 1 + "px";
        target.style.transform = "none";
        target.style.position = "fixed";
      }
    }

    for (var i = 0; i < links.length; i++) {
      links[i].addEventListener("click", function (e) {return e.preventDefault();});
      links[i].addEventListener("click", mouseenterFunc);
    }

    function resizeFunc() {
      for (var i = 0; i < li.length; i++) {
        var span = document.getElementById('menu_item_' + i);

        var width = links[i].getBoundingClientRect().width + margin * 2;
        var height = links[i].getBoundingClientRect().height;
        var left = links[i].getBoundingClientRect().left - margin; //+ window.pageXOffset
        //var top = links[i].getBoundingClientRect().top + window.pageYOffset;
        var top = links[i].getBoundingClientRect().top + height

        span.style.width = width + "px";
        //span.style.height = height + "px";
        span.style.left = left + "px";
        span.style.top = top + "px";
        span.style.transform = "none";

        if(strCopyMenu[1] == "PILOT") {
          links[0].click();
        }
        if(strCopyMenu[1] == "MANU") {
          links[1].click();
        }

      }
    }

    window.addEventListener("resize", resizeFunc);
    window.addEventListener('scroll', resizeFunc);
    links[0].click();
});
