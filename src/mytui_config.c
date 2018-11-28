#include "mytui_config.h"

void ini_conf_file(){
    print_info("ini_con_file");
    verification_init_file();
    print_info("terminada verificacion de existencia de archivos de configuracion");
    //bool exist_file(const char* path);
    char *hola = "hola";
get_file_conf_path(&hola);
    printf("%s\n",hola );
}

static void create_default_conf(){
    //FILE *f = fopen();



}


static void get_file_conf_path(char *path){
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
    path = conf_folder_resolution;
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
