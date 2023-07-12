#include <stdio.h>
#include <oqs/oqs.h>
#include <string.h>


short parse_args(int argc, char **argv, int *qgc_root_pos, int *ap_root_pos);
short save_key(const char *path, const char *filename, uint8_t key[], int key_length);


int main(int argc, char **argv) {
    
    uint8_t private_key_gcs[OQS_KEM_kyber_512_length_secret_key];
    uint8_t public_key_gcs[OQS_KEM_kyber_512_length_public_key];

    uint8_t private_key_uav[OQS_KEM_kyber_512_length_secret_key];
    uint8_t public_key_uav[OQS_KEM_kyber_512_length_public_key];

    if (argc < 5 || (argc > 1 && !strcmp(argv[1], "--help"))) {
        fprintf(stderr, "Questo programma genera due coppie di chiavi da utilizzare per l'algoritmo Kyber-512..\n");
        fprintf(stderr, "È necessario specificare la root di ArduPilot mediante l'argomento --ap.\n");
        fprintf(stderr, "È necessario specificare inoltre la root di QGroundControl mediante l'argomento --qgc.\n");
        fprintf(stderr, "La chiave pubblica della GCS verrà copiata nella root di ArduPilot insieme alla chiave privata di quest'ultimo.\n");
        fprintf(stderr, "La chiave pubblica dell'UAV verrà copiata nella root di QGroundControl insieme alla chiave privata di quest'ultimo.\n");
        exit(1);
    } else {
        int qgc_root_pos = 0;
        int ap_root_pos = 0;


        if (!parse_args(argc, argv, &qgc_root_pos, &ap_root_pos)) {
            fprintf(stderr, "Errore nel parsing degli argomenti. Invoca il programma con --help per ulteriori informazioni.\n");
            exit(1);
        } else {
            fprintf(stdout, "Generazione delle chiavi per la GCS.\n");

            OQS_STATUS result = OQS_KEM_kyber_512_keypair(public_key_gcs, private_key_gcs);
            if (result != OQS_SUCCESS) {
                fprintf(stderr, "Errore nella generazione per la coppia di chiavi per la GCS. Uscita.\n");
                exit(1);
            }

            fprintf(stdout, "Generazione delle chiavi per l'UAV.\n");
            result = OQS_KEM_kyber_512_keypair(public_key_uav, private_key_uav);
            if (result != OQS_SUCCESS) {
                fprintf(stderr, "Errore nella generazione per la coppia di chiavi per l'UAV. Uscita.\n");
                exit(1);
            }

            fprintf(stdout, "Salvataggio delle chiavi per la GCS.\n");
            
            if (!save_key(argv[ap_root_pos], "public_key_gcs.key", public_key_gcs, OQS_KEM_kyber_512_length_public_key)) {
                fprintf(stderr, "Salvataggio della chiave pubblica per la GCS non riuscito");
                exit(1);
            }

            if (!save_key(argv[qgc_root_pos], "private_key_gcs.key", private_key_gcs, OQS_KEM_kyber_512_length_secret_key)) {
                fprintf(stderr, "Salvataggio della chiave privata per la GCS non riuscito");
                exit(1);
            }

            fprintf(stdout, "Salvataggio delle chiavi per l'UAV.\n");

            if (!save_key(argv[qgc_root_pos], "public_key_uav.key", public_key_uav, OQS_KEM_kyber_512_length_public_key)) {
                fprintf(stderr, "Salvataggio della chiave pubblica per l'UAV non riuscito.\n");
                exit(1);
            }

            if (!save_key(argv[ap_root_pos], "private_key_uav.key", private_key_uav, OQS_KEM_kyber_512_length_secret_key)) {
                fprintf(stderr, "Salvataggio della chiave privata per l'UAV non riuscito.\n");
                exit(1);
            }
        }
    }
}

short parse_args(int argc, char **argv, int *qgc_root_pos, int *ap_root_pos) {
    if (qgc_root_pos == NULL || ap_root_pos == NULL) {
        return 0;
    } else {
        int index = 0;
        short qgc_path_found = 0;
        short ap_path_found = 0;
        
        while (index < argc) {
            // Si assume che il parametro successivo sia un percorso valido
            if (!strcmp(argv[index], "--ap")) {
                ap_path_found = 1;
                *ap_root_pos = index + 1;
            }

            if (!strcmp(argv[index], "--qgc")) {
                qgc_path_found = 1;
                *qgc_root_pos = index + 1;
            }

            index++;
        }

        if (qgc_path_found && ap_path_found) {
            return 1;
        } else {
            return 0;
        }
    }
}


short save_key(const char *path, const char *filename, uint8_t key[], int key_length) {
    int complete_filename_length = strlen(path) + strlen(filename) + 1;
    char *complete_filename = calloc(complete_filename_length, sizeof(char));

    if (complete_filename == NULL) {
        return 0;
    }

    complete_filename = strncat(complete_filename, path, strlen(path));
    complete_filename = strncat(complete_filename, filename, strlen(filename));

    FILE *file_pointer = fopen(complete_filename, "wb");

    if (file_pointer == NULL) {
        return 0;
    }

    if (fwrite(key, sizeof(uint8_t), key_length, file_pointer) != key_length) {
        fprintf(stderr, "fwrite ha riportato un errore.\n");
        fclose(file_pointer);
        free(complete_filename);
        return 0;
    }

    fclose(file_pointer);
    free(complete_filename);
    return 1;
}