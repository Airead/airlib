/**
 * @file air_config.h
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/27 09:16:40
 */

#ifndef _AIR_CONFIG_H_
#define _AIR_CONFIG_H_

#include <stdio.h>

#define CONFIG_KEY_SIZE 64
#define CONFIG_VALUE_SIZE 128
#define CONFIG_ERROR_SIZE 256

/**
 * @brief state overview
 *
 * APSOK:
 *     parse configure file ok. when reaching file end, and (kp == key && vp == value) (key value is complete) APSOK will return.
 * APSSTART:
 *     core state transmit routing. special char: '
 * APSCOMMENT:
 *     skip all char until receive '\n'
 * APSSPACE:
 *     skip all ' ' and '\t'.
 * APSSTRING:
 *     store all char until receive '"'
 * APSKSTART:
 *     speacial char ' ', '\t', ';' stand for key end;
 * APSVSTART:
 *     ' ', '\t', ',', ';' stand for value end; '"' stands for string start;
 * APSVASTART:
 *     value array start
 * APSVAEND:
 *     one value array is ready to add
 * APSKVFIN:
 *     one key-value pair is ready to add
 * APSEEOF:
 *     unexpected file end, the key-value pair is not complete;
 * APSERROR:
 *     some unkonwn error;
 * APSESEMMI:
 *     unexcept semmicolon error
 * APSENEEDCOMMA:
 *     except comma error
 * APSECOMMA:
 *     unexcept comma error
 */

enum air_parse_state {
    APSOK,
    APSSTART,                   /* AIR PARSE STATE START */
    APSCOMMENT,
    APSSPACE,
    APSSTRING,
    APSKSTART,
    APSVSTART,
    APSVASTART,                 /* VALUE ARRAY START */
    APSVAEND,
    APSKVFIN,                   /* KEY VALUE FINISH */
    APSEEOF,
    APSERROR,
    APSESEMMI,                  /* unexpect semicolon*/
    APSENEEDCOMMA,
    APSECOMMA,                 /* unexpect comma */
    APSEDUP,                   /* duplicate */
};
enum air_value_type {
    AVTINT,                     /* AIR VALUE INT */
    AVTUINT,
    AVTBOOL,
    AVTSTR,
};

struct air_config_value {
    struct air_config_value *next;
    char *value;
};

struct air_config_t {
    struct air_config_t *next;
    char *key;
    void *value;
    int type;
    int array;                /* 1 for array, 0 for noarray */
    int num;
};

#define config_valueh(key) ((struct air_config_value *)(key->value))

void air_config_destroy_key(struct air_config_t *key);
void air_config_destroy(struct air_config_t *ach);
int air_config_append(struct air_config_t *ach, struct air_config_t *node);
int air_config_append_value(struct air_config_t *key, char *value);
int air_config_catch(struct air_config_t *ach, char *key, char *value, int array);
int air_config_handler(struct air_config_t *ach, FILE *in, int aps, char *error);
struct air_config_t *air_config_parse(char *file, char **error);
void air_config_show_list(struct air_config_t *ach);
int air_config_get(struct air_config_t *ach, char *key, struct air_config_t **result);
int air_config_get_string(struct air_config_t *ach, char *key, char **result);
int air_config_get_array(struct air_config_t *ach, char *key, struct air_config_value **result);
int air_config_get_int(struct air_config_t *ach, char *key, int *result);

extern struct air_config_t *global_configh;
#endif /* _AIR_CONFIG_H_ */
