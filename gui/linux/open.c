#include <stdio.h>
#include <gtk/gtk.h>
#include "errors.h"

extern GtkWidget *text_view;
extern const gchar *current_file_path;


void open_file(GtkWidget *button)
{
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;
	GtkWidget * file_selection;
	FILE *file;
	const gchar *path;
	gchar read[1024];

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

	//creation of the file selection window
	file_selection = gtk_file_chooser_dialog_new ("Open File",
	                                         NULL,
	                                         GTK_FILE_CHOOSER_ACTION_OPEN,
	                                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                         GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
	                                         NULL);
	//banning use of other window
	gtk_window_set_modal(GTK_WINDOW(file_selection), TRUE);
	if(gtk_dialog_run(GTK_DIALOG(file_selection))==GTK_RESPONSE_ACCEPT)
		{
			/* retrival of the file path */
			path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_selection));
			file = fopen(path,"r");

			open_error(file_selection, file, "Can't open the file : \n%s", path);

			//save the current file path
			current_file_path=path;

			
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
	gtk_widget_destroy(file_selection);	
}
