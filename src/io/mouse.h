#pragma once
/*-----------------------------
  mouse.h
  (c) H.Buchmann FHNW 2012
  $Id$
-------------------------------*/
typedef enum
{
 LE_BUTTON =(1<<0),
 RI_BUTTON =(1<<1),
 MI_BUTTON =(1<<2)
} Button;

typedef void (*OnMouse)(int x,int y,
                        unsigned button);

extern void mouse_register(OnMouse mouse);
extern void mouse_enable();
