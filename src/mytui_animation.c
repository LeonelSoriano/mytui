#include "mytui_animation.h"

MytuiAnimation* init_MytuiAnimation(MiTuiWidget *widget)
{

    if (widget == NULL) {
        print_error(
            "MytuiAnimation init_mytuiAnimation no puede ser inicializada con un widget NULL");
    }

    MytuiAnimation* animation = (MytuiAnimation*) malloc(sizeof(MytuiAnimation));
    animation->listAnimationsStep = NULL;
    animation->widget = widget;
    return animation;
}


void add_step_MytuiAnimation(MytuiAnimation** animation, MytuiAnimationTypes typeAnimation,
        double values[4], float step_time){
    if (*animation == NULL) {
        print_error("add_step_MytuiAnimation: MytuiAnimation* no pueden ser NULL");
    }
    MytuiStepAnimation *stepAnimation = (MytuiStepAnimation *)malloc(sizeof(MytuiStepAnimation));
    stepAnimation->step_time = step_time;
    stepAnimation->typeAnimation = typeAnimation;
    memcpy(stepAnimation->values, values, sizeof(values[0])*4);

    if((*animation)->listAnimationsStep == NULL){
        stepAnimation->next = NULL;

        (*animation)->listAnimationsStep = stepAnimation;
    }else{
        struct mytuiStepAnimation *tmpAniamtion = (*animation)->listAnimationsStep;
        stepAnimation->next = tmpAniamtion;
        (*animation)->listAnimationsStep = stepAnimation;
    }
}


void free_MytuiAnimation(MytuiAnimation** animation){

    if(*animation == NULL){
        print_error("free_MytuiAnimation: MytuiAnimation** no puede ser NULL");
        return;
    }

    if((*animation)->listAnimationsStep != NULL){

        while((*animation)->listAnimationsStep != NULL){

            struct mytuiStepAnimation* tmpStepAnimation = (*animation)->listAnimationsStep->next;
            free((*animation)->listAnimationsStep);
            (*animation)->listAnimationsStep = tmpStepAnimation;
        }
    }
    free(*animation);
}


#include <math.h>

void update_mytuiAnimation(MytuiAnimation** animation){
//	sleep(2);

    MytuiStepAnimation* tmpAnimationStep =  (*animation)->listAnimationsStep;
	while(tmpAnimationStep != NULL){

		switch(tmpAnimationStep->typeAnimation){
		case  mytuiAnimationMove:
            if((*animation)->widget->type == mytuiButton){
                clean_MyTuiWidget((*animation)->widget, NULL);
                (*animation)->widget->x += tmpAnimationStep->values[0];
                (*animation)->widget->y += tmpAnimationStep->values[1];
                update_MyTuiWidget((*animation)->widget);

                float seconds = tmpAnimationStep->step_time - ((int)tmpAnimationStep->step_time) ;

float nanoseconds2 = 1000000000;
    //        double tmp_float = ( tmpAnimationStep->step_time - seconds);


            //long nanoseconds = ((long) tmp_float ) * 100000000;

            print_error("valor %f", (seconds) * nanoseconds2);


    print_info("time %f - %.0lf",tmpAnimationStep->step_time , (double)((seconds * 10)* nanoseconds2));

            //    struct timespec reqDelay = {seconds, nanoseconds}; nanosleep(&reqDelay, (struct timespec *) NULL);
            }

			break;
		}

        screen_manager(&nodeBufer);
		tmpAnimationStep = tmpAnimationStep->next;
	}

}
