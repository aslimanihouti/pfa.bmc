#ifndef WINDOW_H
#define WINDOW_H


void create_window(const gchar* title, gint width , gint height, BrailleMusicEditor *editor);

void on_window_destroy(GtkObject *object, BrailleMusicEditor *editor);
	
#endif
