#include "mytui_config.h"

static const char* CONF_FONDER = ".config";
static const char* TUI_FOLDER_CONF = "mytui";
static const char* CONF_FILE_NAME = "init.conf";

static void create_default_conf();

/**
 *  @brief verifica archivo de conf
 *  @return si el archivo de configuracion no existia y es creado es false
 *  verifica si existe los path y archivos de confi de la lab
 */
static bool verification_init_file();

static char* get_file_conf_path();

void ini_conf_file(){
    print_info("ini_con_file");

    char *mytui_conf_file = get_file_conf_path();
    bool exist_file_conf = false;

    if(exist_file(mytui_conf_file) == true){
        exist_file_conf = true;
    }

    print_info("terminada verificacion de existencia de archivos de configuracion");

    if(exist_file_conf == false){
        print_info("recreando conf file");
        create_default_conf(mytui_conf_file);
    }

}

/**
 * genera un archivo de configuracion con la informacion por defecto
 * esta se enciuentra dentro de mytui_std_conf
 * @param path de donde se creara el archivo
 */
static void create_default_conf(char* path_conf_file){
    FILE *f = fopen(path_conf_file, "w");
    if(f == NULL){
        print_error
            ("create_default_conf: error al conseguir el archivo de conf: %s",
             path_conf_file );
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MYTUI_CONF_MAX; i++) {
        fputs( mytui_std_conf_optiones[i] , f);
        fputs("\n", f);
    }
    fclose(f);
}


static char* get_file_conf_path(){
    const char* folder_home = get_home_folder();

    char conf_folder_resolution[ strlen(folder_home) + (strlen(SEPARATOR_FOLDER) * 3) +
        strlen(CONF_FONDER) + strlen(TUI_FOLDER_CONF) + strlen(CONF_FILE_NAME)];

    strcpy(conf_folder_resolution, folder_home);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FONDER);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_CONF);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FILE_NAME);

    static char response[sizeof folder_home + (sizeof SEPARATOR_FOLDER * 3) +  sizeof CONF_FONDER +
        sizeof TUI_FOLDER_CONF + sizeof CONF_FILE_NAME];
    strcpy(response, conf_folder_resolution);
    return response;
}

static bool verification_init_file(){
    const char* folder_home = get_home_folder();

    char conf_folder_resolution[ strlen(folder_home) + (strlen(SEPARATOR_FOLDER) * 3) +
        strlen(CONF_FONDER) + strlen(TUI_FOLDER_CONF) + strlen(CONF_FILE_NAME)];

    strcpy(conf_folder_resolution, folder_home);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FONDER);

    if(exist_file(conf_folder_resolution) == false){
        print_error("No se consigue archivo .conf");
        exit(0);
    }

    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_CONF);

    if(exist_file(conf_folder_resolution) == false){
        char cmd_create_folder_mitui_conf[(strlen(MKDIR) + strlen(conf_folder_resolution))];
        strcpy(cmd_create_folder_mitui_conf, MKDIR);
        strcat(cmd_create_folder_mitui_conf, conf_folder_resolution);
        run_cmd_silent(cmd_create_folder_mitui_conf);
    }

    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FILE_NAME);

    if(exist_file(conf_folder_resolution) == false){
        char cmd_create_folder_mitui_conf[(strlen(TOUCH) + strlen(conf_folder_resolution))];
        strcpy(cmd_create_folder_mitui_conf, TOUCH);
        strcat(cmd_create_folder_mitui_conf, conf_folder_resolution);
        run_cmd_silent(cmd_create_folder_mitui_conf);
        return false;
    }
    return true;
}

void init_conf_map(ConfMap *confMap){
    if(confMap != NULL){
        print_error("init_conf_map: confMap debe ser NULL");
    }
}

