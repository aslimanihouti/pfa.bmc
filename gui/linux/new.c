#include <gtk/gtk.h>

extern GtkWidget *text_view;
extern const gchar *current_file_path;

void new_file()
{
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	
	gtk_text_buffer_get_start_iter(buffer,&start);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_delete(buffer, &start, &end);

	current_file_path = NULL;
}
