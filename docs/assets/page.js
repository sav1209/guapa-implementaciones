document.addEventListener("DOMContentLoaded", function () {
  var code = document.querySelector("pre code");
  var btn = document.getElementById("copy");
  if (window.hljs && code) hljs.highlightElement(code);
  if (!btn || !code) return;
  btn.onclick = async function () {
    var t = code.textContent;
    try { await navigator.clipboard.writeText(t); }
    catch (e) {
      var ta = document.createElement("textarea");
      ta.value = t; document.body.appendChild(ta); ta.select();
      document.execCommand("copy"); ta.remove();
    }
    btn.textContent = "¡Copiado!";
    setTimeout(function () { btn.textContent = "Copiar"; }, 1500);
  };
});
