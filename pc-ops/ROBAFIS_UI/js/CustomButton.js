class CustomButton {
  constructor(ctxGamepad, pos1, pos2, pos3, pos4, color) {
    this.ctxGamepad   = ctxGamepad;
    this.pos1 = pos1;
    this.pos2 = pos2;
    this.pos3 = pos3;
    this.pos4 = pos4;
    this.color = color;
  }

  draw() {
    ctxGamepad.fillStyle = this.color; // L1
    ctxGamepad.beginPath();
    ctxGamepad.moveTo(this.pos1[0], this.pos1[1]);
    ctxGamepad.lineTo(this.pos2[0], this.pos2[1]);
    ctxGamepad.lineTo(this.pos3[0], this.pos3[1]);
    ctxGamepad.lineTo(this.pos4[0], this.pos4[1]);
    ctxGamepad.closePath();
    ctxGamepad.fill();
  }

}
