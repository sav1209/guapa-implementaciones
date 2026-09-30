/*
 * E. Magic Powder - 2
 * Contest: Contest II - 2027-1 (https://codeforces.com/group/P35WkNZDR8/contest/713751)
 * Problema: E. Magic Powder - 2 (https://codeforces.com/group/P35WkNZDR8/contest/713751/problem/E)
 * Idea principal: binaria sobre la respuesta; x galletas son posibles si el polvo mágico alcanza para cubrir lo que falta de cada ingrediente.
 * Complejidad: O(n*log(2*10^9)).
 *              Memoria: O(n).
 * Técnicas: binary search sobre la respuesta.
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

#define endl '\n'

/*E. Magic Powder - 2
El problema nos dice que debemos hornear galletas; para las galletas ocupamos n ingredientes.
De antemano sabemos cuántos gramos a_i necesitamos de cada uno y cuántos b_i tenemos en un principio.
Además tenemos k gramos de polvo mágico que podemos usar para sustituir cualquier ingrediente.

Podemos realizar una búsqueda binaria sobre la respuesta para encontrar la solución.
Si podemos hacer x galletas también podemos hacer x-1, por lo que la función es de la forma V V V F F F.
Como a_i>=1, b_i<=10^9 y k<=10^9, a lo mucho podemos hacer 2*10^9 galletas (todo lo que tenemos de un ingrediente más todo el polvo),
por lo que podemos aprovechar eso y usar una binaria entre 0 y 2*10^9. Esto nos da una complejidad de O(n*log(2*10^9)).
Con ese límite, a_i*x es a lo mucho 10^9*2*10^9=2*10^18, que cabe en un long long (con 1e10 se desbordaría).
*/
ll n,k;
vll a,b;
bool puede(ll x){
    ll ans=0;
    for(int i=0;i<n;i++){//Recorremos el arreglo sumando lo que nos falta de cada ingrediente
        ans+=max(a[i]*x-b[i],0LL);//Agarramos lo que nos falta o 0, si nos sobra ingrediente
        if(ans>k)return false;//Si la suma es mayor a k, esa cantidad no la podemos hacer.
    }
    return true;
}
void solve() {
    cin>>n>>k;
    a.resize(n),b.resize(n);
    for(auto &x:a)cin>>x;
    for(auto &x:b)cin>>x;
    //Calculamos la binaria de la forma V V V F F F para encontrar el último que se cumple.
    //Los límites van de 0 a 2*10^9, que es lo máximo que podríamos llegar a hacer.
    ll l=0,r=2000000000LL;
    while(l<r){
        //m es igual al techo de la división, para evitar un loop infinito al maximizar.
        ll m=l+(r-l+1)/2;
        //Si podemos hacer esa cantidad aumentamos l, ya que la respuesta es esa o está después.
        if(puede(m))l=m;
        //Si no podemos hacer esa cantidad restamos 1 a r, ya que sabemos que la respuesta es como mínimo una menos.
        else r=m-1;
    }
    //Esa es la cantidad de galletas que podemos hacer.
    cout<<l<<endl;
}

/*Programa principal
El problema tiene un solo caso de prueba, por lo que llamamos solve() una sola vez.
*/
int main(){
    cin.tie(0)->sync_with_stdio(0);
    solve();
}
