class SquareButton {
  constructor(ctxGamepad, x, y, w, h, radius, color, clickedColor) {
    this.ctxGamepad = ctxGamepad;
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.radius = radius;
    this.color = color;
    this.clickedColor = clickedColor;
  }

  draw(customColor) {
    var r = this.x + this.w;
    var b = this.y + this.h;
    ctxGamepad.fillStyle = customColor ? customColor : this.color;
    ctxGamepad.beginPath();
    ctxGamepad.moveTo(this.x + this.radius, this.y);
    ctxGamepad.lineTo(r - this.radius, this.y);
    ctxGamepad.quadraticCurveTo(r, this.y, r, this.y + this.radius);
    ctxGamepad.lineTo(r, this.y + this.h - this.radius);
    ctxGamepad.quadraticCurveTo(r, b, r - this.radius, b);
    ctxGamepad.lineTo(this.x + this.radius, b);
    ctxGamepad.quadraticCurveTo(this.x, b, this.x, b - this.radius);
    ctxGamepad.lineTo(this.x, this.y + this.radius);
    ctxGamepad.quadraticCurveTo(this.x, this.y, this.x + this.radius, this.y);
    ctxGamepad.fill();
  }

  erase() {
    this.draw(this.clickedColor);
  }
}
