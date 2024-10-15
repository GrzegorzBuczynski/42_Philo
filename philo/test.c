#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int counter = 0;

void *increment(void *arg) {
    for (int i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&mutex); // Blokujemy mutex
        counter++;
        pthread_mutex_unlock(&mutex); // Zwalniamy mutex
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Inicjalizacja mutexa
    pthread_mutex_init(&mutex, NULL);

    // Utworzenie dwóch wątków
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    // Czekanie na zakończenie wątków
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final counter value: %d\n", counter);

    // Zniszczenie mutexa
    pthread_mutex_destroy(&mutex);

    return 0;
}