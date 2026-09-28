/*
 * Prefix Sums (Sumas prefijas)
 * Categoría: estructuras_de_datos
 * Descripción: Acumulados desde el inicio de un arreglo para responder consultas en O(1):
 *              suma, mínimo, máximo, conteo y una plantilla general (suma, min, max, XOR).
 * Complejidad: Construcción O(n). Consulta O(1). Actualización O(n) en el peor caso.
 *              Memoria: O(n).
 * Cuándo usarlo: cuando hay muchas consultas sobre prefijos o rangos de un arreglo o string
 *              y este no cambia (o casi no cambia) entre consultas.
 */
#include <bits/stdc++.h>
using namespace std;

/*PREFIX
Nos sirven para convertir muchas consultas o cálculos sobre arreglos o strings en operaciones rápidas.
Esto se precomputa en O(n) siempre y cuando no haya actualizaciones de por medio, ya que por cada
actualización en el peor de los casos es O(n). Si se requieren muchas actualizaciones es mejor buscar otras técnicas o estructuras.

Un prefix contiene información acumulada desde el inicio de un arreglo y podemos realizar consultas en O(1).
En este caso solo voy a hacer las implementaciones y hablar del prefix.
Pero el concepto del suffix es idéntico, solo que partiendo desde el final y hacia el inicio.

Les colocaré algunas de las implementaciones más útiles del prefix.
Muy importante recalcar que la construcción es en O(n), y las consultas en O(1).

En los ejemplos, a es un arreglo de n elementos indexado desde 0, i es una posición y l, r son los extremos de un rango (ambos incluidos).
*/

/*Prefix Sum
Este prefix se caracteriza por ser un acumulado de sumas durante el arreglo, nos ayuda a conocer la suma
de los elementos de un arreglo en cierto rango.
*/
void prefixSum(vector<int>& a,int i,int l,int r){
    int n=(int)a.size();
    //Establecemos nuestro prefix de tamaño n+1 para mayor comodidad en las consultas.
    //Usamos long long porque la suma acumulada puede superar el límite de int.
    vector<long long> pref(n+1);
    //Inicializamos siempre en un elemento neutro.
    pref[0]=0;
    //Recorremos el arreglo y calculamos la posición siguiente del prefix a partir de la actual.
    for(int k=0;k<n;k++){
        pref[k+1]=pref[k]+a[k];
    }
    //Esto nos da como resultado que cada posición i del arreglo pref tiene el acumulado de todas las posiciones anteriores a i.

    //Quiero saber cuál es la suma de los elementos anteriores a i.
    long long anteriores=pref[i];

    //Quiero saber cuál es la suma en el rango l r.
    long long rango=pref[r+1]-pref[l];
    //Usamos r+1 porque si usáramos r contaríamos lo anterior a r sin contar a r.
    //Usamos l porque me resta todo lo anterior a l, o sea lo que está afuera de mi rango.
    cout<<anteriores<<" "<<rango<<"\n";
}

/*Prefix Minimum y Maximum
Estos prefix nos ayudan a saber cuál es el elemento más grande (Maximum) o más pequeño (Minimum) hasta una posición.
*/
void prefixMinMax(vector<int>& a,int i){
    int n=(int)a.size();
    //Se inicializa de la misma manera que el de sumas, con la diferencia de que el neutro del máximo es INT_MIN y el del mínimo es INT_MAX
    //(con 0 en el máximo fallaría si todos los elementos son negativos).
    vector<int> prefMaxi(n+1), prefMini(n+1);
    prefMaxi[0]=INT_MIN;
    prefMini[0]=INT_MAX;
    //Recorremos el arreglo y guardamos el máximo o el mínimo según lo que nos pida.
    for(int k=0;k<n;k++){
        prefMaxi[k+1]=max(prefMaxi[k],a[k]);
        prefMini[k+1]=min(prefMini[k],a[k]);
    }
    //Quiero saber cuál es el elemento más grande que hay antes de la posición i.
    int mayor=prefMaxi[i];
    //Quiero saber cuál es el elemento más pequeño antes de la posición i.
    int menor=prefMini[i];
    cout<<mayor<<" "<<menor<<"\n";
}

/*Prefix Count
Este prefix nos puede ayudar a saber cuántas veces aparece un elemento x antes de una posición o un rango.
*/
void prefixCount(vector<int>& a,int x,int i,int l,int r){
    int n=(int)a.size();
    //Mismo proceso de inicialización.
    vector<int> prefCount(n+1);
    prefCount[0]=0;
    //Recorremos el arreglo y agregamos uno cada que encontremos el valor x.
    for(int k=0;k<n;k++){
        prefCount[k+1]=prefCount[k]+(a[k]==x);
    }
    //Quiero saber cuántas veces aparece x antes de i.
    int veces=prefCount[i];
    //Cuántas veces aparece x en el rango l r.
    int veces_rango=prefCount[r+1]-prefCount[l];
    cout<<veces<<" "<<veces_rango<<"\n";
}

/*PREFIX GENERAL
En resumen podríamos quedarnos con una plantilla y sustituir combinar por la temática de nuestro pref
(en este archivo combinar y neutro se reciben como parámetros para poder probarla).
Los usos más comunes son:
+ sumas
min() mínimo
max() máximo
^ XOR
*/
void prefixGeneral(vector<int>& a,long long neutro,function<long long(long long,long long)> combinar,int i,int l,int r){
    int n=(int)a.size();
    vector<long long> pref(n+1);
    pref[0]=neutro; //Casi siempre es el neutro

    for(int k=0;k<n;k++){
        pref[k+1]=combinar(pref[k],a[k]);
    }
    //Consultas
    long long antes=pref[i];             //lo que está antes de i
    long long entre=pref[r+1]-pref[l];   //lo que está entre l y r
    //Ojo: la resta pref[r+1] - pref[l] solo funciona con operaciones que se pueden deshacer, como la suma o el conteo.
    //Con XOR el rango se obtiene con pref[r+1] ^ pref[l], porque aplicar XOR dos veces cancela el valor.
    //Con min y max no se puede deshacer, por lo que esos prefix solo responden consultas desde el inicio (pref[i]).
    cout<<antes<<" "<<entre<<"\n";
}

/*Ejemplo de uso
Pequeño main de prueba para compilar y verificar el archivo.
Todas las consultas usan i=3 y el rango l=1, r=4.
*/
int main(){
    vector<int> a={2,-1,4,-1,3,6};
    prefixSum(a,3,1,4);         // 5 5
    prefixMinMax(a,3);          // 4 -1
    prefixCount(a,-1,3,1,4);    // 1 2
    prefixGeneral(a,0,[](long long x,long long y){return x+y;},3,1,4);  // 5 5
    return 0;
}
