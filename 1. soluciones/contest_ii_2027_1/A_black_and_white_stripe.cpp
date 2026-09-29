/*
 * A. Black and White Stripe
 * Contest: Contest II - 2027-1 (https://codeforces.com/group/P35WkNZDR8/contest/713751)
 * Problema: A. Black and White Stripe (https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/A)
 * Idea principal: el mínimo de cambios equivale a la mínima cantidad de 'W' en una ventana de tamaño k.
 * Complejidad: O(n) por caso de prueba con cualquiera de las dos opciones.
 *              Memoria: O(1) en la opción 1 y O(n) en la opción 2.
 * Técnicas: sliding window, prefix sums (frecuencias).
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

/*A. Black and White Stripe
El problema nos dice que dada una cadena s de tamaño n compuesta por letras 'W' y 'B'
hay que buscar el mínimo de cambios que hay que hacer en la cadena para tener al menos un segmento de tamaño k
con únicamente letras 'B'.

La solución del problema se puede traducir a la mínima cantidad de 'W' que hay en un segmento de tamaño k.
Calcular todas las ventanas posibles nos da una complejidad de O(n*k) que para nuestros límites de 2*10^5 no es factible.
Vamos a utilizar una técnica llamada sliding window donde calculamos una ventana y la vamos recorriendo a lo largo
de nuestra cadena n.
*/
void solve() {
    string s;
    ll n,k,ans=LLONG_MAX,x=0;
    cin>>n>>k>>s;
    //Propongo 2 maneras de hacerlo:
    /*Opción 1: sliding window
    Precalcular la primera ventana de tamaño k e ir agregando y quitando 1 elemento del principio
    y del final por cada elemento de n.
    */
    for(int i=0;i<k;i++){//precálculo de cuántas W hay en la primera ventana
        if(s[i]=='W')x++;
    }
    ans=min(x,ans);//actualizamos la respuesta
    //Por último recorremos la cadena y vamos moviendo la ventana: quitamos el elemento de la izquierda y agregamos el nuevo de la derecha.
    for(int i=0;i+k<n;i++){
        if(s[i]=='W')x--;//si el de la izquierda que vamos a quitar era W, disminuimos nuestra x momentánea
        if(s[i+k]=='W')x++;//si el nuevo de la derecha es W aumentamos nuestra x momentánea
        ans=min(ans,x);//nos quedamos con la respuesta mínima
    }
    /*Opción 2: prefix de frecuencias
    Precalcular un prefix de frecuencias, y consultar en O(1) por cada ventana.
    */
    ans=LLONG_MAX;
    vll pref(n+1,0);
    pref[0]=0;
    //Precalculamos nuestro prefix de frecuencias.
    for(int i=0;i<n;i++){
        pref[i+1]=pref[i]+(s[i]=='W');
    }
    for(int i=0;i+k<=n;i++){
        x=pref[i+k]-pref[i];//Obtenemos la cantidad de W en el rango [i, i+k-1]
        ans=min(ans,x);//Nos quedamos con el mínimo
    }
    cout<<ans<<"\n";
}

/*Casos de prueba
El problema tiene múltiples casos de prueba: leemos t y ejecutamos solve() una vez por cada uno.
*/
int main(){
    cin.tie(0)->sync_with_stdio(0);
    int tc = 1;
    cin >> tc;
    while(tc--) solve();
}
