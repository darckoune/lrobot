class CustomButton {
  constructor(ctx, pos1, pos2, pos3, pos4, color) {
    this.ctx   = ctx;
    this.pos1 = pos1;
    this.pos2 = pos2;
    this.pos3 = pos3;
    this.pos4 = pos4;
    this.color = color;
  }

  draw() {
    ctx.fillStyle = this.color; // L1
    ctx.beginPath();
    ctx.moveTo(this.pos1[0], this.pos1[1]);
    ctx.lineTo(this.pos2[0], this.pos2[1]);
    ctx.lineTo(this.pos3[0], this.pos3[1]);
    ctx.lineTo(this.pos4[0], this.pos4[1]);
    ctx.closePath();
    ctx.fill();
  }

}
