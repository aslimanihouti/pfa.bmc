#ifndef WINDOW_H
#define WINDOW_H

/**
 * \file window.h
 * \author Team BMC editor 
 */


void create_window(const gchar* title, gint width , gint height, BrailleMusicEditor *editor);

void window_destroy (GtkWidget *widget, BrailleMusicEditor *editor);

gboolean window_delete_event (GtkWidget *widget, GdkEvent *event, BrailleMusicEditor *editor);	

#endif
