class XboxButton {
  constructor(ctxGamepad, color) {
    this.ctxGamepad   = ctxGamepad;
    this.color = color;
  }

  draw() {
    ctxGamepad.translate(-150, -150);
    ctxGamepad.rotate(340 * Math.PI / 180);

    ctxGamepad.fillStyle = this.color;
    ctxGamepad.beginPath();
    ctxGamepad.arc(208.5, 299.5, 16, 0, 220 * Math.PI / 180);
    ctxGamepad.fill();

    ctxGamepad.rotate(20 * Math.PI / 180);
    ctxGamepad.translate(150, 150);
  }

  erase() {
    ctxGamepad.translate(-150, -150);
    ctxGamepad.rotate(340 * Math.PI / 180);

    ctxGamepad.fillStyle = "#AFB6BB";
    ctxGamepad.beginPath();
    ctxGamepad.arc(208.5, 299.5, 16, 0, 220 * Math.PI / 180);
    ctxGamepad.fill();

    ctxGamepad.rotate(20 * Math.PI / 180);
    ctxGamepad.translate(150, 150);
  }

}
