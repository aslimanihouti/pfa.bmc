#include <stdio.h>
#include <gtk/gtk.h>

extern GtkWidget *text_view;
void open_file(GtkWidget *button, GtkWidget *file_selection)
{
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;
	FILE *file;
	const gchar *path;
	gchar read[1024];

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

	path = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection));
	file = fopen(path,"rt");

	if(file == NULL)
		{
			GtkWidget *dialog;

			dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Can't open the file : \n%s", g_locale_to_utf8(path, -1, NULL, NULL, NULL));
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
			gtk_widget_destroy(file_selection);

			return;
		}

	gtk_widget_destroy(file_selection);

	gtk_text_buffer_get_start_iter(buffer,&start);
	gtk_text_buffer_get_end_iter(buffer,&end);
	gtk_text_buffer_delete(buffer, &start, &end);

	while(fgets(read, 1024, file))
		{
			gtk_text_buffer_get_end_iter(buffer,&end);
			gtk_text_buffer_insert(buffer, &end, read, -1);
		}

	fclose(file);
}
