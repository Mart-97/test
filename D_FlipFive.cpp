#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct nodo{
	int bmask;
	int pasos;
};

int N;
char original[3][3];
bool mapa[3][3];
int meta;
queue<nodo> cola;
map<int, bool> visitados;

int bitMask(bool bMapa[3][3]){
	int mask = 0;
	mask |= bMapa[0][0] << 0;
	mask |= bMapa[0][1] << 1;
	mask |= bMapa[0][2] << 2;

	mask |= bMapa[1][0] << 3;
	mask |= bMapa[1][1] << 4;
	mask |= bMapa[1][2] << 5;

	mask |= bMapa[2][0] << 6;
	mask |= bMapa[2][1] << 7;
	mask |= bMapa[2][2] << 8;

	return mask;
}

void toMap(int mask, bool bMapa[3][3]){
	bMapa[0][0] = mask & (1 << 0);
	bMapa[0][1] = mask & (1 << 1);
	bMapa[0][2] = mask & (1 << 2);

	bMapa[1][0] = mask & (1 << 3);
	bMapa[1][1] = mask & (1 << 4);
	bMapa[1][2] = mask & (1 << 5);

	bMapa[2][0] = mask & (1 << 6);
	bMapa[2][1] = mask & (1 << 7);
	bMapa[2][2] = mask & (1 << 8);
}

bool valido(int x, int y) {
	if(x < 0 || x > 2 || y < 0 || y > 2) return false;
	return true;
}

void clickear(bool bMapa[3][3], int i, int j){
	if(valido(i,j)) 	bMapa[i][j] 	= !bMapa[i][j]; //Centro
	if(valido(i-1,j)) 	bMapa[i-1][j] 	= !bMapa[i-1][j];	
	if(valido(i,j-1)) 	bMapa[i][j-1] 	= !bMapa[i][j-1];
	if(valido(i+1,j)) 	bMapa[i+1][j] 	= !bMapa[i+1][j];
	if(valido(i,j+1)) 	bMapa[i][j+1] 	= !bMapa[i][j+1];
}

int BFS(){
	nodo actual;
	actual.bmask = 0;
	actual.pasos = 0;

	cola.push(actual);
	while(!cola.empty()){
		actual = cola.front();
		cola.pop();

		if(visitados[actual.bmask]) continue;
		visitados[actual.bmask] = true;

		if(actual.bmask == meta) return actual.pasos;

		bool nMapa[3][3];
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				nodo nuevo;
				toMap(actual.bmask, nMapa);
				clickear(nMapa, i, j);
				nuevo.bmask = bitMask(nMapa);
				nuevo.pasos = actual.pasos + 1;
				cola.push(nuevo);
			}
		}
	}
	return -1;
}

int main(){
	cin >> N;
	while(N--){
		//Leemos el mapa original
		for(int i = 0; i < 3; i++){
			cin >> original[i];
		}

		for(int i=0; i < 3; i++){
			for(int j=0; j < 3; j++){
				mapa[i][j] = original[i][j] == '*';
			}
		}

		meta = bitMask(mapa);

		cout << BFS() << endl;
		while(!cola.empty()) cola.pop();	//Eliminamos los nodos que se quedaron de la anterior
		visitados.clear();					//Limpiamos los visitados

	}
	return 0;
}
