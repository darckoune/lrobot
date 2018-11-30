class JoyStick {
  constructor(ctxGamepad, posX, posY, size, range, color) {
    this.ctxGamepad   = ctxGamepad;
    this.posX  = posX;
    this.posY  = posY;
    this.size  = size;
    this.range = range;
    this.color = color;

    this.valX  = 0;
    this.valY  = 0;
  }

  draw() {
    ctxGamepad.lineWidth = 2;
    ctxGamepad.fillStyle = this.color;
    ctxGamepad.strokeStyle = this.color;

    ctxGamepad.beginPath(); // internal circle
    ctxGamepad.arc(this.posX, this.posY, this.size, 0, 2*Math.PI);
    ctxGamepad.stroke();

    var x = this.posX + (this.valX / 100) * this.range;
    var y = this.posY + (this.valY / 100) * this.range;
    ctxGamepad.beginPath(); // external circle
    ctxGamepad.arc(x, y, this.size - 5, 0, 2*Math.PI);
    ctxGamepad.fill();
  }

  setXY(nValX, nValY) {
    this.valX = nValX;
    this.valY = nValY;
  }
}
