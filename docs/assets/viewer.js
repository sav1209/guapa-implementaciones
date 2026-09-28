document.addEventListener("DOMContentLoaded", function () {
  var body = document.body;
  var pasos = Array.prototype.slice.call(document.querySelectorAll(".paso"));
  var secs = Array.prototype.slice.call(document.querySelectorAll(".seccion"));
  var contador = document.getElementById("contador");

  if (window.hljs) {
    Array.prototype.forEach.call(document.querySelectorAll("pre code"), function (c) {
      hljs.highlightElement(c);
    });
  }

  function respaldo(t) {
    var ta = document.createElement("textarea");
    ta.value = t;
    document.body.appendChild(ta);
    ta.select();
    document.execCommand("copy");
    ta.remove();
  }
  function copiar(texto, btn) {
    var fin = function () {
      if (!btn) return;
      var old = btn.textContent;
      btn.textContent = "¡Copiado!";
      setTimeout(function () { btn.textContent = old; }, 1500);
    };
    if (navigator.clipboard && navigator.clipboard.writeText) {
      navigator.clipboard.writeText(texto).then(fin, function () { respaldo(texto); fin(); });
    } else { respaldo(texto); fin(); }
  }

  // Botón "Copiar" en cada bloque de código
  Array.prototype.forEach.call(document.querySelectorAll("pre.codigo"), function (pre) {
    var b = document.createElement("button");
    b.type = "button";
    b.className = "copiar";
    b.textContent = "Copiar";
    b.onclick = function () { copiar(pre.querySelector("code").textContent, b); };
    pre.appendChild(b);
  });

  function seleccionados() {
    return pasos.filter(function (p) { return p.classList.contains("sel"); });
  }
  function actualizarContador() {
    if (!contador) return;
    var n = seleccionados().length;
    contador.textContent = n ? n + " seleccionado" + (n === 1 ? "" : "s") : "";
  }
  function sincronizarSeccion(s) {
    var ps = s.querySelectorAll(".paso");
    s._cb.checked = ps.length > 0 && s.querySelectorAll(".paso.sel").length === ps.length;
  }

  // Casilla de cada paso
  pasos.forEach(function (p) {
    var l = document.createElement("label");
    l.className = "selbox";
    var c = document.createElement("input");
    c.type = "checkbox";
    c.onchange = function () {
      p.classList.toggle("sel", c.checked);
      sincronizarSeccion(p.closest(".seccion"));
      actualizarContador();
    };
    l.appendChild(c);
    l.appendChild(document.createTextNode(" Seleccionar"));
    p.insertBefore(l, p.firstChild);
    p._cb = c;
  });

  // Casilla de cada sección
  secs.forEach(function (s) {
    var h2 = s.querySelector("h2");
    var l = document.createElement("label");
    l.className = "selbox";
    var c = document.createElement("input");
    c.type = "checkbox";
    c.onchange = function () {
      Array.prototype.forEach.call(s.querySelectorAll(".paso"), function (p) {
        p._cb.checked = c.checked;
        p.classList.toggle("sel", c.checked);
      });
      actualizarContador();
    };
    l.appendChild(c);
    l.appendChild(document.createTextNode(" Sección"));
    s.insertBefore(l, h2);
    s._cb = c;
  });

  function marcarTodo(v) {
    pasos.forEach(function (p) { p._cb.checked = v; p.classList.toggle("sel", v); });
    secs.forEach(function (s) { s._cb.checked = v; });
    actualizarContador();
  }

  function imprimir(soloSeleccion) {
    if (soloSeleccion) {
      if (!seleccionados().length) {
        alert("Primero selecciona al menos un paso o sección.");
        return;
      }
      body.classList.add("solo-sel");
      secs.forEach(function (s) {
        s.classList.toggle("vacia", !s.querySelector(".paso.sel"));
      });
    } else {
      body.classList.remove("solo-sel");
    }
    window.print();
    body.classList.remove("solo-sel");
  }

  function on(id, fn) {
    var e = document.getElementById(id);
    if (e) e.onclick = fn;
  }

  on("btnImpSel", function () { imprimir(true); });
  on("btnImpTodo", function () { imprimir(false); });
  on("btnSelTodo", function () { marcarTodo(true); });
  on("btnLimpiar", function () { marcarTodo(false); });

  on("btnCopiarSel", function () {
    var lista = seleccionados();
    if (!lista.length) { alert("Primero selecciona al menos un paso o sección."); return; }
    var partes = [];
    lista.forEach(function (p) {
      var c = p.querySelector("pre.codigo code");
      if (c) partes.push(c.textContent.replace(/\s+$/, ""));
    });
    if (!partes.length) { alert("Lo seleccionado no contiene código."); return; }
    copiar(partes.join("\n\n") + "\n", document.getElementById("btnCopiarSel"));
  });

  on("btnCpp", function () {
    var cpp = document.getElementById("cppCompleto");
    if (!cpp) return;
    var ver = cpp.hasAttribute("hidden");
    if (ver) cpp.removeAttribute("hidden"); else cpp.setAttribute("hidden", "");
    body.classList.toggle("ver-cpp", ver);
    this.textContent = ver ? "Ver bloques" : "Ver .cpp completo";
  });

  on("copiarCpp", function () {
    var c = document.querySelector("#cppCompleto pre code");
    if (c) copiar(c.textContent, this);
  });

  var chk = document.getElementById("chkTexto");
  if (chk) {
    chk.onchange = function () { body.classList.toggle("sin-texto", !chk.checked); };
  }
});
