class JoyStick {
  constructor(ctx, posX, posY, size, range, color) {
    this.ctx   = ctx;
    this.posX  = posX;
    this.posY  = posY;
    this.size  = size;
    this.range = range;
    this.color = color;

    this.valX  = 0;
    this.valY  = 0;
  }

  draw() {
    ctx.lineWidth = 2;
    ctx.fillStyle = this.color;
    ctx.strokeStyle = this.color;

    ctx.beginPath(); // internal circle
    ctx.arc(this.posX, this.posY, this.size, 0, 2*Math.PI);
    ctx.stroke();

    var x = this.posX + (this.valX / 100) * this.range;
    var y = this.posY + (this.valY / 100) * this.range;
    ctx.beginPath(); // external circle
    ctx.arc(x, y, this.size - 5, 0, 2*Math.PI);
    ctx.fill();
  }

  setXY(nValX, nValY) {
    this.valX = nValX;
    this.valY = nValY;
  }
}
