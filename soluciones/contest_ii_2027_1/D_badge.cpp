/*
 * D. Badge
 * Contest: Contest II - 2027-1 (https://codeforces.com/group/P35WkNZDR8/contest/713751)
 * Problema: D. Badge (https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/D)
 * Idea principal: para cada estudiante, seguir la cadena de culpas hasta llegar al primero que se repite.
 * Complejidad: O(n^2): cada simulación recorre a lo más n estudiantes y se hace una por estudiante.
 *              Memoria: O(n).
 * Técnicas: simulación, grafos (recorrido con arreglo de visitados).
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

#define endl '\n'

/*D. Badge
El problema nos dice que un grupo de estudiantes hizo algo malo, la maestra visitó a cada uno y cada
uno le echó la culpa a alguien más.

El problema consiste en, para cada estudiante como punto de partida, encontrar el primero que se repite en esta cadena de culpas.
Como cada estudiante culpa a exactamente uno, la cadena siempre repite a alguien en a lo más n pasos,
por lo que cada simulación es O(n) y, al hacer una por estudiante, la complejidad total es O(n^2), suficiente para n=1000.
*/
void solve() {
    ll n;cin>>n;
    vll a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];//Leemos los alumnos y los 0 indexamos para trabajar directamente con el arreglo
        a[i]--;
    }
    for(int i=0;i<n;i++){
        vector<bool> vis(n,true);//Vector de visitados para saber cuáles alumnos no hemos visitado (true = sin visitar)
        ll x=i;
        while(vis[x]){//mientras no lo hayamos visitado lo visitamos
            vis[x]=false;//lo marcamos como falso para indicar que ya lo visitamos
            x=a[x];//visitamos al que le echó la culpa
        }
        cout<<x+1<<" ";//si alguno estaba visitado salimos del bucle e imprimimos el índice +1 por el 0 indexado del principio.
    }
    cout<<endl;
}

/*Programa principal
El problema tiene un solo caso de prueba, por lo que llamamos solve() una sola vez.
*/
int main(){
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
