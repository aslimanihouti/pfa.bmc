#include <stdio.h>
#include <gtk/gtk.h>
#include "errors.h"

extern GtkWidget *text_view;
extern const gchar *current_file_path;

void save_file(GtkWidget *button)
{
	GtkTextBuffer *buffer;
	GtkTextIter start;
	GtkTextIter end;
	GtkWidget *file_selection;
	FILE *file;
	const gchar *path;
	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
	
	//creation of the file selection window
	file_selection = gtk_file_chooser_dialog_new ("Save file",
	                                              NULL,
	                                              GTK_FILE_CHOOSER_ACTION_SAVE,
	                                              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                         GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
	                                         NULL);
	//banning use of other window
	gtk_window_set_modal(GTK_WINDOW(file_selection), TRUE);
	
	if(gtk_dialog_run(GTK_DIALOG(file_selection))==GTK_RESPONSE_ACCEPT)
		{
			path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_selection));
	
			file = fopen(path,"w+");
			open_error(file_selection, file, "Can't save in the file : \n%s", path);

			//save the current file path
			current_file_path=path;
	
			gtk_text_buffer_get_start_iter(buffer,&start);
			gtk_text_buffer_get_end_iter(buffer,&end);
			
			const gchar *write=gtk_text_buffer_get_text(buffer,&start, &end,TRUE);
	
			fputs(write, file);
			
			fclose(file);
		}
	gtk_widget_destroy(file_selection);
}
