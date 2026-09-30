# Implementaciones GUAPA

Repositorio dedicado para compartir implementaciones de problemas básicos y soluciones de contests a miembros del Grupo Universitario de Algoritmia y Programación Avanzada (GUAPA).

## Consultar desde el navegador
Todo el material se puede leer (con código resaltado, botón de copiar y opción de imprimir) en el sitio web del club, sin necesidad de saber usar GitHub: **Settings → Pages** del repositorio muestra la URL.

## Implementaciones
Algoritmos y estructuras listos para consultar (código en C++ por categoría, en `implementaciones/`).

### Búsqueda
- [Binary Search](implementaciones/busqueda/binary_search.cpp): búsqueda binaria sobre un arreglo (valor exacto, lower y upper bound) y sobre la respuesta (minimizar y maximizar).
### Estructuras de datos
- [Prefix Sums](implementaciones/estructuras_de_datos/prefix_sums.cpp): acumulados para consultas en O(1) (suma, mínimo, máximo, conteo y plantilla general con XOR).

## Upsolving
Soluciones comentadas de nuestros contests semanales (en `soluciones/`).

### Contest II - 2027-1
[Ver contest](https://codeforces.com/group/P35WkNZDR8/contest/713751)
- [A. Black and White Stripe](soluciones/contest_ii_2027_1/A_black_and_white_stripe.cpp): sliding window y prefix de frecuencias para hallar la mínima cantidad de 'W' en una ventana de tamaño k.
- [B. Pashmak and Flowers](soluciones/contest_ii_2027_1/B_pashmak_and_flowers.cpp): conteo de mínimos y máximos; la máxima diferencia es maximo-minimo y las parejas son cantm·cantx (o n(n-1)/2 si todos son iguales).
- [C. Interesting drink](soluciones/contest_ii_2027_1/C_interesting_drink.cpp): ordenar los precios y usar búsqueda binaria para contar en cuántas tiendas alcanza con m_i monedas.
- [D. Badge](soluciones/contest_ii_2027_1/D_badge.cpp): para cada estudiante, seguir la cadena de culpas con un arreglo de visitados hasta el primero que se repite (O(n²)).

## Estructura
- `implementaciones/`: código en C++ por categoría (grafos, strings, estructuras_de_datos, busqueda…).
- `soluciones/`: soluciones de contests (`contest_01/`, `contest_02/`…). En el sitio se muestran como **Upsolving**.
- `docs/`: sitio estático (GitHub Pages).

Los archivos usan `snake_case` sin acentos ni espacios (ej. `binary_search.cpp`).
