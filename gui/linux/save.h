#ifndef SAVE_H
#define SAVE_H

void save_file(GtkWidget *widget, BrailleMusicEditor *editor);

void save_file_as(GtkWidget *widget, BrailleMusicEditor *editor);

void write_file(gchar *path,GtkTextBuffer *buffer, GtkWidget *file_selection, BrailleMusicEditor *editor);

gint check_for_save (BrailleMusicEditor *editor);

#endif
