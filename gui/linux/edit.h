#ifndef EDIT_H
#define EDIT_H


/**
 * \file edit.h
 * \author Team BMC editor 
 */


/**
 * edit menu callback prototypes
 */

void on_copy(GtkWidget *widget, BrailleMusicEditor *editor);
void on_cut(GtkWidget *widget, BrailleMusicEditor *editor);
void on_paste(GtkWidget *widget, BrailleMusicEditor *editor);
void on_select(GtkWidget *widget, BrailleMusicEditor *editor);
void on_select_all(GtkWidget *widget, BrailleMusicEditor *editor);

#endif
