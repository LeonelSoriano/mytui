#include "mytui_buffer.h"

void init_buffer(NodeBufer **nodeBufer){
    struct InfoTerm infoTerm = get_info_term();
    int max_buffer = (infoTerm.height)  * (infoTerm.width + 1) ;
    if(*nodeBufer != NULL){
        print_error("init_bufffer: error no puede ser null el nodebuffer");
    }

    for (int i = 0; i <= (int)(max_buffer); i++) {
        if(i == 0){
            *nodeBufer = (NodeBufer *)malloc(sizeof(NodeBufer));
            (*nodeBufer)->next = NULL;
            (*nodeBufer)->update = true;
        }else{
            NodeBufer *tmp_buffer = (NodeBufer *)malloc(sizeof(NodeBufer));
            tmp_buffer->next = (*nodeBufer);
            tmp_buffer->update = true;
            (*nodeBufer) = tmp_buffer;
        }
    }
}

void free_buffer(NodeBufer **nodeBufer){
    if(*nodeBufer == NULL){
        print_error("free_buffer: no puede ser null el nodebufer");
        exit(EXIT_FAILURE);
    }
    while((*nodeBufer)->next != NULL){
        NodeBufer *tmp_buffer = (*nodeBufer)->next;
        free(*nodeBufer);
        (*nodeBufer) = tmp_buffer;
    }
    if((*nodeBufer) != NULL){
        free(*nodeBufer);
    }
}

void screen_manager(NodeBufer **nodeBufer){
    unsigned int x = 0,y =0;
    NodeBufer *initPosBuffer = *nodeBufer;
    struct InfoTerm infoTerm = get_info_term();
    if(*nodeBufer != NULL){
        do{
            if(x  >= infoTerm.width ){
                tb_change_cell(x , y , 'x', 100, 10);
                y++;
                x= 0;
            }else{
                tb_change_cell(x , y , '0', 100, 1);
                x++;
            }
            (*nodeBufer) = (*nodeBufer)->next;
        }while((*nodeBufer)->next != NULL);

    }
    *nodeBufer = initPosBuffer;

    tb_present();
}

void reevaluete_screen_manager(NodeBufer **nodeBufer){
    free_buffer(nodeBufer);
    init_buffer(nodeBufer);
    screen_manager(nodeBufer);
}


void nodeTranformation_init(NodeTranformation **nodeTranformation){
    *nodeTranformation = NULL;
}
