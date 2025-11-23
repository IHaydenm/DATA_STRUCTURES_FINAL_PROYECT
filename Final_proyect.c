#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 30   // número total de estados

const char* nombres[V] = {
    "California", "Oregon", "Nevada", "Arizona", "Idaho", "Washington",
    "Utah", "New Mexico", "Montana", "Wyoming", "North Dakota",
    "South Dakota", "Nebraska", "Colorado", "Kansas", "Oklahoma",
    "Texas", "Minnesota", "Iowa", "Wisconsin", "Illinois", "Indiana",
    "Missouri", "Arkansas", "Louisiana", "Mississippi", "Alabama",
    "Tennessee", "Kentucky", "Michigan"
};

int distanciaMinima(int dist[], bool visitado[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visitado[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int grafo[V][V], int origen, int destino) {
    int dist[V];
    bool visitado[V];
    int anterior[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visitado[i] = false;
        anterior[i] = -1;
    }

    dist[origen] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = distanciaMinima(dist, visitado);
        if (u == -1) break;
        visitado[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visitado[v] && grafo[u][v] > 0 &&
                dist[u] + grafo[u][v] < dist[v]) {

                dist[v] = dist[u] + grafo[u][v];
                anterior[v] = u;
            }
        }
    }

    if (dist[destino] == INT_MAX) {
        printf("\nNO existe ruta entre %s y %s.\n",
                nombres[origen], nombres[destino]);
        return;
    }

    int camino[V], tam = 0;

    for (int v = destino; v != -1; v = anterior[v]) {
        camino[tam++] = v;
    }

    printf("\nDistancia mínima entre %s y %s: %d km\n",
           nombres[origen], nombres[destino], dist[destino]);

    printf("Camino: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%s", nombres[camino[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}

int main() {
    
    int grafo[V][V] = {
/*CA   OR   NV   AZ   ID   WA   UT   NM   MT   WY   ND   SD   NE   CO   KS   OK   TX   MN   IA   WI   IL   IN   MO   AR   LA   MS   AL   TN   KY   MI */
{  0,1074, 881,1185,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // CA
{1074,  0, 834,   0, 635,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // OR
{ 881,834,   0,   0,   0,   0, 626,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // NV
{1185,  0,   0,   0,   0,   0,1036, 710,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // AZ
{  0,635,   0,   0,   0,935,   0,   0, 841,832,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // ID
{  0,  0,   0,   0,935,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // WA
{  0,  0, 626,1036,   0,   0,   0,   0,   0,593,   0,   0,   0,807,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // UT
{  0,  0,   0, 710,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,799,645,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // NM
{  0,  0,   0,   0,841,   0,   0,   0,   0,679,843,1067,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // MT
{  0,  0,   0,   0,832,   0,593,   0,679,   0,   0,   0,730,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // WY
{  0,  0,   0,   0,   0,   0,   0,   0,843,   0,   0,518,   0,   0,   0,   0,   0,558,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // ND
{  0,  0,   0,   0,   0,   0,   0,   0,1067,  0,518,   0,   0,   0,   0,   0,   0,725,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // SD
{  0,  0,   0,   0,   0,   0,   0,   0,   0,730,   0,   0,   0,   0,   0,   0,   0,   0,645,   0,   0,   0,356,   0,   0,   0,   0,   0,   0,   0}, // NE
{  0,  0,   0,   0,   0,   0,807,   0,   0,   0,   0,   0,   0,   0,743,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // CO
{  0,  0,   0,   0,   0,   0,   0,799,   0,   0,   0,   0,   0,743,   0,568,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // KS
{  0,  0,   0,   0,   0,   0,   0,799,   0,   0,   0,   0,   0,   0,568,   0,1004,   0,   0,   0,   0,   0,   0,448,   0,   0,   0,   0,   0}, // OK
{  0,  0,   0,   0,   0,   0,   0,645,   0,   0,   0,   0,   0,   0,   0,1004,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // TX
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,558,725,   0,   0,   0,   0,   0,   0,650,684,   0,   0,   0,   0,   0,   0,   0,   0,   0}, // MN
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,645,   0,   0,   0,   0,650,   0,   0,   0,   0,356,426,   0,   0,   0,   0,   0}, // IA
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,684,   0,   0,448,298,   0,   0,   0,   0,   0,   0,522}, // WI
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,448,   0,218,442,658,   0,   0,   0,   0,   0}, // IL
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,298,218,   0,   0,   0,   0,   0,   0,   0,   0}, // IN
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,356,   0,   0,   0,   0,   0,356,   0,442,   0,   0,426,   0,   0,   0,   0,   0}, // MO
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,448,   0,   0,426,   0,658,   0,426,   0,448,   0,   0,   0,   0}, // AR
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,448,   0,   0,   0,   0,   0,   0,   0,448,   0,397,   0,   0,   0}, // LA
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,397,   0,245,   0,   0}, // MS
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,245,   0,408,   0}, // AL
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,408,   0,281}, // TN
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,281,   0}, // KY
{  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,522,   0,   0,   0,   0,   0,   0,   0,   0,   0}  // MI
};
    
    while (1) {
        printf("\n===== LISTA DE ESTADOS =====\n");
        for (int i = 0; i < V; i++) {
            printf("%2d) %s\n", i, nombres[i]);
        }

        int origen, destino;
        char opcion;

        printf("\nSeleccione el estado ORIGEN (0-29): ");
        scanf("%d", &origen);

        printf("Seleccione el estado DESTINO (0-29): ");
        scanf("%d", &destino);

        if (origen < 0 || origen >= V || destino < 0 || destino >= V) {
            printf("ERROR: valores fuera de rango.\n");
            continue;
        }

        dijkstra(grafo, origen, destino);

        printf("\n¿Deseas buscar otra ruta? (s/n): ");
        scanf(" %c", &opcion);

        if (opcion == 'n' || opcion == 'N') {
            printf("Saliendo del programa...\n");
            break;
        }
    }

    return 0;
}