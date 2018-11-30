class SquareButton {
  constructor(ctx, x, y, w, h, radius, color) {
    this.ctx = ctx;
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.radius = radius;
    this.color = color;
  }

  draw() {
    var r = this.x + this.w;
    var b = this.y + this.h;
    ctx.fillStyle = this.color
    ctx.beginPath();
    ctx.moveTo(this.x + this.radius, this.y);
    ctx.lineTo(r - this.radius, this.y);
    ctx.quadraticCurveTo(r, this.y, r, this.y + this.radius);
    ctx.lineTo(r, this.y + this.h - this.radius);
    ctx.quadraticCurveTo(r, b, r - this.radius, b);
    ctx.lineTo(this.x + this.radius, b);
    ctx.quadraticCurveTo(this.x, b, this.x, b - this.radius);
    ctx.lineTo(this.x, this.y + this.radius);
    ctx.quadraticCurveTo(this.x, this.y, this.x + this.radius, this.y);
    ctx.fill();
  }

  erase() {
    var r = this.x + this.w;
    var b = this.y + this.h;
    ctx.fillStyle = "#546A79"
    ctx.beginPath();
    ctx.moveTo(this.x + this.radius, this.y);
    ctx.lineTo(r - this.radius, this.y);
    ctx.quadraticCurveTo(r, this.y, r, this.y + this.radius);
    ctx.lineTo(r, this.y + this.h - this.radius);
    ctx.quadraticCurveTo(r, b, r - this.radius, b);
    ctx.lineTo(this.x + this.radius, b);
    ctx.quadraticCurveTo(this.x, b, this.x, b - this.radius);
    ctx.lineTo(this.x, this.y + this.radius);
    ctx.quadraticCurveTo(this.x, this.y, this.x + this.radius, this.y);
    ctx.fill();
  }
}
