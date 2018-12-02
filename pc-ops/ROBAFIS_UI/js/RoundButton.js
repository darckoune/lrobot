class RoundButton {
  constructor(ctxGamepad, posX, posY, size,color, clickedColor = undefined) {
    this.ctxGamepad   = ctxGamepad;
    this.posX  = posX;
    this.posY  = posY;
    this.size  = size;
    this.color = color;
    this.clickedColor = clickedColor;
  }

  draw(customColor) {
    ctxGamepad.lineWidth = 1;
    ctxGamepad.fillStyle = customColor ? customColor : this.color;
    ctxGamepad.strokeStyle = customColor ? customColor : this.color;

    ctxGamepad.beginPath();
    ctxGamepad.arc(this.posX, this.posY, this.size, 0, 2*Math.PI);
    ctxGamepad.fill();
  }

  erase() {
    this.draw(this.clickedColor);
  }

}
