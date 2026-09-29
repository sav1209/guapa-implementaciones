/*
 * B. Pashmak and Flowers
 * Contest: Contest II - 2027-1 (https://codeforces.com/group/P35WkNZDR8/contest/713751)
 * Problema: B. Pashmak and Flowers (https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/B)
 * Idea principal: la máxima diferencia es maximo-minimo; las parejas se cuentan con las veces que aparece cada extremo.
 * Complejidad: O(n).
 *              Memoria: O(n).
 * Técnicas: conteo, combinatoria básica (combinaciones de 2 en n).
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

/*B. Pashmak and Flowers
El problema nos dice que dado un arreglo b con n flores, donde cada posición b[i]
representa el nivel de belleza de una flor, se quiere saber la mayor diferencia de belleza que se puede
obtener entre 2 flores y de cuántas maneras se pueden seleccionar parejas de flores que cumplan la condición
de tener esa máxima diferencia de belleza entre ellas.

Para saber qué flores tienen la mayor diferencia nos conviene tomar las de belleza mayor y las de
belleza menor del arreglo. Esto nos garantiza que las combinaciones cumplirán la condición de
tener la máxima diferencia entre ellas.
*/
void solve() {
    ll n,mini=LLONG_MAX,maxi=LLONG_MIN,cantm=0,cantx=0;
    cin>>n;
    vll b(n);
    //Primero obtenemos el valor máximo y el mínimo del arreglo.
    for(int i=0;i<n;i++){
        cin>>b[i];
        mini=min(mini,b[i]);
        maxi=max(maxi,b[i]);
    }
    //Después calculamos cuántas flores hay con ese valor.
    for(int i=0;i<n;i++){
        if(b[i]==mini)cantm++;
        if(b[i]==maxi)cantx++;
    }
    //Imprimimos la máxima diferencia entre el valor más grande y el más pequeño.
    cout<<maxi-mini<<" ";
    /*Cantidad de parejas
    Por último es importante notar 2 casos.
    */
    /*Si el máximo y el mínimo son diferentes hay que multiplicar las 2 cantidades de flores
    que hay, ya que esto nos da la cantidad de maneras en que puedo tomar las parejas.
    */
    if(mini!=maxi){
        cout<<cantm*cantx<<"\n";
    }
    /*Si son iguales, todas las flores tienen la misma belleza y cualquier pareja sirve, así que debemos saber
    ¿cuántas maneras hay de seleccionar 2 flores diferentes de un grupo de n? Lo cual se responde
    con n en 2, o simplificando nos queda como (n*(n-1))/2. En este caso cantx es igual a n.
    */
    else{
        cout<<cantx*(cantx-1)/2<<"\n";
    }
}

/*Programa principal
El problema tiene un solo caso de prueba, por lo que llamamos solve() una sola vez.
*/
int main(){
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
