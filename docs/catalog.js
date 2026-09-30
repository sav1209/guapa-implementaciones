const CATALOG = [
  { tipo: "implementacion", categoria: "busqueda", titulo: "Binary Search", descripcion: "Búsqueda binaria sobre un arreglo (valor exacto, lower y upper bound) y sobre la respuesta (minimizar y maximizar).", archivo: "implementaciones/binary_search.html", cpp: "implementaciones/busqueda/binary_search.cpp", tags: ["binary search", "búsqueda binaria", "lower_bound", "upper_bound", "minimizar", "maximizar", "O(log n)"] }
,  { tipo: "implementacion", categoria: "estructuras_de_datos", titulo: "Prefix Sums", descripcion: "Acumulados desde el inicio de un arreglo para responder consultas en O(1): suma, mínimo, máximo, conteo y una plantilla general (suma, min, max, XOR).", archivo: "implementaciones/prefix_sums.html", cpp: "implementaciones/estructuras_de_datos/prefix_sums.cpp", tags: ["prefix sum", "sumas prefijas", "acumulados", "rango", "xor", "prefix min", "prefix max", "prefix count", "suffix", "O(1)"] }
,,  {
    tipo: "solucion",
    contest: "Contest II - 2027-1",
    contestSlug: "contest_ii_2027_1",
    contestUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751",
    problema: "A",
    tituloProblema: "Black and White Stripe",
    problemaUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/A",
    descripcion: "Mínimo de cambios para tener un segmento de k letras 'B': mínima cantidad de 'W' en una ventana de tamaño k, con sliding window y con prefix de frecuencias.",
    archivo: "soluciones/contest_ii_2027_1/A_black_and_white_stripe.html",
    cpp: "soluciones/contest_ii_2027_1/A_black_and_white_stripe.cpp",
    tags: ["sliding window", "prefix sum", "strings", "ventana deslizante"]
  },
  ,  {
    tipo: "solucion",
    contest: "Contest II - 2027-1",
    contestSlug: "contest_ii_2027_1",
    contestUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751",
    problema: "B",
    tituloProblema: "Pashmak and Flowers",
    problemaUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/B",
    descripcion: "Máxima diferencia de belleza entre dos flores y de cuántas maneras se puede elegir una pareja con esa diferencia: contar mínimos y máximos, y combinaciones de 2 en n cuando todos son iguales.",
    archivo: "soluciones/contest_ii_2027_1/B_pashmak_and_flowers.html",
    cpp: "soluciones/contest_ii_2027_1/B_pashmak_and_flowers.cpp",
    tags: ["conteo", "combinatoria", "máximo y mínimo", "matemáticas"]
  },
    {
    tipo: "solucion",
    contest: "Contest II - 2027-1",
    contestSlug: "contest_ii_2027_1",
    contestUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751",
    problema: "C",
    tituloProblema: "Interesting drink",
    problemaUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/C",
    descripcion: "En cuántas tiendas se puede comprar una bebida con m_i monedas cada día: ordenar los precios y usar búsqueda binaria para encontrar la última tienda con precio <= m_i.",
    archivo: "soluciones/contest_ii_2027_1/C_interesting_drink.html",
    cpp: "soluciones/contest_ii_2027_1/C_interesting_drink.cpp",
    tags: ["binary search", "búsqueda binaria", "ordenamiento", "sorting"]
  },
    ,{
    tipo: "solucion",
    contest: "Contest II - 2027-1",
    contestSlug: "contest_ii_2027_1",
    contestUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751",
    problema: "D",
    tituloProblema: "Badge",
    problemaUrl: "https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/D",
    descripcion: "Para cada estudiante como punto de partida, encontrar el primero que se repite al seguir la cadena de culpas: simulación con un arreglo de visitados por cada inicio.",
    archivo: "soluciones/contest_ii_2027_1/D_badge.html",
    cpp: "soluciones/contest_ii_2027_1/D_badge.cpp",
    tags: ["simulación", "grafos", "ciclos", "visitados"]
  }
];
