/*
 * Nombre: Prefix (sumas, máximo, mínimo, conteo y plantilla general)
 * Categoría: estructuras_de_datos
 * Descripción: Acumulados desde el inicio de un arreglo para responder
 *              consultas rápidamente.
 * Complejidad: construcción O(n) | consulta O(1) | memoria O(n)
 * Cuándo usarlo: muchas consultas sobre rangos y pocas o ninguna
 *                actualización.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* PREFIX
Nos sirven para convertir muchas consultas o cálculos sobre arreglos o strings en operaciones rápidas.
Se precomputa en O(n) siempre y cuando no haya actualizaciones de por medio, ya que cada
actualización es O(n) en el peor caso. Si se requieren muchas actualizaciones es mejor buscar otras técnicas o estructuras.

Un prefix contiene información acumulada desde el inicio de un arreglo y podemos consultarlo en O(1).
En este caso solo voy a hacer las implementaciones y hablar del prefix.
El concepto del suffix es idéntico, solo que partiendo desde el final hacia el inicio.

Les colocaré algunas de las implementaciones más útiles del prefix.
Muy importante recalcar que la construcción es O(n) y las consultas O(1).
*/

int main(){
    // Datos de ejemplo (en un problema real se leen de la entrada)
    vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6};
    int n = a.size();
    int i = 5, l = 2, r = 5, x = 1;

    {
    /* Prefix Sum
    Este prefix es un acumulado de sumas a lo largo del arreglo, nos ayuda a conocer la suma
    de los elementos en cierto rango.
    */
    // Establecemos nuestro prefix de tamaño n+1 para mayor comodidad en las consultas.
    // [AGREGADO] Usamos long long para evitar overflow al sumar muchos int.
    vector<ll> pref(n+1);
    // Inicializamos siempre en un elemento neutro.
    pref[0] = 0;
    // Recorremos el arreglo y calculamos la posición siguiente del prefix a partir de la actual.
    for(int k=0;k<n;k++){
        pref[k+1] = pref[k] + a[k];
    }
    // Esto nos da como resultado que cada posición i del arreglo pref
    // tiene el acumulado de todas las posiciones anteriores a i.

    // Quiero saber cuál es la suma de los elementos anteriores a i
    ll anteriores = pref[i];

    // Quiero saber cuál es la suma en el rango [l, r]
    ll rango = pref[r+1] - pref[l];
    // Usamos r+1 porque pref[r] solo acumula lo anterior a r, sin contar a r.
    // Usamos l porque restamos todo lo anterior a l, o sea lo que está fuera de mi rango.

    cout << "Suma antes de i: " << anteriores << "\n";   // 14
    cout << "Suma en [l,r]: " << rango << "\n";          // 19
    }

    {
    /* Prefix Minimum y Maximum
    Estos prefix nos ayudan a saber cuál es el elemento más grande (Maximum)
    o más pequeño (Minimum) hasta una posición.
    */
    // Se inicializa igual que el de sumas, pero con el neutro de cada operación.
    vector<int> prefMaxi(n+1), prefMini(n+1);
    prefMaxi[0] = INT_MIN;   // [CORREGIDO] antes era 0, incorrecto si hay negativos
    prefMini[0] = INT_MAX;
    // Recorremos el arreglo y guardamos el máximo o el mínimo según lo que nos pidan.
    for(int k=0;k<n;k++){
        prefMaxi[k+1] = max(prefMaxi[k], a[k]);
        prefMini[k+1] = min(prefMini[k], a[k]);
    }
    // Quiero saber cuál es el elemento más grande que hay antes de la posición i
    int mayor = prefMaxi[i];
    // Quiero saber cuál es el elemento más pequeño antes de la posición i
    int menor = prefMini[i];

    // [AGREGADO] Ojo: con min/max NO se puede restar prefijos para un rango [l, r]
    // (no son operaciones invertibles). Para eso: Sparse Table o Segment Tree.

    cout << "Mayor antes de i: " << mayor << "\n";       // 5
    cout << "Menor antes de i: " << menor << "\n";       // 1
    }

    {
    /* Prefix Count
    Este prefix nos ayuda a saber cuántas veces aparece un elemento x antes de una posición o en un rango.
    */
    // Mismo proceso de inicialización
    vector<int> prefCount(n+1);
    prefCount[0] = 0;
    // Recorremos el arreglo y sumamos uno cada vez que encontremos el valor x
    for(int k=0;k<n;k++){
        prefCount[k+1] = prefCount[k] + (a[k] == x);
    }
    // Quiero saber cuántas veces aparece x antes de i
    int veces = prefCount[i];
    // Cuántas veces aparece x en el rango [l, r]
    int veces_rango = prefCount[r+1] - prefCount[l];

    cout << "Veces x antes de i: " << veces << "\n";     // 2
    cout << "Veces x en [l,r]: " << veces_rango << "\n"; // 1
    }

    {
    /* PREFIX GENERAL
    En resumen, podemos quedarnos con una plantilla y sustituir "combinar" por la operación que necesitemos.
    Los usos más comunes son:
      +    suma
      min  mínimo
      max  máximo
      ^    XOR
    */
    // [AGREGADO] Ejemplo concreto con XOR (neutro = 0).
    auto combinar = [](ll acumulado, int valor){ return acumulado ^ valor; };

    vector<ll> pref(n+1);
    pref[0] = 0;   // Casi siempre es el neutro de la operación

    for(int k=0;k<n;k++){
        pref[k+1] = combinar(pref[k], a[k]);
    }
    // Consultas
    ll antes = pref[i];   // lo que está antes de i
    // Lo que está entre l y r. [AGREGADO] Solo funciona si la operación es invertible
    // (suma con resta, XOR con XOR, conteo con resta). Con min/max no aplica.
    ll entre = pref[r+1] ^ pref[l];

    cout << "XOR antes de i: " << antes << "\n";         // 3^1^4^1^5 = 2
    cout << "XOR en [l,r]: " << entre << "\n";           // 9
    }
    return 0;
}
