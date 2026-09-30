/*
 * C. Interesting drink
 * Contest: Contest II - 2027-1 (https://codeforces.com/group/P35WkNZDR8/contest/713751)
 * Problema: C. Interesting drink (https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/C)
 * Idea principal: ordenar los precios de las tiendas y, por cada día, buscar con binaria la última tienda con precio <= monedas; su posición es la cantidad de tiendas donde puede comprar.
 * Complejidad: O(n log n + q log n).
 *              Memoria: O(n).
 * Técnicas: ordenamiento, binary search.
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

#define all(x) (x).begin(), (x).end()
#define pb push_back
#define endl '\n'

/*C. Interesting drink
El problema nos dice que una persona quiere comprar su bebida favorita en una tienda. Hay n tiendas
y quiere saber en cuántas la puede comprar si cada día tiene m_i monedas, y quiere saberlo durante q días.

Hacer una búsqueda completa y contar los lugares donde pueda comprar es demasiado para n,q=10^5 (sería O(n*q)).
Por lo que podemos ordenar las tiendas y hacer una búsqueda binaria para poder encontrar la última tienda
donde pueda comprar.
*/
bool puede(ll m,ll x){//Esta es la condición que establecemos en la binaria.
    if(m<=x)return true;
    return false;
}
void solve() {
    vll a;
    ll n;cin>>n;
    for(int i=0;i<n;i++){
        ll x;cin>>x;
        a.pb(x);
    }
    //Primero ordenamos las tiendas para poder aplicar la binaria.
    sort(all(a));
    ll q;cin>>q;
    //Hacemos la binaria para cada día.
    for(int i=0;i<q;i++){
        ll x;cin>>x;
        ll l=0,r=n-1,m;
        //Buscamos el último <=x en las tiendas.
        //La función es de la forma V V V V V F F F F F
        while(l<=r){
            m=l+(r-l)/2;
            if(puede(a[m],x))l=m+1;
            else r=m-1;
        }
        //Al terminar, l es la posición del primer precio mayor a x, o sea, la cantidad de tiendas con precio <= x.
        cout<<l<<endl;
    }
}

/*Programa principal
El problema tiene un solo caso de prueba, por lo que llamamos solve() una sola vez.
*/
int main(){
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
