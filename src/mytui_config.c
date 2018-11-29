#include "mytui_config.h"

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
        print_error("create_default_conf: error al conseguir el archivo de conf: %s",path_conf_file );
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MYTUI_CONF_MAX; i++) {
        //fputs( mytui_std_conf1[i] , f);
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
