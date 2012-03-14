#ifndef COLOR_H
#define COLOR_H

/**
 * \file color.h
 * \author Team BMC editor 
 */


void syntax_highlighting(GtkWidget *widget, BrailleMusicEditor *editor);

void init_braille_table();

void init_colors();

void set_tags(GtkTextBuffer *buffer);

void color(BrailleMusicEditor *editor);

void syntax_highlighting_off(BrailleMusicEditor *editor); 

void color_options(GtkWidget *widget, BrailleMusicEditor *editor);

void color_selection(GtkWidget *widget, BrailleMusicEditor *editor);

#endif
