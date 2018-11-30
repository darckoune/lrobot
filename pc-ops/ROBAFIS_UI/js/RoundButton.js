class RoundButton {
  constructor(ctxGamepad, posX, posY, size,color) {
    this.ctxGamepad   = ctxGamepad;
    this.posX  = posX;
    this.posY  = posY;
    this.size  = size;
    this.color = color;
  }

  draw() {
    ctxGamepad.lineWidth = 1;
    ctxGamepad.fillStyle = this.color;
    ctxGamepad.strokeStyle = this.color;

    ctxGamepad.beginPath();
    ctxGamepad.arc(this.posX, this.posY, this.size, 0, 2*Math.PI);
    ctxGamepad.fill();
  }

}
