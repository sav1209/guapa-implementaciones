document.addEventListener("DOMContentLoaded", function () {
  var body = document.body;
  function $(s, r) { return (r || document).querySelector(s); }
  function $$(s, r) { return Array.prototype.slice.call((r || document).querySelectorAll(s)); }

  async function copiar(texto, btn) {
    try { await navigator.clipboard.writeText(texto); }
    catch (e) {
      var ta = document.createElement("textarea");
      ta.value = texto; document.body.appendChild(ta); ta.select();
      document.execCommand("copy"); ta.remove();
    }
    if (btn) {
      var ant = btn.textContent;
      btn.textContent = "¡Copiado!";
      setTimeout(function () { btn.textContent = ant; }, 1500);
    }
  }

  if (window.hljs) $$("pre code").forEach(function (c) { hljs.highlightElement(c); });

  function crearCheck(clase, etiqueta) {
    var l = document.createElement("label");
    l.className = "sel " + clase;
    var i = document.createElement("input");
    i.type = "checkbox";
    i.setAttribute("aria-label", etiqueta);
    l.appendChild(i);
    return l;
  }

  function sync() {
    var n = $$(".paso.sel-on").length;
    $$(".seccion").forEach(function (s) {
      var c = $$(".paso.sel-on", s).length, t = $$(".paso", s).length;
      s.classList.toggle("tiene-sel", c > 0);
      var ch = $(".sel-sec input", s);
      if (ch) ch.checked = t > 0 && c === t;
    });
    $$(".paso").forEach(function (p) { $(".sel-paso input", p).checked = p.classList.contains("sel-on"); });
    body.classList.toggle("hay-sel", n > 0);
    var cont = $("#contador");
    if (cont) cont.textContent = n ? n + " seleccionado(s)" : "";
  }

  $$(".paso").forEach(function (p) {
    var ch = crearCheck("sel-paso", "Seleccionar paso");
    p.insertBefore(ch, p.firstChild);
    $("input", ch).onchange = function () { p.classList.toggle("sel-on", this.checked); sync(); };
    var code = $("pre.codigo code", p);
    if (code) {
      var b = document.createElement("button");
      b.type = "button"; b.className = "copiar"; b.textContent = "Copiar";
      b.onclick = function () { copiar(code.textContent, b); };
      $("pre.codigo", p).appendChild(b);
    }
  });

  $$(".seccion").forEach(function (s) {
    var h2 = $("h2", s);
    var ch = crearCheck("sel-sec", "Seleccionar sección");
    h2.insertBefore(ch, h2.firstChild);
    $("input", ch).onchange = function () {
      var v = this.checked;
      $$(".paso", s).forEach(function (p) { p.classList.toggle("sel-on", v); });
      sync();
    };
  });

  function seleccionarTodo(v) {
    $$(".paso").forEach(function (p) { p.classList.toggle("sel-on", v); });
    sync();
  }

  function imprimir(todo) {
    if (todo && body.classList.contains("hay-sel")) {
      body.classList.remove("hay-sel");
      body.setAttribute("data-restaurar", "1");
    }
    window.print();
  }
  window.addEventListener("afterprint", function () {
    if (body.getAttribute("data-restaurar")) { body.removeAttribute("data-restaurar"); sync(); }
  });

  $("#btnImpSel").onclick = function () { imprimir(false); };
  $("#btnImpTodo").onclick = function () { imprimir(true); };
  $("#btnSelTodo").onclick = function () { seleccionarTodo(true); };
  $("#btnLimpiar").onclick = function () { seleccionarTodo(false); };
  $("#btnCopiarSel").onclick = function () {
    var partes = $$(".paso.sel-on pre.codigo code").map(function (c) { return c.textContent; });
    if (!partes.length) { alert("Selecciona al menos un bloque con código."); return; }
    copiar(partes.join("\n\n"), this);
  };
  $("#btnCpp").onclick = function () {
    var box = $("#cppCompleto");
    box.hidden = !box.hidden;
    this.textContent = box.hidden ? "Ver .cpp completo" : "Ocultar .cpp completo";
  };
  var cb = $("#copiarCpp");
  if (cb) cb.onclick = function () { copiar($("#cppCompleto code").textContent, cb); };
  $("#chkTexto").onchange = function () { body.classList.toggle("sin-texto", !this.checked); };

  sync();
});
