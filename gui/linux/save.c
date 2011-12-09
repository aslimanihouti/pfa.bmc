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


gint check_for_save (BrailleMusicEditor *editor)
{
	int ret = 2;
	//0 means no, 1 means yes, 2 means cancel 
	GtkTextBuffer *buffer;
        
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (editor->textview));
        
	if (gtk_text_buffer_get_modified (buffer) == TRUE)
		{
			// we need to prompt for save 
			GtkWidget *dialog;
                
			const gchar *msg  = "Do you want to save the changes you have made?";
                
			dialog = gtk_message_dialog_new (GTK_WINDOW(editor->window), 
			                                 GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,
			                                 GTK_MESSAGE_QUESTION,
			                                 GTK_BUTTONS_YES_NO,
			                                 msg);
        
			gtk_window_set_title (GTK_WINDOW (dialog), "Save?");
			
			gint resp=gtk_dialog_run (GTK_DIALOG (dialog));
			if ( resp == GTK_RESPONSE_YES)
				ret = 1;
			else if( resp == GTK_RESPONSE_NO)
				ret = 0;
                
			gtk_widget_destroy (dialog);     
		}     	
	return ret;
}