void conf_map_add(ConfMap **confMap,  char* key,  char* value){

    int value_len = strlen(value);
    int key_len = strlen(key);
    if( value_len > 255 ||  key_len > 255){
        print_error("conf_map_add: problemas en el archivode configuracion "
                "las opciones no puedne ser mayor a 255, elimine el archivo "
                "en $HOME/.conf/mytui/init.conf este se recreara con una "
                "configuracion valida");
        exit(EXIT_FAILURE);
    }

    if(*confMap == NULL){
        *confMap = (ConfMap*)malloc(sizeof(ConfMap));
        (*confMap)->value  = (char*)malloc(  strlen(value) + 1);
        strcpy((*confMap)->value , value);
        (*confMap)->key  = (char*)malloc(strlen(key) + 1);
        strcpy((*confMap)->key , key);
        (*confMap)->next = NULL;
    }else{
        ConfMap* tmp_old = *confMap;
        ConfMap* tmp_confMap = (ConfMap*)malloc(sizeof(ConfMap));
        (tmp_confMap)->key  = (char*)malloc(strlen(key) + 1);
        strcpy((tmp_confMap)->key , key);
        (tmp_confMap)->value  = (char*)malloc(  strlen(value) + 1);
        strcpy((tmp_confMap)->value , value);
        (*confMap) =  tmp_confMap;
        (*confMap)->next = tmp_old;
    }
}

void free_conf_map(ConfMap **confMap){

    if(*confMap == NULL){
        print_error("free_conf_map: no puedes liberar confMap null");
         return;
    }
    for(;;){
        if(*confMap == NULL){
            return;
        }else{
            ConfMap *next_node = (* confMap)->next;

            if((*confMap)->key != NULL){
                free((*confMap)->key);
            }
            if((*confMap)->value != NULL){

                free((*confMap)->value);
            }

            if(*confMap != NULL){
                free(*confMap);
            }

            (*confMap) = next_node;
        }
    }
}

void load_conf_map(ConfMap **confMap){
    init_conf_map(*confMap);
    int max_line = 1024;
    char str[max_line];
    char* path_conf_file = get_file_conf_path();
    FILE *f = fopen(path_conf_file, "r");
    const char separator[1]= "=";

    if(f == NULL){
        print_error("load_conf_map: no se consigue el archivo de configuracion");
    }
    while (fgets(str, max_line, f) != NULL){
        char *token;

        token = strtok(str, separator);
        int validateKeyValue = 0;
        char* key;
        char*    value;

        while( token != NULL ) {
            validateKeyValue++;
            if(validateKeyValue == 1){

                key = token;
            }else if( validateKeyValue == 2){
                value = token;
            }
            token = strtok(NULL, separator);
        }
        if(validateKeyValue == 2){
            conf_map_add(confMap, key, value);
        }else{
            print_error("load_conf_map: debe poseer key value cada linea de "
                "la configuracion" );
        }
   }
    fclose(f);
}

const char* getValueConf(ConfMap *confMap, const char* key){
     ConfMap *confTmp =  confMap;

    while(confTmp != NULL){

        if(strcmp(confTmp->key, key) == 0){
            return confTmp->value;
        }
        confTmp = confTmp->next;
    }

    print_info("valor no existe");
    return "";
}

char* resolve_value( ConfMap *confMap,char *type_conf,const char* component_value ){
    if(component_value != NULL && strcmp(component_value , "") != 0){
        print_info("entro en el if");
        return (char*)component_value;
    }

    char* memory_value = (char*)getValueConf(confMap,type_conf);

    if(strcmp(memory_value , "") != 0){
        return memory_value;
    }

    const char separator[1]= "=";

    bool isFound = false;

    //salida para el caso de std
    static char tokenResult[255];

    for(int i = 0; i < MYTUI_CONF_MAX; i++){

        char *token;

        char str[ strlen(mytui_std_conf_optiones[i])];
        strcpy(str, mytui_std_conf_optiones[i]);
        token = strtok(str, separator);

        while( token != NULL ){
            if(strcmp(token, type_conf) == 0 &&  isFound == false){
                token = strtok(NULL, separator);
                if(strlen(token) > 255){
                    print_error("resolve_value: un value no puede ser mayor"
                        " a 255");
                    return "";
                }
                strcpy(tokenResult, token);
                isFound = true;
            }
            token = strtok(NULL, separator);
        }
        if(isFound == true){
            print_info("valor debe ser de %s", tokenResult);
            return tokenResult;
        }
    }
    return "";
}
