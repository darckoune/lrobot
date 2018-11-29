class RoundButton {
  constructor(ctx, posX, posY, size,color) {
    this.ctx   = ctx;
    this.posX  = posX;
    this.posY  = posY;
    this.size  = size;
    this.color = color;
  }

  draw() {
    ctx.lineWidth = 1;
    ctx.fillStyle = this.color;
    ctx.strokeStyle = this.color;

    ctx.beginPath();
    ctx.arc(this.posX, this.posY, this.size, 0, 2*Math.PI);
    ctx.fill();
  }

}
