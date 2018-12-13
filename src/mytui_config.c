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

void conf_map_add(ConfMap **confMap, const char* key, const char* value){
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
        (*confMap)->key = key;
        (*confMap)->value = value;
        (*confMap)->next = NULL;
    }else{
        /** (*nodeTranformation) = tmp_tranformation; */
        /** (*nodeTranformation)->next = tmp_old; */
        ConfMap* tmp_old = (*confMap);
        ConfMap* tmp_confMap = (ConfMap*)malloc(sizeof(ConfMap));
        (*confMap)->key = key;
        (*confMap)->value = value;
        (*confMap) =  tmp_confMap;
        (*confMap)->next = tmp_old;
    }
}

