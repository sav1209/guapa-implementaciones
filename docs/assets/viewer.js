document.addEventListener("DOMContentLoaded", function () {
  var body = document.body;
  var pasos = Array.prototype.slice.call(document.querySelectorAll(".paso"));
  var secs = Array.prototype.slice.call(document.querySelectorAll(".seccion"));

  if (window.hljs) {
    Array.prototype.forEach.call(document.querySelectorAll("pre code"), function (c) { hljs.highlightElement(c); });
  }

  function copiar(texto, btn) {
    var fin = function () {
      var old = btn.textContent;
      btn.textContent = "¡Copiado!";
      setTimeout(function () { btn.textContent = old; }, 1500);
    };
    if (navigator.clipboard && navigator.clipboard.writeText) {
      navigator.clipboard.writeText(texto).then(fin, function () { respaldo(texto); fin(); });
    } else { respaldo(texto); fin(); }
  }
  function respaldo(t) {
    var ta = document.createElement("textarea");
    ta.value = t; document.body.appendChild(ta); ta.select();
    document.execCommand("copy"); ta.remove();
  }

  // Botón "Copiar" en cada bloque de código
  Array.prototype.forEach.call(document.querySelectorAll("pre.codigo"), function (pre) {
    var b = document.createElement("button");
    b.type = "button"; b.className = "copiar"; b.textContent = "Copiar";
    b.onclick = function () { copiar(pre.querySelector("code").textContent, b); };
    pre.appendChild(b);
  });

  // Casillas de selección
  function crearCasilla(el, alCambiar) {
    var l = document.createElement("label"); l.className = "selbox";
    var c = document.createElement("input"); c.type = "checkbox";
    c.onchange = function () { alCambiar(c.checked); };
    l.appendChild(c); l.appendChild(document.createTextNode(" Seleccionar"));
    el.insertBefore(l, el.firstChild);
    return c;
  }
  function sincronizarSeccion(s) {
    var ps = s.querySelectorAll(".paso");
    var todos = ps.length > 0 && s.querySelectorAll(".paso.sel").length === ps.length;
    s._cb.checked = todos;
  }
  pasos.forEach(function (p) {
    p._cb = crearCasilla(p, function (v) {
      p.classList.toggle("sel", v);
      sincronizarSeccion(p.closest(".seccion"));
    });
  });
  secs.forEach(function (s) {
    var h2 = s.querySelector("h2");
    var l = document.createElement("label"); l.className = "selbox";
    var c = document.createElement("input"); c.type = "checkbox";
    c.onchange = function () {
      Array.prototype.forEach.call(s.querySelectorAll(".paso"), function (p) {
        p._cb.checked = c.checked; p.classList.toggle("sel", c.checked);
      });
    };
    l.appendChild(c); l.appendChild(document.createTextNode(" Sección"));
    h2.parentNode.insertBefore(l, h2);
    s._cb = c;
  });

  function seleccionados() { return pasos.filter(function (p) { return p.classList.contains("sel"); }); }
  function marcarTodo(v) {
    pasos.forEach(function (p) { p._cb.checked = v; p.classList.toggle("sel", v); });
    secs.forEach(function (s) { s._cb.checked = v; });
  }

  function imprimir(soloSeleccion) {
    if (soloSeleccion) {
      if (!seleccionados().length) { alert("Primero selecciona al menos un paso o sección."); return; }
      body.classList.add("solo-sel");
      secs.forEach(function (s) { s.classList.toggle("vacia", !s.querySelector(".paso.sel")); });
    } else {
      body.classList.remove("solo-sel");
    }
    window.print();
    body.classList.remove("solo-sel");
  }

  function on(id, fn) { var e = document.getElementById(id); if (e) e.onclick = fn; }
  on("imp-sel", function () { imprimir(true); });
  on("imp-todo", function () { imprimir(false); });
  on("sel-todo", function () { marcarTodo(true); });
  on("sel-limpiar", function () { marcarTodo(false); });
  on("copiar-sel", function () {
    var lista = seleccionados();
    if (!lista.length) { alert("Primero selecciona al menos un paso o sección."); return; }
    var partes = [];
    lista.forEach(function (p) {
      var c = p.querySelector("pre.codigo code");
      if (c) partes.push(c.textContent.replace(/\s+$/, ""));
    });
    if (!partes.length) { alert("Lo seleccionado no contiene código."); return; }
    copiar(partes.join("\n\n") + "\n", document.getElementById("copiar-sel"));
  });
  on("ver-cpp", function () {
    var v = body.classList.toggle("ver-cpp");
    this.textContent = v ? "Ver bloques" : "Ver .cpp completo";
  });
  on("toggle-texto", function () {
    var v = body.classList.toggle("sin-texto");
    this.textContent = v ? "Mostrar texto" : "Ocultar texto";
  });
  on("copiar-cpp", function () {
    copiar(document.querySelector("#cpp-src code").textContent, this);
  });
});
