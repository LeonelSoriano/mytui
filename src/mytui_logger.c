#include "mytui_logger.h"

int mytuiDebugModeState;

// static char *_mytui_last_file_logger_in_memory = "";

static const char *LOG_LAST_FILE_NAME = "last.log";

static char *LOG_FILE_NAME_PRE = "info";
static char *LOG_FILE_NAME_POST = ".log";

static FILE *fileLog = NULL;

/* lineas actuales del documento */
static int actual_line_log = 0;

/*lineas maximas en los archivos de log */
static const int MAX_LINE_FILE_LOG = 1000;

static const char *get_path_log()
{
    const char *folder_home = get_home_folder();
    static char conf_folder_resolution[sizeof folder_home + (sizeof SEPARATOR_FOLDER * 4) +
                                       sizeof CONF_FONDER + sizeof TUI_FOLDER_CONF +
                                       sizeof TUI_FOLDER_LOG + sizeof TUI_FOLDER_LOG];

    strcpy(conf_folder_resolution, folder_home);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FONDER);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_CONF);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_LOG);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);

    return conf_folder_resolution;
}

static const char *get_path_next_file_log()
{
    const char *folder_home = get_home_folder();
    static char conf_folder_resolution[sizeof folder_home + (sizeof SEPARATOR_FOLDER * 4) +
                                       sizeof CONF_FONDER + sizeof TUI_FOLDER_CONF +
                                       sizeof TUI_FOLDER_LOG + sizeof TUI_FOLDER_LOG];

    strcpy(conf_folder_resolution, folder_home);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, CONF_FONDER);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_CONF);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);
    strcat(conf_folder_resolution, TUI_FOLDER_LOG);
    strcat(conf_folder_resolution, SEPARATOR_FOLDER);

    return conf_folder_resolution;
}

static void get_next_file()
{
    DIR *d;
    struct dirent *dir;
    int maxValueInFile = 0;
    d = opendir(get_path_next_file_log());
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 ||
                strcmp(dir->d_name, LOG_LAST_FILE_NAME) == 0) {
                continue;
            }
            if (strstr(dir->d_name, LOG_FILE_NAME_PRE) != NULL) {
                // contains
                char a[strlen(dir->d_name)];
                strcpy(a, dir->d_name);
                delete_word(a, LOG_FILE_NAME_POST);

                delete_word(a, LOG_FILE_NAME_PRE);

                if (strIsInt(a)) {
                    int valueFromFile = atoi(a);
                    if (valueFromFile > maxValueInFile)
                        maxValueInFile = valueFromFile;
                }
            }
        }
        closedir(d);
    } // end while
    maxValueInFile++;
    char maxValueInFileStr[12];
    sprintf(maxValueInFileStr, "%d", maxValueInFile);

    char name_new_file[strlen(maxValueInFileStr) + strlen(LOG_FILE_NAME_PRE) +
                       strlen(LOG_FILE_NAME_POST)];
    strcpy(name_new_file, LOG_FILE_NAME_PRE);
    strcat(name_new_file, maxValueInFileStr);
    strcat(name_new_file, LOG_FILE_NAME_POST);

    const char *folder_log = get_path_log();
    char logFile[strlen(folder_log) + strlen(LOG_LAST_FILE_NAME)];
    strcpy(logFile, folder_log);
    strcat(logFile, LOG_LAST_FILE_NAME);

    char logNewFile[strlen(folder_log) + strlen(name_new_file)];
    strcpy(logNewFile, folder_log);
    strcat(logNewFile, name_new_file);

    fclose(fileLog);
    if (copy_file(logFile, logNewFile)) {

        remove(logFile);

        fileLog = fopen(logFile, "wb");
        actual_line_log = 0;
    }
}

void print_line_log(MytuiLoggerType mytuiLoggerType, const char *msg, ...)
{
    actual_line_log++;
    time_t timer;
    char buffer_time[26];
    struct tm *tm_info;
    time(&timer);
    tm_info = localtime(&timer);
    strftime(buffer_time, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    const char *after_date_str = " : ";
    const char *new_line = "\n";

    char tmp_str[strlen(msg) + strlen(buffer_time) + strlen(after_date_str) + strlen(new_line)];

    strcpy(tmp_str, buffer_time);
    strcat(tmp_str, after_date_str);
    strcat(tmp_str, msg);
    strcat(tmp_str, new_line);

    va_list args;
    va_start(args, msg);

    vfprintf(fileLog, tmp_str, args);

    va_end(args);
    // TODO cuando hace rotamiento de archivo no consigue otro
    if (actual_line_log > MAX_LINE_FILE_LOG) {
        get_next_file();
        return;
    }
}

static void init_cursor_file_log()
{
    if (fileLog == NULL) {
        const char *folder_log = get_path_log();

        char logFile[strlen(folder_log) + strlen(LOG_LAST_FILE_NAME)];
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        strcpy(logFile, folder_log);

        strcat(logFile, LOG_LAST_FILE_NAME);
        fileLog = fopen(logFile, "r+");
        if (fileLog == NULL) {
            printf("No se pudo encontrar el ultimo archivo de log\n");
            fileLog = fopen(logFile, "wb");
        }

        while ((read = getline(&line, &len, fileLog)) != -1) {
            actual_line_log++;
        }

        if (line) {
            free(line);
        }

        if (actual_line_log > MAX_LINE_FILE_LOG) {
            get_next_file();
            init_cursor_file_log();
            return;
        }
    }
}

static void verificate_fold_log()
{
    const char *folder_log = get_path_log();
    // char conf_folder_resolution[strlen(folder_home)];

    DIR *dir = opendir(folder_log);
    if (dir == NULL) {
        printf("Could not open current directory  %s", folder_log);
        mkdir(folder_log, 0700);
    }
    if (dir != NULL) {
        free(dir);
    }
}

void init_mytui_logger()
{

    verificate_fold_log();
    init_cursor_file_log();
}

void free_mytui_logger()
{
    if (fileLog != NULL) {
        fclose(fileLog);
    }
}
