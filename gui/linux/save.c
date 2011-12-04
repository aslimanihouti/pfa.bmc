#include <stdio.h>
#include <gtk/gtk.h>
#include "BrailleMusicEditor.h"
#include "save.h"
#include "errors.h"

void save_file(GtkWidget *widget, BrailleMusicEditor *editor)
{
	GtkTextBuffer *buffer;
	GtkWidget *file_selection;
	gchar *path;
	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor->textview));
	
	if(editor->filename!=NULL)
		write_file(editor->filename,buffer, NULL, editor);
	else
		{
			//creation of the file selection window
			file_selection = gtk_file_chooser_dialog_new ("Save file",
			                                              NULL,
			                                              GTK_FILE_CHOOSER_ACTION_SAVE,
			                                              GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			                                              GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
			                                              NULL);
			//banning use of other window
			gtk_window_set_modal(GTK_WINDOW(file_selection), TRUE);
			
			gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(file_selection), TRUE);
			
			if(gtk_dialog_run(GTK_DIALOG(file_selection))==GTK_RESPONSE_ACCEPT)
				{
					path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_selection));
					write_file(path,buffer, file_selection, editor);
				}
			gtk_widget_destroy(file_selection);
		}
}
	
	
void save_file_as(GtkWidget *widget, BrailleMusicEditor *editor)
{
	editor->filename=NULL;
	save_file(widget, editor);
}



void write_file(gchar *path,GtkTextBuffer *buffer, GtkWidget *file_selection, BrailleMusicEditor *editor)
{
	FILE *file;
	GtkTextIter start;
	GtkTextIter end;
	
	file = fopen(path,"w+");
	open_error(file_selection, file, "Can't save in the file : \n%s", path);
	
	//save the current file path
	editor->filename=path;
	
	gtk_text_buffer_get_start_iter(buffer,&start);
	gtk_text_buffer_get_end_iter(buffer,&end);
	
	const gchar *write=gtk_text_buffer_get_text(buffer,&start, &end,TRUE);
	
	fputs(write, file);
	
	fclose(file);
}
