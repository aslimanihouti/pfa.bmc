#ifndef FILE_SELECTION_H
#define FILE_SELECTION_H

void collect_path(GtkWidget *bouton, GtkWidget *file_selection);
void create_file_selection(GCallback c_handler, const gchar* title);

#endif

