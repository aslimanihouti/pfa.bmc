#ifndef SAVE_H
#define SAVE_H

void save_file(GtkWidget *button);

void save_file_as(GtkWidget *button);

void write_file(const gchar *path,GtkTextBuffer *buffer, GtkWidget *file_selection);

#endif
