/**
 * @file test_air_config.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/31 10:07:57
 */

#include <stdlib.h>

#include "air_config.h"

int main(int argc, char *argv[])
{
    char *key, *value, *error;
    int num_int;
    struct air_config_value *acvp;

    if (air_config_parse("example.conf", &error) == NULL) {
        if (error == NULL) {    /* open failed */
            if (air_config_parse("/etc/example.conf", &error) == NULL) {
                if (error == NULL) {    /* open failed */
                    fprintf(stderr, "can not parse configure file, please check pip.conf in ./ or /etc/\n");
                    exit(1);
                } else {
                    fprintf(stderr, "parse failed: %s\n", error);
                    exit(1);
                }
            }
        } else {
            fprintf(stderr, "parse failed: %s\n", error);
            exit(1);
        }
    }
    
    air_config_show_list(global_configh);

    fprintf(stdout, "=================================\n");

    key = "int";
    air_config_get_int(global_configh, key, &num_int);
    fprintf(stdout, "search %s, found %s: %d\n", key, key, num_int);

    key = "uint";
    air_config_get_string(global_configh, key, &value);
    fprintf(stdout, "search %s, found %s: %s\n", key, key, value ? value: "null");
 
    key = "unex";
    air_config_get_string(global_configh, key, &value);
    fprintf(stdout, "search %s, found %s: %s\n", key, key, value ? value: "null");

    key = "string_array";
    air_config_get_array(global_configh, key, &acvp);
    while (acvp != NULL) {
        value = acvp->value;
        fprintf(stdout, "search %s, found %s: %s\n", key, key, value ? value: "null");
        acvp = acvp->next;
    }

    air_config_destroy(global_configh);

    return 0;
}



