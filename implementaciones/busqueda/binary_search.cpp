/*
 * Nombre: Binary Search (búsqueda binaria)
 * Categoría: busqueda
 * Descripción: Encontrar una posición o un valor dentro de un espacio ordenado
 *              descartando la mitad de las posibilidades en cada paso.
 *              Dos usos: sobre un arreglo y sobre una respuesta.
 * Complejidad: arreglo O(log n) por búsqueda | sobre la respuesta
 *              O(log(rango) * costo de puede()) | memoria O(1)
 * Cuándo usarlo: arreglo ordenado, o cuando una condición cambia una sola vez
 *                (V...V F...F o F...F V...V) y se quiere minimizar/maximizar.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*BINARY SEARCH
La idea principal de la búsqueda binaria es encontrar una posición o un valor dentro de un espacio ordenado.
En lugar de revisar elemento por elemento, descartamos la mitad de las posibilidades en cada paso.
Al dividir a la mitad en cada iteración nuestra complejidad se vuelve O(log n) por cada búsqueda.
Existen 2 usos principales de la binaria.
1.- Sobre un arreglo
2.- Sobre una respuesta
*/

/*Binary sobre un arreglo
Sea a un arreglo de enteros ordenado.
*/

/*Buscar si existe un valor exacto*/
int binarySearch(vector<int>& a,int x){
    // Establecemos los límites de la binaria desde 0 hasta n-1 que es el último índice de nuestro arreglo.
    int l=0,r=(int)a.size()-1;
    while(l<=r){
        // m va a ser quien divida a la mitad y nos ayude a descartar lo que no sirva.
        //  Usamos l+(r-l)/2 en lugar de (l+r)/2 para evitar overflow con índices grandes.
        int m=l+(r-l)/2;
        // Encontramos el valor y regresamos la posición.
        if(a[m]==x)return m;
        // Si a[m] < x descartamos la mitad de la izquierda ya que sabemos que x debe estar al menos una posición después de esa m.
        // Si no descartamos la de la derecha porque sabemos que x debe estar al menos una posición antes que m.
        if(a[m]<x)
            l=m+1;
        else
            r=m-1;
    }
    // Si terminamos la búsqueda y no lo encontramos regresamos -1 para indicar que no existe en el arreglo.
    return -1;
}

/*Encontrar la primera posición >=x o >x
El lower bound y upper bound son funciones que utilizan una búsqueda binaria.
Podemos obtenerlas con:
int posLower = lower_bound(a.begin(),a.end(),x)-a.begin();
int posUpper = upper_bound(a.begin(),a.end(),x)-a.begin();
o programar la binaria: tomamos como base lowerBound, pero podemos cambiar el >= por > para obtener upperBound.
*/
int lowerBound(vector<int>& a,int x){
    // Establecemos los límites de la binaria desde 0 hasta n, ya que si está en el final significa que no hay dentro del arreglo un elemento >=x.
    int l=0,r=a.size();
    while(l<r){   // [CORREGIDO] antes era l<=r: con r=m se cicla y lee fuera del arreglo
        // m va a ser quien divida a la mitad y nos ayude a descartar lo que no sirva.
        int m=l+(r-l)/2;
        // Si a[m]>=x reducimos r, porque ya nos aseguramos de que a[m] es al menos mayor o igual a x.
        // Si es menor avanzamos 1 porque x debe estar al menos una posición después.
        if(a[m]>=x)// Solo cambiamos >= por > para el upper, lo demás es idéntico
            r=m;
        else
            l=m+1;
    }
    // Regresamos la posición en donde se cumplió.
    return l;
}

