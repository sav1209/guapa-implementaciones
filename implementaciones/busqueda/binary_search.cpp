/*
 * Binary Search (Búsqueda binaria)
 * Categoría: busqueda
 * Descripción: Búsqueda binaria sobre un arreglo ordenado (valor exacto, lower_bound
 *              y upper_bound) y sobre la respuesta (minimizar y maximizar).
 * Complejidad: O(log n) por búsqueda sobre un arreglo.
 *              O(log(rango) * costo de puede) sobre la respuesta.
 *              Memoria: O(1).
 * Cuándo usarlo: cuando el arreglo está ordenado o cuando la respuesta cumple una
 *              función monótona (F...F V...V o V...V F...F).
 */
#include <bits/stdc++.h>
using namespace std;

/*BINARY SEARCH
La idea principal de la búsqueda binaria es encontrar una posición o un valor dentro de un espacio ordenado.
En lugar de revisar elemento por elemento, descartamos la mitad de las posibilidades en cada paso.
Al dividir a la mitad en cada iteración nuestra complejidad se vuelve O(log n) por cada búsqueda.
Existen 2 usos principales de la binaria:
1.- Sobre un arreglo
2.- Sobre una respuesta
*/

/*Binary sobre un arreglo
Sea a un arreglo de enteros ordenados.
*/

/*Buscar si existe un valor exacto
Si hay valores repetidos regresa la posición de alguno de ellos, no necesariamente la primera (para la primera usa lowerBound).
*/
int binarySearch(vector<int>& a,int x){
    //Establecemos los límites de la binaria desde 0 hasta n-1, que es el último índice de nuestro arreglo.
    int l=0,r=(int)a.size()-1;
    while(l<=r){
        //m va a ser quien divida a la mitad y nos ayude a descartar lo que no sirva.
        //Se calcula como l+(r-l)/2 y no como (l+r)/2 para evitar overflow.
        int m=l+(r-l)/2;
        //Encontramos el valor y regresamos la posición.
        if(a[m]==x)return m;
        //Si a[m] < x descartamos la mitad de la izquierda, ya que sabemos que x debe estar al menos una posición después de m.
        //Si no, descartamos la de la derecha, porque sabemos que x debe estar al menos una posición antes que m.
        if(a[m]<x)
            l=m+1;
        else
            r=m-1;
    }
    //Si terminamos la búsqueda y no lo encontramos regresamos -1 para indicar que no existe en el arreglo.
    return -1;
}

/*Encontrar la primera posición >=x o >x
lower_bound y upper_bound son funciones que utilizan una búsqueda binaria.
Podemos obtenerlas con:
int pos = lower_bound(a.begin(),a.end(),x)-a.begin();
int pos = upper_bound(a.begin(),a.end(),x)-a.begin();
O programar la binaria: tomamos como base lowerBound, pero podemos cambiar el >= por > para obtener upperBound.
*/
int lowerBound(vector<int>& a,int x){
    //Establecemos los límites de la binaria desde 0 hasta n, ya que si la respuesta es n significa que no hay dentro del arreglo ningún valor >=x.
    //Aquí usamos l<r (y no l<=r): r=n solo es válido como respuesta, nunca se accede a a[n].
    int l=0,r=(int)a.size();
    while(l<r){
        //m va a ser quien divida a la mitad y nos ayude a descartar lo que no sirva.
        int m=l+(r-l)/2;
        //Si a[m]>=x reducimos r, porque ya nos aseguramos de que a[m] es al menos mayor o igual a x.
        //Si es menor avanzamos 1, porque x debe estar al menos una posición después.
        if(a[m]>=x)// Solo cambiamos >= por > para el upper, lo demás es idéntico
            r=m;
        else
            l=m+1;
    }
    //Regresamos la posición en donde se cumplió.
    return l;
}

/*Binary sobre una respuesta
Es muy importante que podamos hacer una función de la forma:
-V=verdadero
-F=falso
V V V V V F F F F F
o también:
F F F F F V V V V V
Donde al inicio sea siempre verdadero y después siempre falso, o primero siempre falso y después siempre verdadero.
Con la binaria podemos buscar 2 cosas: el último valor antes del cambio o el primero después del cambio.
Esto nos puede ayudar a maximizar o minimizar las soluciones.
*/

/*Minimizar
Dada una función de la forma
F F F F V V V V
imprime el mínimo x que cumple con algo (el primer verdadero de la función).
*/
long long minimizar(long long minimo,long long maximo,function<bool(long long)> puede){
    //Establecemos los límites de la binaria; generalmente va de 0 a un valor muy grande como 1e18,
    //que cabe sin problema en límites de 1 segundo (son unas 60 iteraciones), pero si de antemano se conoce entre qué valores puede estar la solución, así se establecen el mínimo y el máximo.
    long long l=minimo, r=maximo;
    while(l<r){
        //m es igual al piso de la división.
        long long m = l + (r-l)/2;
        //La función puede se ajusta al problema; nos devuelve un bool, verdadero o falso, para la m actual.
        if(puede(m)){
            //Reducimos la r y sabemos que puede ser esa la solución o estar antes.
            r=m;
        }
        //Si es falso, avanzamos 1, ya que sabemos que ese es falso y necesitamos el primer verdadero, por lo que al menos está uno después.
        else l=m+1;
    }
    //Por último regresamos la l, que nos da el primer valor que cumple con algo (en un problema la imprimimos con cout<<l<<endl;).
    //Si puede nunca es verdadera, l termina valiendo maximo, así que si puede no haber solución verifica puede(l).
    return l;
}

/*Maximizar
Dada una función de la forma
V V V V V F F F F F
imprime el máximo x que cumple con algo (el último verdadero de la función).
*/
long long maximizar(long long minimo,long long maximo,function<bool(long long)> puede){
    //Establecemos los límites de la binaria; generalmente va de 0 a un valor muy grande como 1e18,
    //pero si de antemano se conoce entre qué valores puede estar la solución, así se establecen el mínimo y el máximo.
    long long l=minimo, r=maximo;
    while(l<r){
        //m es igual al techo de la división.
        long long m = l + (r-l+1)/2;
        //La función puede se ajusta al problema; nos devuelve un bool, verdadero o falso, para la m actual.
        if(puede(m)){
            //Aumentamos la l y sabemos que puede ser esa la solución o estar después.
            l=m;
        }
        //Si es falso sabemos que por lo menos tiene que estar una antes, por lo que reducimos r restándole 1.
        else r=m-1;
    }
    //Por último regresamos la l, que nos da el último valor que cumple con algo (en un problema la imprimimos con cout<<l<<endl;).
    //Si puede nunca es verdadera, l termina valiendo minimo, así que si puede no haber solución verifica puede(l).
    return l;
}

/*La diferencia entre minimizar y maximizar es la división piso o techo, para evitar un loop infinito en el while.
Con piso al maximizar, cuando r=l+1 tendríamos m=l y l=m no avanzaría.*/

/*Ejemplo de uso
Pequeño main de prueba para compilar y verificar el archivo.
*/
int main(){
    vector<int> a={1,3,3,5,8,13};
    cout<<binarySearch(a,5)<<"\n";  // 3
    cout<<binarySearch(a,4)<<"\n";  // -1
    cout<<lowerBound(a,3)<<"\n";    // 1
    long long n=50;
    cout<<minimizar(0,1000000000LL,[&](long long m){return m*m>=n;})<<"\n";  // 8: menor x con x*x >= n
    cout<<maximizar(0,1000000000LL,[&](long long m){return m*m<=n;})<<"\n";  // 7: mayor x con x*x <= n
    return 0;
}
