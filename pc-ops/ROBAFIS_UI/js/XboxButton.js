class XboxButton {
  constructor(ctx, color) {
    this.ctx   = ctx;
    this.color = color;
  }

  draw() {
    ctx.translate(-150, -150);
    ctx.rotate(340 * Math.PI / 180);

    ctx.fillStyle = this.color;
    ctx.beginPath();
    ctx.arc(208.5, 299.5, 16, 0, 220 * Math.PI / 180);
    ctx.fill();

    ctx.rotate(20 * Math.PI / 180);
    ctx.translate(150, 150);
  }

  erase() {
    ctx.translate(-150, -150);
    ctx.rotate(340 * Math.PI / 180);

    ctx.fillStyle = "#AFB6BB";
    ctx.beginPath();
    ctx.arc(208.5, 299.5, 16, 0, 220 * Math.PI / 180);
    ctx.fill();

    ctx.rotate(20 * Math.PI / 180);
    ctx.translate(150, 150);
  }

}