int main(){
    //  Ejemplo de uso
    vector<int> a = {1, 3, 3, 5, 7, 9, 11};
    cout << binarySearch(a, 7) << "\n";                              // 4
    cout << binarySearch(a, 4) << "\n";                              // -1
    cout << lowerBound(a, 3) << "\n";                                // 1
    cout << lowerBound(a, 4) << "\n";                                // 3
    cout << lowerBound(a, 12) << "\n";                               // 7 (no hay elemento >= 12)
    cout << upper_bound(a.begin(), a.end(), 3) - a.begin() << "\n";  // 3

    /*Binary sobre una respuesta
    Es muy importante que podamos hacer una función de la forma:
    -V=verdadero
    -F=falso
    V V V V V F F F F F
    o también:
    F F F F F V V V V V
    Donde al inicio sea siempre verdadero y después siempre falso o primero siempre falso y después siempre verdadero.
    Con la binaria podemos buscar 2 cosas, el último valor antes del cambio o el primero después del cambio.
    Esto nos puede ayudar a maximizar o minimizar las soluciones.
    */

    {
    /*Minimizar
    Dada una función de la forma
    F F F F V V V V
    imprime el mínimo x que cumple con algo (el primer verdadero de la función).
    */
    //  Ejemplo: el menor m tal que m*m >= 50 (respuesta: 8).
    auto puede = [](ll m){ return m*m >= 50; };
    ll minimo=0, maximo=100;
    // Establecemos los límites de la binaria, generalmente va de 0 a un valor muy grande como 1e18
    // que pasa muy bien en límites de 1 segundo, pero si de antemano se conoce entre qué valores puede estar la solución así se establecen el mínimo y el máximo.
    //  Con límites de hasta 1e18 usa long long (ll); int no alcanza.
    ll l=minimo, r=maximo;
    while(l<r){
        // m es igual al piso de la división
        ll m = l + (r-l)/2;
        // La función puede se ajusta al problema, nos devuelve un bool si es verdadero o falso para la m actual
        if(puede(m)){
            // Reducimos la r y sabemos que puede ser esa la solución o estar antes.
            r=m;
        }
        // Si es falso, avanzamos 1 ya que sabemos que ese es falso y necesitamos el primer verdadero por lo que al menos está uno después.
        else l=m+1;
    }
    //  Ojo: si ningún valor cumple, l termina valiendo maximo. Verifica puede(l) al final si eso puede pasar.
    // Por último imprimimos la l que nos da el primer valor que cumple con algo.
    cout<<l<<endl;   // 8
    }

    {
    /*Maximizar
    Dada una función de la forma
    V V V V V F F F F F
    imprime el máximo x que cumple con algo (el último verdadero de la función).
    */
    //  Ejemplo: el mayor m tal que m*m <= 50 (respuesta: 7).
    auto puede = [](ll m){ return m*m <= 50; };
    ll minimo=0, maximo=100;
    // Establecemos los límites de la binaria, generalmente va de 0 a un valor muy grande como 1e18.
    // Si de antemano se conoce entre qué valores puede estar la solución así se establecen el mínimo y el máximo.
    ll l=minimo, r=maximo;
    while(l<r){
        // m es igual al techo de la división
        ll m = l + (r-l+1)/2;
        // La función puede se ajusta al problema, nos devuelve un bool si es verdadero o falso para la m actual
        if(puede(m)){
            // Aumentamos la l y sabemos que puede ser esa la solución o estar después.
            l=m;   // [CORREGIDO] antes era r=m
        }
        // Si es falso sabemos que por lo menos tiene que estar una antes por lo que reducimos r y restamos 1.
        else r=m-1;   // [CORREGIDO] antes era l=m+1 (y faltaba el ;)
    }
    //  Ojo: si ningún valor cumple, l termina valiendo minimo. Verifica puede(l) al final si eso puede pasar.
    // Por último imprimimos la l que nos da el último valor que cumple con algo.
    cout<<l<<endl;   // 7
    }

    /*La diferencia entre minimizar y maximizar es la división piso o techo para evitar un loop infinito en el while.
     Al minimizar hacemos r=m: con piso m<r siempre, así el rango se achica. Al maximizar hacemos l=m: con techo m>l siempre.
    */
    return 0;
}
