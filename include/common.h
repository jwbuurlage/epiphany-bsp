#define DEBUG
#define MAX_N_REGISTER 10
#define MAX_NAME_SIZE 30
#define REGISTERMAP_BUFFER_ADRESS 0x7000 //MUST BE IN SHARED MEMORY e_mem_t struct??
#define REGISTERMAP_ADRESS 0x7050 //MUST BE IN LOCAL MEMORY
#define CORE_ID e_group_config.core_row*e_group_config.group_cols+e_group_config.core_col
#define CORE_ROW e_group_config.core_row
#define CORE_COL e_group_config.core_col
#define NCORES e_group_config.group_rows*e_group_config.group_cols