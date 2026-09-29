(function () {
  'use strict';

  function $(s, c) { return (c || document).querySelector(s); }
  function $$(s, c) { return Array.prototype.slice.call((c || document).querySelectorAll(s)); }

  /* ---------- Avisos ---------- */
  var toastTimer;
  function toast(msg) {
    var t = $('.toast');
    if (!t) { t = document.createElement('div'); t.className = 'toast'; document.body.appendChild(t); }
    t.textContent = msg;
    t.style.display = 'block';
    clearTimeout(toastTimer);
    toastTimer = setTimeout(function () { t.style.display = 'none'; }, 2000);
  }

  /* ---------- Copiar al portapapeles ---------- */
  function copiar(texto, btn) {
    function ok() {
      if (btn) {
        var previo = btn.textContent;
        btn.textContent = '¡Copiado!';
        setTimeout(function () { btn.textContent = previo; }, 1500);
      } else {
        toast('Código copiado');
      }
    }
    function respaldo() {
      var ta = document.createElement('textarea');
      ta.value = texto;
      ta.style.position = 'fixed';
      ta.style.opacity = '0';
      document.body.appendChild(ta);
      ta.select();
      try { document.execCommand('copy'); ok(); } catch (e) { toast('No se pudo copiar'); }
      document.body.removeChild(ta);
    }
    if (navigator.clipboard && window.isSecureContext) {
      navigator.clipboard.writeText(texto).then(ok, respaldo);
    } else {
      respaldo();
    }
  }

  function textoDe(pre) {
    var code = $('code', pre);
    return (code || pre).textContent.replace(/\n$/, '');
  }

  /* ---------- Modos de vista ---------- */
  function fijarModo(modo) {
    document.body.classList.remove('modo-explicacion', 'modo-codigo', 'modo-ambos');
    document.body.classList.add('modo-' + modo);
  }

  /* ---------- Selección ---------- */
  function crearCheck() {
    var lbl = document.createElement('label');
    lbl.className = 'sel-lbl';
    lbl.title = 'Seleccionar';
    lbl.innerHTML = '<input type="checkbox" aria-label="Seleccionar">';
    return lbl;
  }

  function pasosSeleccionados() { return $$('.paso.sel'); }

  function actualizarSeccion(sec) {
    var pasos = $$('.paso', sec);
    var n = pasos.filter(function (p) { return p.classList.contains('sel'); }).length;
    sec.classList.toggle('vacia', n === 0);
    var chk = $('h2 input', sec);
    if (chk) chk.checked = pasos.length > 0 && n === pasos.length;
  }

  function marcarPaso(paso, valor) {
    paso.classList.toggle('sel', valor);
    var chk = $('.sel-lbl input', paso);
    if (chk) chk.checked = valor;
  }

  function marcarTodo(valor) {
    $$('.paso').forEach(function (p) { marcarPaso(p, valor); });
    $$('.seccion').forEach(actualizarSeccion);
  }

  /* ---------- Vista del .cpp completo ---------- */
  function alternarCpp() {
    var vista = $('#vista-cpp');
    var contenido = $('#contenido');
    if (!vista) {
      var fuente = $('#cpp-fuente');
      if (!fuente) return;
      vista = document.createElement('section');
      vista.id = 'vista-cpp';
      vista.innerHTML =
        '<p class="vista-cpp-cab">Archivo original con todos sus comentarios.</p>' +
        '<pre class="codigo"><button class="btn-copiar" type="button">Copiar</button><code class="language-cpp"></code></pre>';
      var code = $('code', vista);
      code.textContent = fuente.textContent.replace(/^\n/, '');
      if (window.hljs) window.hljs.highlightElement(code);
      $('.btn-copiar', vista).addEventListener('click', function (e) { copiar(code.textContent, e.currentTarget); });
      contenido.parentNode.insertBefore(vista, contenido.nextSibling);
    }
    var mostrar = !vista.classList.contains('visible');
    vista.classList.toggle('visible', mostrar);
    contenido.style.display = mostrar ? 'none' : '';
    var b = $('[data-a="ver-cpp"]');
    if (b) b.textContent = mostrar ? 'Volver a la vista por bloques' : 'Ver .cpp completo';
  }

  /* ---------- Inicio ---------- */
  function iniciar() {
    if (window.hljs) window.hljs.highlightAll();
    fijarModo('ambos');

    // Casillas de selección
    $$('.paso').forEach(function (p) {
      var lbl = crearCheck();
      p.insertBefore(lbl, p.firstChild);
      $('input', lbl).addEventListener('change', function (e) {
        marcarPaso(p, e.target.checked);
        actualizarSeccion(p.closest('.seccion'));
      });
    });
    $$('.seccion').forEach(function (sec) {
      var h2 = $('h2', sec);
      if (!h2) return;
      var lbl = crearCheck();
      lbl.title = 'Seleccionar toda la sección';
      h2.insertBefore(lbl, h2.firstChild);
      $('input', lbl).addEventListener('change', function (e) {
        $$('.paso', sec).forEach(function (p) { marcarPaso(p, e.target.checked); });
        actualizarSeccion(sec);
      });
      sec.classList.add('vacia');
    });

    // Botones de copiar en cada bloque de código
    $$('#contenido pre.codigo').forEach(function (pre) {
      var b = document.createElement('button');
      b.type = 'button';
      b.className = 'btn-copiar';
      b.textContent = 'Copiar';
      b.addEventListener('click', function () { copiar(textoDe(pre), b); });
      pre.insertBefore(b, pre.firstChild);
    });

    // Barra de acciones
    var barra = $('#barra-acciones');
    if (barra) {
      barra.className = 'barra';
      barra.innerHTML =
        '<span class="modos" role="radiogroup" aria-label="Modo de vista">' +
          '<label><input type="radio" name="modo-vista" value="explicacion"> Solo explicación</label>' +
          '<label><input type="radio" name="modo-vista" value="codigo"> Solo código</label>' +
          '<label><input type="radio" name="modo-vista" value="ambos" checked> Ambos</label>' +
        '</span>' +
        '<button type="button" data-a="imp-sel">Imprimir selección</button>' +
        '<button type="button" data-a="imp-todo">Imprimir todo</button>' +
        '<button type="button" data-a="sel-todo">Seleccionar todo</button>' +
        '<button type="button" data-a="limpiar">Limpiar selección</button>' +
        '<button type="button" data-a="copiar-sel">Copiar código de lo seleccionado</button>' +
        '<button type="button" data-a="ver-cpp">Ver .cpp completo</button>';

      barra.addEventListener('click', function (e) {
        var a = e.target.getAttribute && e.target.getAttribute('data-a');
        if (!a) return;
        if (a === 'imp-sel') {
          if (!pasosSeleccionados().length) { toast('No hay nada seleccionado'); return; }
          document.body.classList.add('solo-sel');
          window.print();
        } else if (a === 'imp-todo') {
          document.body.classList.remove('solo-sel');
          window.print();
        } else if (a === 'sel-todo') {
          marcarTodo(true);
        } else if (a === 'limpiar') {
          marcarTodo(false);
        } else if (a === 'copiar-sel') {
          var partes = [];
          pasosSeleccionados().forEach(function (p) {
            $$('pre.codigo', p).forEach(function (pre) { partes.push(textoDe(pre)); });
          });
          if (!partes.length) { toast('No hay código seleccionado'); return; }
          copiar(partes.join('\n'), null);
        } else if (a === 'ver-cpp') {
          alternarCpp();
        }
      });

      barra.addEventListener('change', function (e) {
        if (e.target.name === 'modo-vista') fijarModo(e.target.value);
      });
    }

    window.addEventListener('afterprint', function () {
      document.body.classList.remove('solo-sel');
    });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', iniciar);
  } else {
    iniciar();
  }
})();
