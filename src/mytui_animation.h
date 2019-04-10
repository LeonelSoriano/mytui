/** @file mytui_animation.h
 *  @ingroup Animation
 *  @brief funcionalidades pequeñas de animacion basicas
 *  @date 04-02-2019
 *  @author leonelsoriano3@gmail.com
 */
#ifndef __MYTUI_ANIMATION_H__
#define __MYTUI_ANIMATION_H__

#include "mytui_widget.h"
#include <unistd.h>

#include <time.h>
#include <errno.h>


/**
 * @brief enumeración de tipos de animacionesa en el core.
 *
 * Enum que posee los tipos de animaciones.
 */
typedef enum {
    mytuiAnimationMove = 1, /**< anima una caja de widget MytuiAnimationTypes#mytuiAnimationBox */
} MytuiAnimationTypes;

typedef struct MytuiAnimation {
    struct MiTuiWidget *widget;
    struct mytuiStepAnimation *listAnimationsStep;
} MytuiAnimation;

typedef struct mytuiStepAnimation {
    MytuiAnimationTypes typeAnimation;
    double values[4];
    double step_time;
    struct mytuiStepAnimation *next;
} MytuiStepAnimation;

/**
 *  @brief inicia na aimacion
 *  @param el widget que se ejercera las animaciones
 *  @return una MytuiAnimation inicializada
 */
MytuiAnimation* init_MytuiAnimation(struct MiTuiWidget *widget);


/**
 *  @brief agrega un step a la animacion
 *  @param la animacion que se le agregara una animacion
 *  @param tipo de animacion
 *  @param valor asociado
 *  @param duracion del paso en milisecond
 */
void add_step_MytuiAnimation(struct MytuiAnimation** animation, MytuiAnimationTypes typeAnimation,
        double values[4], double step_time);

/**
 *  @brief libera la memoria de una mytui animation
 *  @param el widget que se ejercera las animaciones
 */
void free_MytuiAnimation(MytuiAnimation** animation);

/**
 *  @brief genera la animacion del componente
 *  @param structura que posee la informacion de la animacion
 */
void update_mytuiAnimation(struct MytuiAnimation** animation);


#endif
